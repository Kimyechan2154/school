#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

void midterm()
{
	FILE* fp = NULL;
	int cnt_i;
	int data;

	// 파일에 있는 숫자를 읽어서 화면에 출력 하시오.
	fp = fopen("data.txt", "rt");
	if (fp == NULL)
	{
		printf("Error");
		return;
	}
	
	for (cnt_i = 0; cnt_i < 10; cnt_i++)
	{
		//데이터 읽기(data 변수)
		fscanf(fp, "%d", &data);
		fprintf("%d\n", data);
		//데이터를 화면에 출력
	}

	getchar();
}

// main 함수에서 midterm() 함수를 호출하여 실행
int main()
{
	midterm();

	return 0;
}
// EOF
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

void midterm()
{
	FILE* fp = NULL;
	int cnt_i;
	int data;

	// 파일에 있는 숫자를 읽어서 화면에 출력 하시오.
	fp = fopen("data.txt", "rt");
	if (fp == NULL)
	{
		printf("Error");
		return;
	}
	
	for (cnt_i = 0; cnt_i < 10; cnt_i++)
	{
		//데이터 읽기(data 변수)
		fscanf(fp, "%d", &data);
		fprintf("%d\n", data);
		//데이터를 화면에 출력
	}

	getchar();
}

// main 함수에서 midterm() 함수를 호출하여 실행
int main()
{
	midterm();

	return 0;
}
// EOF
