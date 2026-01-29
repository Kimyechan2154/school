#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdint.h> //8비트 정수 사용을 위함

typedef uint8_t byte; //8비트 부호없는 정수형을 byte로 정의

#define AES_BLOCK_SIZE 16 // AES 블록 크기 (16바이트)
#define AES_ROUND_SIZE 16 //각 라운드 키 크기 (16바이트)
#define AES_KEY_SIZE 16 // AES 키 크기 (16바이트, 128비트)

void SubBytes(byte state[16]) {

	// SubBytes 함수 구현 (예: S-Box 변환)
}

void ShiftRows(byte state[16]) {
	// ShiftRows 함수 구현
}

void MixColumns(byte state[16]) { 
	// MixColumns 함수 구현
}

void AddRoundKey(byte state[16], byte roundKey[16]) {
	for (int i = 0; i < AES_BLOCK_SIZE; i++) {
		state[i] ^= roundKey[i]; // 라운드 키와 상태를 XOR 연산
	}
}

void AES_Encrypt(byte input[16], byte roundKeys[176]) {

	AddRoundKey(input, roundKeys); // 초기 라운드 키 추가

	for (int round = 1; round <= 9; round++) {
		SubBytes(input);
		ShiftRows(input);
		MixColumns(input); //// 10라운드 까지만
		AddRoundKey(input, &roundKeys[round * AES_ROUND_SIZE]);	
	}
	SubBytes(input);
	ShiftRows(input);
	AddRoundKey(input, &roundKeys[10 * AES_ROUND_SIZE]); // 마지막 라운드 키 추가
}
