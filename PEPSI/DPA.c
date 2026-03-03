#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

int main() {

	char name[21] = { 0 }; //파일 설명 20바이트
	int num_trace = 0; // 파형수 4바이트
	int num_points = 0; // 포인트 수 4바이트
	int end_tag[5] = { 0 }; //마무리 4바이트

	FILE* fp = fopen("powerConsumption.trace", "rb"); // 주어진 파일 열기



}
