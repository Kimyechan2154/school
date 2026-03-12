#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "params.h"
#include "file_read.h"

void fileReadTest()
{
    uint8_t** pt = NULL;
    float** trace = NULL;
    FILE* ptFile = fopen(PT_PATH, "rt");//평문, 암호문은 텍스트로 연다.
    FILE* traceFile = fopen(TRACE_PATH, "rb");//전력 파형은 바이너리로 연다.

    // 헤더 이후로 위치 이동 순수 데이터만 읽게 함
    fseek(traceFile, 32, SEEK_CUR);

    // file 예외 처리
    if (traceFile == NULL || ptFile == NULL)
    {
        printf("file open error\n");
        return;
    }

    // 동적할당(배열이 크기 때문에 추천), 정적 배열로 해도 됩니다.
    pt = (uint8_t**)calloc(NUM_TRACE, sizeof(uint8_t*));
    trace = (float**)calloc(NUM_TRACE, sizeof(float*));
    for (int traceIdx = 0; traceIdx < NUM_TRACE; traceIdx++)
    {
        pt[traceIdx] = (uint8_t*)calloc(16, sizeof(uint8_t));
        trace[traceIdx] = (float*)calloc(NUM_POINT, sizeof(float));
    }

    // 평문 파일 읽기, 예외처리
    if (ptFileRead(pt, ptFile) != 0)
    {
        printf("ptFileRead error\n");
        return;
    }

    // 전력 파일 읽기, 예외처리
    if (traceFileRead(trace, traceFile) != 0)
    {
        printf("traceFileRead error\n");
        return;
    }
    // 파일 닫기
    fclose(traceFile);
    fclose(ptFile);

    // 테스트 출력
    printf("[ptFileRead Test]\n");
    for (int byteIdx = 0; byteIdx < 16; byteIdx++)
    {
        printf("%02x ", pt[0][byteIdx]);
    }
    printf("\n");

    printf("[traceFileRead Test]\n");
    for (int pointIdx = 0; pointIdx < 16; pointIdx++)
    {
        printf("%f ", trace[0][pointIdx]);
    }
    printf("\n");


    // 동적할당 메모리 해제
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
