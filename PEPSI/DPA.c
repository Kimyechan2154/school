#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

int main() {

	char name[21] = { 0 }; //파일 설명 20바이트
	int num_trace = 0; // 파형수 4바이트
	int num_points = 0; // 포인트 수 4바이트
	char end_tag[5] = { 0 }; //마무리 4바이트

	FILE* fp = fopen("powerConsumption.trace", "rb"); // 주어진 파일 열기

	if (fp == NULL) {
		printf("파일을 열 수 없습니다.\n");
		return 1;
	}

	fread(name, 1, 20, fp); // 앞부분 파일 담기
	fread(&num_trace, 4, 1, fp);
	fread(&num_points, 4, 1, fp);
	fread(&end_tag, 4, 1, fp);

	printf("파형 수: %d\n", num_trace);
	printf("포인트 수: %d\n", num_points);
	printf("꼬리표: %s\n", end_tag);

	fclose(fp);
	
	return 0;
}
