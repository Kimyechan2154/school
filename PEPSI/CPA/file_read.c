#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdint.h>

#include "file_read.h" //만든 파일 불러오기
#include "params.h"

int ptFileRead(uint8_t** pt, FILE* ptFile)
{
    for (int traceIdx = 0; traceIdx < NUM_TRACE; traceIdx++) //파형수 1000 만큼 반복
    {
        for (int byteIdx = 0; byteIdx < 16; byteIdx++) //16바이트 반복
        {
            if (fscanf(ptFile, "%2hhx", &pt[traceIdx][byteIdx]) != 1) 
                //16진수(%x)로 2글자씩(%2) 1바이트에(%hh) 맞게 읽어라
            {
                return -1; //파일 끝나면 에러처리
            }
        }
    }
    return 0;
}

int traceFileRead(float** trace, FILE* traceFile)
{
    for (int traceIdx = 0; traceIdx < NUM_TRACE; traceIdx++)//파형수 1000 만큼 반복
    {
        if (fread(trace[traceIdx], sizeof(float), NUM_POINT, traceFile) != NUM_POINT)//데이터를 덩어리로 묶어서 2차원 배열에 통째로 복사
        {
            return -1;
        }
    }
    return 0;
}
