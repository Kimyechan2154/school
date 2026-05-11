#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <memory.h>

// 로터 배선 및 노치 위치 정의
int WIRING_1[] = { 4,10,12,5,11,6,3,16,21,25,13,19,14,22,24,7,20,18,0,9,1,2,23,8,15,17 }; // Rotor I
int WIRING_2[] = { 0,9,3,10,18,8,17,20,23,1,11,7,22,19,12,2,16,6,25,13,15,24,5,21,14,4 }; // Rotor II
int WIRING_3[] = { 1,3,5,7,9,11,13,2,15,16,19,18,20,23,21,14,12,10,8,6,4,0,17,22,24,25 }; // Rotor III
int REFLECT_B[] = { 24,17,20,7,16,18,11,3,15,23,13,6,14,10,12,8,4,1,5,25,2,22,21,9,0,19 };// Reflector B

// 각 로터의 노치(턴오버) 위치: I(Q=16), II(E=4), III(V=21)
int NOTCH_1 = 16, NOTCH_2 = 4, NOTCH_3 = 21;

// 로터 함수 (회전 위치인 offset 반영)
int rotor(int input, int wiring[], int offset, int direction) {
    if (direction == 0) { // 순방향
        int shift_in = (input + offset) % 26;
        int substitution = wiring[shift_in];
        return (substitution - offset + 26) % 26;
    }
    else { // 역방향
        int shift_in = (input + offset) % 26;
        for (int i = 0; i < 26; i++) {
            if (wiring[i] == shift_in) {
                return (i - offset + 26) % 26;
            }
        }
    }
    return -1;
}

int plugboard(int* plug, int input) {
    if (plug[input] == -1) return input;
    return plug[input];
}

int main() {
    int N = 0, Plug[26];
    int off1 = 0, off2 = 0, off3 = 0; // 로터 초기 위치 (A, A, A)
    char sentence[256];

    memset(Plug, -1, sizeof(Plug));

    // 1. 플러그보드 설정
    printf("[plugboard] 연결 쌍 개수: ");
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        char a, b;
        printf("  (%d) 쌍 입력 (예: a b): ", i + 1);
        scanf(" %c %c", &a, &b);
        Plug[a - 97] = b - 97;
        Plug[b - 97] = a - 97;
    }

    // 2. 문장 입력
    printf("\n암호화할 문장 입력 (소문자/공백): ");
    while (getchar() != '\n'); // 입력 버퍼 비우기
    fgets(sentence, sizeof(sentence), stdin);
    sentence[strcspn(sentence, "\n")] = 0; // 줄바꿈 제거

    printf("결과: ");

    // 3. 문장 처리 루프
    for (int i = 0; i < strlen(sentence); i++) {
        if (sentence[i] < 'a' || sentence[i] > 'z') {
            printf("%c", sentence[i]); // 알파벳이 아니면 그대로 출력
            continue;
        }

        // --- 로터 회전 로직 (암호화 전 단계) ---
        // 더블 스테핑 로직 포함
        if (off2 == NOTCH_2) { // 중간 로터가 노치에 도달 시
            off1 = (off1 + 1) % 26;
            off2 = (off2 + 1) % 26;
        }
        else if (off3 == NOTCH_3) { // 오른쪽 로터가 노치에 도달 시
            off2 = (off2 + 1) % 26;
        }
        off3 = (off3 + 1) % 26; // 오른쪽 로터는 매 입력마다 회전

        // --- 암호화 경로 (Signal Path) ---
        int signal = sentence[i] - 97;

        signal = plugboard(Plug, signal);             // 플러그보드 (In)
        signal = rotor(signal, WIRING_3, off3, 0);    // Rotor III (Fwd)
        signal = rotor(signal, WIRING_2, off2, 0);    // Rotor II (Fwd)
        signal = rotor(signal, WIRING_1, off1, 0);    // Rotor I (Fwd)

        signal = REFLECT_B[signal];                   // Reflector

        signal = rotor(signal, WIRING_1, off1, 1);    // Rotor I (Bwd)
        signal = rotor(signal, WIRING_2, off2, 1);    // Rotor II (Bwd)
        signal = rotor(signal, WIRING_3, off3, 1);    // Rotor III (Bwd)
        signal = plugboard(Plug, signal);             // 플러그보드 (Out)

        printf("%c", (char)(signal + 97));
    }
    printf("\n");

    return 0;
}
