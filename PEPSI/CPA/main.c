#define _CRT_SECURE_NO_WARNINGS

// CPA(Correlation Power Analysis) 공격 구현
// - 전력 트레이스와 해밍 가중치 모델의 Pearson 상관계수를 이용해 AES 키 복구

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <math.h>
#include <string.h>

#include "params.h"
#include "file_read.h"

// 상관계수를 계산할 전력 트레이스의 분석 구간 (포인트 인덱스)
#define START_POINT 0
#define END_POINT   3724

// AES SubBytes 치환 테이블 (S-box)
// 1라운드 중간값 intermediate = sbox[pt ^ key] 계산에 사용
const uint8_t sbox[256] = {
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

// 해밍 가중치 룩업 테이블: hw_table[v] = v의 2진수에서 1의 개수
// 전력 소비 모델로 사용 (HW 모델: 전력 ∝ 처리하는 값의 비트 수)
static const uint8_t hw_table[256] = {
    0,1,1,2,1,2,2,3,1,2,2,3,2,3,3,4,
    1,2,2,3,2,3,3,4,2,3,3,4,3,4,4,5,
    1,2,2,3,2,3,3,4,2,3,3,4,3,4,4,5,
    2,3,3,4,3,4,4,5,3,4,4,5,4,5,5,6,
    1,2,2,3,2,3,3,4,2,3,3,4,3,4,4,5,
    2,3,3,4,3,4,4,5,3,4,4,5,4,5,5,6,
    2,3,3,4,3,4,4,5,3,4,4,5,4,5,5,6,
    3,4,4,5,4,5,5,6,4,5,5,6,5,6,6,7,
    1,2,2,3,2,3,3,4,2,3,3,4,3,4,4,5,
    2,3,3,4,3,4,4,5,3,4,4,5,4,5,5,6,
    2,3,3,4,3,4,4,5,3,4,4,5,4,5,5,6,
    3,4,4,5,4,5,5,6,4,5,5,6,5,6,6,7,
    2,3,3,4,3,4,4,5,3,4,4,5,4,5,5,6,
    3,4,4,5,4,5,5,6,4,5,5,6,5,6,6,7,
    3,4,4,5,4,5,5,6,4,5,5,6,5,6,6,7,
    4,5,5,6,5,6,6,7,5,6,6,7,6,7,7,8
};

void fileReadTest()
{
    uint8_t** pt = NULL;
    float** trace = NULL;

    // 평문 파일(텍스트)과 전력 트레이스 파일(바이너리) 열기
    FILE* ptFile    = fopen(PT_PATH,    "rt");
    FILE* traceFile = fopen(TRACE_PATH, "rb");

    if (traceFile == NULL || ptFile == NULL)
    {
        printf("file open error\n");
        return;
    }

    // 트레이스 파일 앞 32바이트는 장비 헤더 정보이므로 건너뜀
    fseek(traceFile, 32, SEEK_CUR);

    // 2D 배열 동적 할당: pt[NUM_TRACE][16], trace[NUM_TRACE][NUM_POINT]
    pt    = (uint8_t**)calloc(NUM_TRACE, sizeof(uint8_t*));
    trace = (float**)  calloc(NUM_TRACE, sizeof(float*));
    for (int traceIdx = 0; traceIdx < NUM_TRACE; traceIdx++)
    {
        pt[traceIdx]    = (uint8_t*)calloc(16,        sizeof(uint8_t));
        trace[traceIdx] = (float*)  calloc(NUM_POINT, sizeof(float));
    }

    // 파일에서 데이터 읽기
    if (ptFileRead(pt, ptFile) != 0)
    {
        printf("ptFileRead error\n");
        return;
    }
    if (traceFileRead(trace, traceFile) != 0)
    {
        printf("traceFileRead error\n");
        return;
    }

    fclose(traceFile);
    fclose(ptFile);

    // 로드 확인: 첫 번째 트레이스의 평문 16바이트 출력
    printf("[ptFileRead Test]\n");
    for (int byteIdx = 0; byteIdx < 16; byteIdx++)
        printf("%02x ", pt[0][byteIdx]);
    printf("\n");

    // 로드 확인: 첫 번째 트레이스의 전력 샘플 16개 출력
    printf("[traceFileRead Test]\n");
    for (int pointIdx = 0; pointIdx < 16; pointIdx++)
        printf("%f ", trace[0][pointIdx]);
    printf("\n");

    // 첫 번째 트레이스 전체를 파일로 저장 (파형 시각화용)
    FILE* f_out = fopen("trace0.txt", "w");
    if (f_out != NULL)
    {
        for (int p = 0; p < NUM_POINT; p++)
            fprintf(f_out, "%f\n", trace[0][p]);
        fclose(f_out);
        printf("\n[SPA] trace0.txt saved\n");
    }

    double start = (double)clock() / CLOCKS_PER_SEC;
    uint8_t finalKey[16] = { 0, };

    printf("\n[CPA %d~%d Points]\n\n", START_POINT, END_POINT);

    // --- 사전 계산: X(전력) 통계량 ---
    // Pearson 공식에서 sumX, sumX2는 키 추측과 무관하므로 루프 밖에서 1회만 계산
    float* sumX  = (float*)calloc(NUM_POINT, sizeof(float)); // Σ X
    float* sumX2 = (float*)calloc(NUM_POINT, sizeof(float)); // Σ X²
    float* sumXY = (float*)malloc(NUM_POINT * sizeof(float)); // Σ X·Y (키마다 갱신)

    for (int traceIdx = 0; traceIdx < NUM_TRACE; traceIdx++)
    {
        for (int pointIdx = START_POINT; pointIdx < END_POINT; pointIdx++)
        {
            sumX[pointIdx]  += trace[traceIdx][pointIdx];
            sumX2[pointIdx] += trace[traceIdx][pointIdx] * trace[traceIdx][pointIdx];
        }
    }

    // 루프 내부에서 반복 선언을 피하기 위해 루프 밖에서 선언
    float     sumY, sumY2, currentKeyMax;          // Y(HW) 통계량 및 현재 키의 최대 상관계수
    float     denominator_x, denominator_y, denominator, numerator, r; // Pearson 계산용
    uint8_t   intermediate;                        // S-box 출력값 (중간값)
    int       hw, currentKeyMaxPoint, bestPoint;   // HW값, 현재/최종 최대 피크 포인트

    // --- 메인 CPA 루프: 16바이트 키를 1바이트씩 복구 ---
    for (int targetByte = 0; targetByte < 16; targetByte++)
    {
        float   bestPeak       = 0.0f; // 256개 키 후보 중 가장 높은 상관계수
        float   secondBestPeak = 0.0f; // 두 번째로 높은 상관계수 (신뢰도 판단용)
        uint8_t bestKey        = 0;
        bestPoint              = 0;

        printf("Target Byte %2d ... ", targetByte);

        // 키 후보 0x00~0xFF 전수 탐색
        for (int keyGuess = 0; keyGuess < 256; keyGuess++)
        {
            // 이 키 후보에 대한 통계량 초기화
            sumY             = 0.0f;
            sumY2            = 0.0f;
            currentKeyMax    = 0.0f;
            currentKeyMaxPoint = 0;
            memset(sumXY, 0, NUM_POINT * sizeof(float));

            // 트레이스별 HW 모델 계산 및 Σ XY 누적
            for (int traceIdx = 0; traceIdx < NUM_TRACE; traceIdx++)
            {
                // 중간값: AES 1라운드 SubBytes(pt XOR key)
                intermediate = sbox[pt[traceIdx][targetByte] ^ keyGuess];
                // 전력 소비 모델: HW(중간값)
                hw            = hw_table[intermediate];
                sumY         += hw;       // Σ Y
                sumY2        += hw * hw;  // Σ Y²
                // 포인트별 Σ X·Y 누적
                for (int pointIdx = START_POINT; pointIdx < END_POINT; pointIdx++)
                    sumXY[pointIdx] += trace[traceIdx][pointIdx] * hw;
            }

            // 포인트별 Pearson 상관계수 r 계산 후 최대값 탐색
            // r = (N·ΣXY - ΣX·ΣY) / sqrt((N·ΣX² - (ΣX)²)·(N·ΣY² - (ΣY)²))
            for (int pointIdx = START_POINT; pointIdx < END_POINT; pointIdx++)
            {
                denominator_x = (NUM_TRACE * sumX2[pointIdx]) - (sumX[pointIdx] * sumX[pointIdx]);
                denominator_y = (NUM_TRACE * sumY2) - (sumY * sumY);
                // 분산이 0이면 상관계수 정의 불가 → 건너뜀
                if (denominator_x <= 0.0f || denominator_y <= 0.0f) continue;
                denominator = sqrtf(denominator_x * denominator_y);
                numerator   = (NUM_TRACE * sumXY[pointIdx]) - (sumX[pointIdx] * sumY);
                r = fabsf(numerator / denominator); // 절댓값: 음의 상관도 동일하게 처리
                if (r > currentKeyMax) { currentKeyMax = r; currentKeyMaxPoint = pointIdx; }
            }

            // 1위/2위 피크 갱신
            if (currentKeyMax > bestPeak)
            {
                secondBestPeak = bestPeak;
                bestPeak       = currentKeyMax;
                bestKey        = (uint8_t)keyGuess;
                bestPoint      = currentKeyMaxPoint; // 최고 상관계수가 나타난 포인트 저장
            }
            else if (currentKeyMax > secondBestPeak)
            {
                secondBestPeak = currentKeyMax;
            }

            if (keyGuess % 32 == 0) printf(".");
        }

        finalKey[targetByte] = bestKey;

        // Ratio = 1위 피크 / 2위 피크: 1.2 이상이면 키가 명확히 분리된 것으로 판단
        float ratio = (secondBestPeak > 0.0f) ? (bestPeak / secondBestPeak) : 0.0f;
        printf(" done! (Key: %02X, Peak: %.4f @ Point %4d, Ratio: %.2f) -> %s\n",
               bestKey, bestPeak, bestPoint, ratio,
               ratio >= 1.2f ? "correct key found" : "low confidence");
    }

    free(sumX);
    free(sumX2);
    free(sumXY);

    double end = (double)clock() / CLOCKS_PER_SEC;

    printf("\n========================================\n");
    printf("AES Key (HEX)  : ");
    for (int i = 0; i < 16; i++) printf("%02X ", finalKey[i]);
    printf("\nAES Key (ASCII): ");
    for (int i = 0; i < 16; i++) printf("%c", finalKey[i]);
    printf("\n\nElapsed: %lf sec\n", end - start);
    printf("========================================\n");

    // 동적 할당 메모리 해제
    for (int traceIdx = 0; traceIdx < NUM_TRACE; traceIdx++)
    {
        free(pt[traceIdx]);
        free(trace[traceIdx]);
    }
    free(pt);
    free(trace);
}

int main()
{
    fileReadTest();
    return 0;
}
