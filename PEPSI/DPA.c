#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

int main() {

	char name[21] = { 0 }; //파일 설명 20바이트 + NULL 문자 공간
	int num_trace = 0; // 파형수 4바이트 
	int num_points = 0; // 포인트 수 4바이트
	char end_tag[5] = { 0 }; //마무리 4바이트 + NULL 문자 공간

	FILE* fp = fopen("powerConsumption.trace", "rb"); // 바이너리 파일 열기

	//실패시 예외 처리
	if (fp == NULL) { 
		printf("파일을 열 수 없습니다.\n");
		return 1;
	}

	fread(name, 1, 20, fp); // 파일 이름 읽기 1바이트씩 20개
	fread(&num_trace, 4, 1, fp); // 파형 수 읽기
	fread(&num_points, 4, 1, fp); // 포인트 수 읽기
	fread(end_tag, 4, 1, fp); // 마무리 읽기

	//결과 출력
	printf("파형 수: %d\n", num_trace);
	printf("포인트 수: %d\n", num_points);
	printf("꼬리표: %s\n", end_tag);

	fclose(fp);
	
	return 0;
}
