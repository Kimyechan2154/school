#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdint.h>

typedef uint8_t byte;

#define AES_BLOCK_SIZE 16
#define AES_ROUND_SIZE 16
#define AES_KEY_SIZE   16

// AES 표준 S-Box
const byte sbox[256] = {
	0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76,
	0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0,
	0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15,
	0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75,
	0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84,
	0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf,
	0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8,
	0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2,
	0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73,
	0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb,
	0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79,
	0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08,
	0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a,
	0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e,
	0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf,
	0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16
};

static inline byte xtime(byte x) {
	return (x << 1) ^ (((x >> 7) & 1) * 0x1b);
}

const byte Rcon[10] = {
	0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36
};

/* =====================================================================
 *  하이딩(Hiding) 인프라
 *  - rng_byte()  : 난수 소스 (데모용 xorshift)
 *                  ※ 실제 타깃 보드에서는 반드시 TRNG/DRBG로 교체할 것.
 *                    PRNG 시드가 예측되면 순열/딜레이가 복원되어 방어 무력화.
 *  - gen_perm()  : 0~15의 무작위 순열 생성 (Fisher-Yates)
 *  - random_delay(): 랜덤 딜레이 삽입(시간 축 하이딩)
 * ===================================================================== */
static uint32_t prng_state = 0x12345678u;

static byte rng_byte(void) {
	uint32_t x = prng_state;
	x ^= x << 13;
	x ^= x >> 17;
	x ^= x << 5;
	prng_state = x;
	return (byte)(x & 0xFF);
}

// 0~15 무작위 순열 (Fisher-Yates 셔플)
// 주의: rng_byte() % (i+1) 은 모듈로 편향(modulo bias)이 존재.
//       고신뢰 구현에서는 rejection sampling으로 편향 제거 권장.
static void gen_perm(byte perm[16]) {
	for (int i = 0; i < 16; i++) perm[i] = (byte)i;
	for (int i = 15; i > 0; i--) {
		int j = rng_byte() % (i + 1);
		byte t = perm[i]; perm[i] = perm[j]; perm[j] = t;
	}
}

// 랜덤 딜레이 삽입: 0~15회 더미 반복. asm("") 로 컴파일러 최적화 제거 방지.
static void random_delay(void) {
	byte n = rng_byte() & 0x0F;
	for (volatile byte k = 0; k < n; k++) { __asm__ __volatile__(""); }
}

/* =====================================================================
 *  셔플링 적용 연산
 *  16바이트를 독립 처리하는 SubBytes / AddRoundKey는 처리 순서를
 *  무작위 순열로 바꿔도 결과가 동일 → 시간 축 하이딩(셔플링) 적용.
 * ===================================================================== */
void SubBytes(byte state[16]) {
	byte perm[16];
	gen_perm(perm);
	for (int j = 0; j < 16; j++) {
		int idx = perm[j];
		state[idx] = sbox[state[idx]];
	}
}

void AddRoundKey(byte state[16], byte roundKey[16]) {
	byte perm[16];
	gen_perm(perm);
	for (int j = 0; j < 16; j++) {
		int idx = perm[j];
		state[idx] ^= roundKey[idx];
	}
}

/* ---- ShiftRows / MixColumns / KeyExpansion : 원본 그대로 ---- */
void ShiftRows(byte state[16]) {
	byte temp;
	temp = state[1]; state[1] = state[5]; state[5] = state[9]; state[9] = state[13]; state[13] = temp;
	temp = state[2]; state[2] = state[10]; state[10] = temp;
	temp = state[6]; state[6] = state[14]; state[14] = temp;
	temp = state[3]; state[3] = state[15]; state[15] = state[11]; state[11] = state[7]; state[7] = temp;
}

void MixColumns(byte state[16]) {
	byte s0, s1, s2, s3;
	for (int i = 0; i < 16; i += 4) {
		s0 = state[i]; s1 = state[i + 1]; s2 = state[i + 2]; s3 = state[i + 3];
		state[i]     = xtime(s0) ^ (xtime(s1) ^ s1) ^ s2 ^ s3;
		state[i + 1] = s0 ^ xtime(s1) ^ (xtime(s2) ^ s2) ^ s3;
		state[i + 2] = s0 ^ s1 ^ xtime(s2) ^ (xtime(s3) ^ s3);
		state[i + 3] = (xtime(s0) ^ s0) ^ s1 ^ s2 ^ xtime(s3);
	}
}

void KeyExpansion(byte key[16], byte roundKeys[11][16]) {
	byte* expandedkey = (byte*)roundKeys;
	byte temp[4];
	for (int i = 0; i < 16; i++) expandedkey[i] = key[i];
	for (int i = 16; i < 176; i += 4) {
		temp[0] = expandedkey[i - 4];
		temp[1] = expandedkey[i - 3];
		temp[2] = expandedkey[i - 2];
		temp[3] = expandedkey[i - 1];
		if (i % 16 == 0) {
			byte t = temp[0];
			temp[0] = temp[1]; temp[1] = temp[2]; temp[2] = temp[3]; temp[3] = t;
			temp[0] = sbox[temp[0]]; temp[1] = sbox[temp[1]];
			temp[2] = sbox[temp[2]]; temp[3] = sbox[temp[3]];
			temp[0] ^= Rcon[(i / 16) - 1];
		}
		expandedkey[i]     = expandedkey[i - 16] ^ temp[0];
		expandedkey[i + 1] = expandedkey[i - 15] ^ temp[1];
		expandedkey[i + 2] = expandedkey[i - 14] ^ temp[2];
		expandedkey[i + 3] = expandedkey[i - 13] ^ temp[3];
	}
}

void AES_Encrypt(byte input[16], byte roundKeys[11][16]) {
	random_delay();                       // [시간 축] 초기 오프셋 랜덤화
	AddRoundKey(input, roundKeys[0]);     // [셔플링]

	for (int round = 1; round <= 9; round++) {
		random_delay();                   // [시간 축] 라운드마다 오프셋 흔들기
		SubBytes(input);                  // [셔플링] ← 1라운드 출력이 CPA 주 공격점
		ShiftRows(input);
		MixColumns(input);
		AddRoundKey(input, roundKeys[round]); // [셔플링]
	}

	random_delay();
	SubBytes(input);                      // [셔플링] ← 마지막 라운드 공격점
	ShiftRows(input);
	AddRoundKey(input, roundKeys[10]);    // [셔플링]
}

int main() {
	byte key[16] = {
		0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6,
		0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c
	};
	byte plaintext[16] = {
		0x32, 0x43, 0xf6, 0xa8, 0x88, 0x5a, 0x30, 0x8d,
		0x31, 0x31, 0x98, 0xa2, 0xe0, 0x37, 0x07, 0x34
	};

	byte AES_secret_key[11][16];
	KeyExpansion(key, AES_secret_key);
	AES_Encrypt(plaintext, AES_secret_key);

	for (int i = 0; i < 16; i++) printf("%02x ", plaintext[i]);
	printf("\n");
	// 기대값: 39 25 84 1d 02 dc 09 fb dc 11 85 97 19 6a 0b 32
}
