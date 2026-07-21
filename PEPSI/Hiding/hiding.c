#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdint.h>
typedef uint8_t byte;
#define AES_BLOCK_SIZE  16
#define AES_ROUND_SIZE  16
#define AES_KEY_SIZE    16
#define AES_HIDDEN_SIZE 18   // 16 + 더미 2
// 기약다항식 x^8 + x^4 + x^3 + x + 1 = 0x11b, 하위 8비트만 사용
#define GF_POLY 0x1b

// S-Box
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

// GF(2^8) x 곱셈, x^8 초과 시 GF_POLY로 환원
static inline byte xtime(byte x) {
	return (x << 1) ^ (((x >> 7) & 1) * GF_POLY);
}

// GF(2^8) 곱셈 (기약다항식 사용)
static byte gf_mul(byte a, byte b) {
	byte result = 0;
	while (b) {
		if (b & 1) result ^= a;
		a = xtime(a);
		b >>= 1;
	}
	return result;
}

// 라운드 상수
const byte Rcon[10] = {
	0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36
};

// 32비트 LFSR (seed = 0 불가)
static uint32_t lfsr_state = 0x12345678u;

// LFSR로 랜덤 1바이트 생성
static byte rng_byte(void) {
	byte out = 0;
	for (int i = 0; i < 8; i++) {
		uint32_t lsb = lfsr_state & 1u;
		lfsr_state >>= 1;
		if (lsb) lfsr_state ^= 0x80200003u;
		out = (byte)((out << 1) | lsb);
	}
	printf("%02x, ", out);
	return out;
}

// Fisher-Yates로 0~17 순열 생성
// x % 2^n == x & (2^n-1) 적용: (i+1)이 2의 거듭제곱이면 & 사용
static void gen_perm_18(byte perm[AES_HIDDEN_SIZE]) {
	for (int i = 0; i < AES_HIDDEN_SIZE; i++) perm[i] = (byte)i;
	for (int i = AES_HIDDEN_SIZE - 1; i > 0; i--) {
		int j;
		if (((i + 1) & i) == 0)
			j = rng_byte() & i;        // x % 2^n == x & (2^n-1)
		else
			j = rng_byte() % (i + 1);
		byte t = perm[i]; perm[i] = perm[j]; perm[j] = t;
	}
}

// 랜덤 더미 지연 (시간 은닉)
static void random_delay(void) {
	byte n = rng_byte() & 0x0F;
	for (volatile byte k = 0; k < n; k++);
}

// SubBytes: 더미 2개 추가해 18회 처리, 오더 배열 미리 출력 (16개만)
void SubBytes(byte state[16]) {
	byte buf[AES_HIDDEN_SIZE];
	for (int i = 0; i < 16; i++) buf[i] = state[i];
	buf[16] = rng_byte();  // 더미
	buf[17] = rng_byte();  // 더미

	byte ls[AES_HIDDEN_SIZE];
	gen_perm_18(ls);

	printf("\nSubBytes order: ");
	for (int i = 0; i < 16; i++) printf("%2d ", ls[i]);
	printf("\n");

	for (int byteIdx = 0; byteIdx < AES_HIDDEN_SIZE; byteIdx++)
		buf[ls[byteIdx]] = sbox[buf[ls[byteIdx]]];

	for (int i = 0; i < 16; i++) state[i] = buf[i];
}

// AddRoundKey: 더미 2개 추가해 18회 XOR
void AddRoundKey(byte state[16], byte rk[16]) {
	byte s_buf[AES_HIDDEN_SIZE], rk_buf[AES_HIDDEN_SIZE];
	for (int i = 0; i < 16; i++) { s_buf[i] = state[i]; rk_buf[i] = rk[i]; }
	s_buf[16] = rng_byte();  rk_buf[16] = rng_byte();  // 더미
	s_buf[17] = rng_byte();  rk_buf[17] = rng_byte();  // 더미

	byte ls[AES_HIDDEN_SIZE];
	gen_perm_18(ls);

	for (int byteIdx = 0; byteIdx < AES_HIDDEN_SIZE; byteIdx++)
		s_buf[ls[byteIdx]] = s_buf[ls[byteIdx]] ^ rk_buf[ls[byteIdx]];

	for (int i = 0; i < 16; i++) state[i] = s_buf[i];
}

// ShiftRows / MixColumns / KeyExpansion: 표준 구현

void ShiftRows(byte state[16]) {
	byte temp;
	temp = state[1]; state[1] = state[5]; state[5] = state[9]; state[9] = state[13]; state[13] = temp;
	temp = state[2]; state[2] = state[10]; state[10] = temp;
	temp = state[6]; state[6] = state[14]; state[14] = temp;
	temp = state[3]; state[3] = state[15]; state[15] = state[11]; state[11] = state[7]; state[7] = temp;
}

// MixColumns 행렬: [[2,3,1,1],[1,2,3,1],[1,1,2,3],[3,1,1,2]]
void MixColumns(byte state[16]) {
	byte s0, s1, s2, s3;
	for (int i = 0; i < 16; i += 4) {
		s0 = state[i]; s1 = state[i + 1]; s2 = state[i + 2]; s3 = state[i + 3];
		state[i]     = gf_mul(0x02, s0) ^ gf_mul(0x03, s1) ^ s2               ^ s3;
		state[i + 1] = s0               ^ gf_mul(0x02, s1) ^ gf_mul(0x03, s2) ^ s3;
		state[i + 2] = s0               ^ s1               ^ gf_mul(0x02, s2) ^ gf_mul(0x03, s3);
		state[i + 3] = gf_mul(0x03, s0) ^ s1               ^ s2               ^ gf_mul(0x02, s3);
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
			// RotWord
			byte t = temp[0];
			temp[0] = temp[1]; temp[1] = temp[2]; temp[2] = temp[3]; temp[3] = t;
			// SubWord
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
	random_delay();
	AddRoundKey(input, roundKeys[0]);

	for (int round = 1; round <= 9; round++) {
		random_delay();
		SubBytes(input);
		ShiftRows(input);
		MixColumns(input);
		AddRoundKey(input, roundKeys[round]);
	}

	random_delay();
	SubBytes(input);
	ShiftRows(input);
	AddRoundKey(input, roundKeys[10]);
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
	printf("\n\nCipher Text = ");
	for (int i = 0; i < 16; i++) printf("%02x ", plaintext[i]);
	printf("\n");
	// 기댓값: 39 25 84 1d 02 dc 09 fb dc 11 85 97 19 6a 0b 32
}
