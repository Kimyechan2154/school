#include <stdio.h>
#include <stdint.h>

// 1. 자료형 및 상수 정의 (Basic Definitions)
// uint8_t를 'byte'로 정의하여 가독성 향상 및 1바이트 단위 명시
typedef uint8_t byte;

#define BLOCK_SIZE 16 // AES 블록 크기 (128비트 = 16바이트)
#define ROUNDS 10     // AES-128 라운드 수

// -------------------------------------------------------------------------
// 2. 핵심 함수 선언 (Function Declarations)
// state[16]: 4x4 행렬 대신 1차원 배열 사용 (구현 및 반복문 효율성 위해)
// -------------------------------------------------------------------------

// S-Box를 이용한 1:1 바이트 치환
void SubBytes(byte state[16]) {
    // TODO: S-Box Lookup Table을 이용한 치환 구현 예정
}

// 행(Row) 단위 이동 (Shift)
void ShiftRows(byte state[16]) {
    // TODO: 각 행별 좌측 Shift 연산 구현 예정
}

// 열(Column) 단위 섞기 (Mix)
void MixColumns(byte state[16]) {
    // TODO: Galois Field 곱셈을 이용한 열 혼합 구현 예정
}

// 라운드 키와 XOR 연산 (Key Mixing)
// 이 함수는 연산이 단순하므로 선언과 동시에 구현함
void AddRoundKey(byte state[16], const byte roundKey[16]) {
    for (int i = 0; i < BLOCK_SIZE; i++) {
        state[i] ^= roundKey[i]; // XOR 연산 (같으면 0, 다르면 1)
    }
}
