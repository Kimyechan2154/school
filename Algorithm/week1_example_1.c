#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
//#include "student.h"

/*
struct 구조채 선언 예약어

*/


void week1() {
	typedef struct _STUDENT_ {
		char name[32];
		int id;
	}STUDENT;

	typedef struct _PROFILE_ {
		STUDENT st;
		char major[32];
		int age;
		char addr[32];
	}PROFILE;

	PROFILE stu1, stu2;

	scanf("%s", stu1.st.name);
	scanf("%d", &stu1.st.id);
	scanf("%s", stu1.major);
	scanf("%d", &stu1.age);
	scanf("%s", stu1.addr);

	printf("\n%s\n", stu1.st.name);
	printf("%d\n", stu1.st.id);
	printf("%s\n", stu1.major);
	printf("%d\n", stu1.age);
	printf("%s\n", stu1.addr);

	stu2 = stu1; // 같은 값 나옴

	printf("\n%s\n", stu2.st.name);
	printf("%d\n", stu2.st.id);
	printf("%s\n", stu2.major);
	printf("%d\n", stu2.age);
	printf("%s\n", stu2.addr);

	//이런식 선언도 가능
	PROFILE stu3 = {"kim", 20222101, "Securit", 24, "good"}; 

	printf("\n%s\n", stu3.st.name);
	printf("%d\n", stu3.st.id);
	printf("%s\n", stu3.major);
	printf("%d\n", stu3.age);
	printf("%s\n", stu3.addr);

	//구조체 배열
	PROFILE stu4[3];
	
	for (int i = 0; i < sizeof(stu4) / sizeof(PROFILE); i++) {
		scanf("%s", stu4[i].st.name);
		scanf("%d", &stu4[i].st.id);
		scanf("%s", stu4[i].major);
		scanf("%d", &stu4[i].age);
		scanf("%s", stu4[i].addr);
	}
	
	for (int i = 0; i < sizeof(stu4) / sizeof(PROFILE); i++) {
		printf("\n%s\n", stu4[i].st.name);
		printf("%d\n", stu4[i].st.id);
		printf("%s\n", stu4[i].major);
		printf("%d\n", stu4[i].age);
		printf("%s\n", stu4[i].addr);
	}
}



typedef struct _STUDENT_ {
	char name[32];
	double grade;
	int english;
}STUDENT;

void input(STUDENT* sp, int size) {
	
	for (int i = 0; i < size; i++) {
		scanf("%s", (sp + 1)->name);
		scanf("%lf", &(sp + 1)->grade);
		scanf("%d", &(sp + 1)->english);
	}
}

void elite(STUDENT* sp, int size) {

	for (int i = 0; i < size; i++) {
		if ((sp + i)->grade > 4.0 && (sp + i)->english > 900) {
			printf("%s", (sp + 1)->name);
			printf("%lf", (sp + 1)->grade);
			printf("%d", (sp + 1)->english);
		}
	}
}

#define INCREASING  1 //컴퓨터가 그냥 숫자 1로 이해함 내가 오름차순으로 코드 작성해줌
#define DECREASING  2 //내림차순

#define NAME        1
#define GRADE          2
#define ENGLISH      3

void exer5() {
	STUDENT stu[5] = { {0x00,}, };

	for (int i = 0; i < sizeof(stu) / sizeof(STUDENT); i++) {
		scanf("%s", stu[i].name);
		scanf("%lf", &stu[i].grade);
		scanf("%d", &stu[i].english);
	}

	for (int i = 0; i < sizeof(stu) / sizeof(STUDENT); i++) {
		frintf("%s", stu[i].name);
		frintf("%lf", stu[i].grade);
		frintf("%d", stu[i].english);
	}	
	insertion(stu, sizeof(stu) / sizeof(STUDENT), INCREASING, NAME);
	insertion(stu, sizeof(stu) / sizeof(STUDENT), INCREASING, GRADE);
	insertion(stu, sizeof(stu) / sizeof(STUDENT), INCREASING, ENGLISH);

	for (int i = 0; i < sizeof(stu) / sizeof(STUDENT); i++) {
		frintf("%s", stu[i].name);
		frintf("%lf", stu[i].grade);
		frintf("%d", stu[i].english);
	}

}

void insertion(STUDENT data[], int size, int dir, int type)
{
	int i, j;
	STUDENT key;
	
	if (dir == INCREASING)
	{
		for (i = 0; i < size; i++)
		{
			key = data[i];
			for (j = 0; j < size; j++)
			{
				if (type == NAME)
				{
					if (strcmp(data[j].name, key.name) <= 0) {
						break;
					}
				}
				else if (type == GRADE)
					{
						if (data[j].grade <= key.grade) 
						{
							break;
						}
					}

				else if (type == ENGLISH)
					{
						if (data[j].english <= key.english) 
						{
							break;
						}
					}
					data[j + 1] = data[j];
				}
				data[j + 1] = key;
			}
		}
	/*
	else if (dir == DECREASING)
	{
		for (i = 0; i < size; i++)
		{
			key = data[i];
			for (j = 0; j < size; j++)
			{
				if (type == NAME)
				{
					if (strcmp(data[j].name, key.name) >= 0) {
						break;
					}
				}
				else if (type == GRADE)
				{
					if (data[j].grade >= key.grade)
					{
						break;
					}
				}

				else if (type == ENGLISH)
				{
					if (data[j].english >= key.english)
					{
						break;
					}
				}
				data[j + 1] = data[j];
			}
			data[j + 1] = key;
		}
	}*/

}

void exer6() 
{
	STUDENT stu[5] = { {0x00,}, };
	STUDENT *stuPtr[5] = { 0x00, };

	for (int i = 0; i < sizeof(stu) / sizeof(STUDENT); i++) 
	{
		stuPtr[i] = &stu[i]; //주소값 대입
	}
	for (int i = 0; i < sizeof(stu) / sizeof(STUDENT); i++) {
		scanf("%s", stuPtr[i]->name);
		scanf("%lf", &(stuPtr[i]->grade));
		scanf("%d", &(stuPtr[i]->english));
	}

	for (int i = 0; i < sizeof(stu) / sizeof(STUDENT); i++) {
		frintf("%s", stuPtr[i]->name);
		frintf("%lf", stuPtr[i]->grade);
		frintf("%d", stuPtr[i]->english);
	}

	insortion2(stuPtr, sizeof(stu) / sizeof(STUDENT), INCREASING, NAME);
	insortion2(stuPtr, sizeof(stu) / sizeof(STUDENT), INCREASING, GRADE);
	insortion2(stuPtr, sizeof(stu) / sizeof(STUDENT), INCREASING, ENGLISH);
}

void insortion2(STUDENT* data[], int size, int dir, int type)
{
	int i, j;
	STUDENT* key;

	if (dir == INCREASING)
	{
		for (i = 0; i < size; i++)
		{
			key = data[i];

			for (j = i - 1; j >= 0; j--)
			{
				if (type == NAME)
				{
					if (strcmp(data[j]->name, key->name) <= 0) {
						break;
					}
				}
				else if (type == GRADE)
				{
					if (data[j]->grade <= key->grade)
					{
						break;
					}
				}

				else if (type == ENGLISH)
				{
					if (data[j]->english <= key->english)
					{
						break;
					}
				}
				data[j + 1] = data[j];
			}
			data[j + 1] = key;
		}
	}
	
	else if (dir == DECREASING)
	{
		for (i = 0; i < size; i++)
		{
			key = data[i];
			for (j = i - 1; j >= 0; j--)
			{
				if (type == NAME)
				{
					if (strcmp(data[j]->name, key->name) >= 0) {
						break;
					}
				}
				else if (type == GRADE)
				{
					if (data[j]->grade >= key->grade)
					{
						break;
					}
				}

				else if (type == ENGLISH)
				{
					if (data[j]->english >= key->english)
					{
						break;
					}
				}
				data[j + 1] = data[j];
			}
			data[j + 1] = key;
		}
	}

}

//실습 1

#pragma once

//void week1_example_1() {
//
//	STUDENT stu1 = {"Seogchung Seo", 2019015,"Security", 38,"Seoul"};
//	STUDENT stu2 = {"Steve Jobs", 2019016,"iPhone", 60,"New York"};
//	
//	printf("학생1 이름 입력 : "); // int name
//	scanf("%s", stu1.name);
//
//	printf("학생1 ID 입력 : "); // int id
//	scanf("%d", &stu1.id);
//
//	printf("학생1 전공입력 : "); // char major 배열
//	scanf("%s", stu1.major);
//
//	printf("학생1 나이입력 : "); // int age
//	scanf("%d", &stu1.age);
//
//	printf("학생1 주소입력 : "); // char addr 배열
//	scanf("%s", stu1.addr);
//
//	printf("\n");
//
//	printf("학생2 이름 입력 : "); // int name
//	scanf("%s", stu2.name);
//
//	printf("학생2 ID 입력 : "); // int id
//	scanf("%d", &stu2.id);
//
//	printf("학생2 전공입력 : "); // char major 배열
//	scanf("%s", stu2.major);
//
//	printf("학생2 나이입력 : "); // int age
//	scanf("%d", &stu2.age);
//
//	printf("학생2 주소입력 : "); // char addr 배열
//	scanf("%s", &stu2.addr);
//
//	printf("\n");
//
//	printf("학생1 이름 : %s\n", stu1.name); // int name
//	printf("학생1 ID : %d\n", stu1.id); // int id
//	printf("학생1 전공: %s\n", stu1.major); // char major 배열
//	printf("학생1 나이: %d\n", stu1.age); // int age
//	printf("학생1 주소: %s\n", stu1.addr); // char addr 배열
//
//	printf("\n");
//
//	printf("학생2 이름 : %s\n", stu2.name); // int name
//	printf("학생2 ID : %d\n", stu2.id); // int id
//	printf("학생2 전공: %s\n", stu2.major); // char major 배열
//	printf("학생2 나이: %d\n", stu2.age); // int age
//	printf("학생주소: %s\n", stu2.addr); // char addr 배열
//
//	stu1.age = 20;
//
//	printf("학생 이름 : %s\n", stu1.name); // int name
//	printf("학생 ID : %d\n", stu1.id); // int id
//	printf("학생전공: %s\n", stu1.major); // char major 배열
//	printf("학생나이: %d\n", stu1.age); // int age
//	printf("학생주소: %s\n", stu1.addr); // char addr 배열
//
//	printf("\n");
//
//	printf("학생 이름 : %s\n", stu2.name); // int name
//	printf("학생 ID : %d\n", stu2.id); // int id
//	printf("학생전공: %s\n", stu2.major); // char major 배열
//	printf("학생나이: %d\n", stu2.age); // int age
//	printf("학생주소: %s\n", stu2.addr); // char addr 배열
//
//	stu1.age = 20;
//}

 //실습 2

//void week1_example_2() {
//
//	typedef struct _PROFILE_ {
//		char name[32];
//		int age;
//		double height;
//	} PROFILE;
//
//	typedef struct _STUDENT_ {
//		PROFILE pf; //이름을 정해주고 호출
//		int id;
//		double grade;
//	}STUDENT;
//
//	STUDENT s1, s2;
//
//	/*STUDENT stu1 = {"Seogchung Seo", 2019015,"Security", 38,"Seoul"};
//	STUDENT stu2 = {"Steve Jobs", 2019016,"iPhone", 60,"New York"};
//	*/
//
//	printf("학생1 이름 입력 : "); // int name
//	scanf("%s", s1.pf.name);
//
//	printf("학생1 나이입력 : "); // int age
//	scanf("%d", &s1.pf.age);
//
//	printf("학생1 키입력 : "); // int age
//	scanf("%lf", &s1.pf.height);
//
//	printf("학생1 ID 입력 : "); // int id
//	scanf("%d", &s1.id);
//
//	printf("학생1 grade : "); // char major 배열
//	scanf("%lf", &s1.grade);
//
//	printf("\n");
//
//	printf("학생1 이름 : %s\n", s1.pf.name); // int name
//	printf("학생1 나이 : %d\n", s1.pf.age); // int id
//	printf("학생1 키 : %lf\n", s1.pf.height); // char major 배열
//	printf("학생1 ID : %d\n", s1.id); // int age
//	printf("학생1 grade : %lf\n", s1.grade); // char addr 배열
//}
//
////실습 3
//
//void week1_example_3() {
//	typedef struct STUDENT_ {
//		char name[32];
//		int id;
//		char major[32];
//		int age;
//		char addr[32];
//	} STUDENT;
//
//	STUDENT stu[3];
//	int cnt_i;
//
//	printf("[학생 정보 입력]");
//	for (cnt_i = 0; cnt_i < sizeof(stu) / sizeof(STUDENT); cnt_i++) {
//		printf("\n학생 %d 이름 입력 : \n", cnt_i + 1); // int name
//		scanf("%s", stu[cnt_i].name);
//
//		printf("\n학생 %d ID 입력 : \n", cnt_i + 1); // int id
//		scanf("%d", &stu[cnt_i].id);
//
//		printf("\n학생 %d 전공 입력 : \n", cnt_i + 1); // char major 배열
//		scanf("%s", stu[cnt_i].major);
//
//		printf("\n학생 %d 나이 입력 : \n", cnt_i + 1); // int age
//		scanf("%d", &stu[cnt_i].age);
//
//		printf("\n학생 %d 주소 입력 : \n", cnt_i + 1); // char addr 배열
//		scanf("%s", stu[cnt_i].addr);
//	}
//
//	printf("\n[학생 정보 입력]");
//
//	for (cnt_i = 0; cnt_i < sizeof(stu) / sizeof(STUDENT); cnt_i++) {
//		printf("\n학생 %d 이름 : %s\n", cnt_i + 1, stu[cnt_i].name); // int name
//		printf("\n학생 %d ID : %d\n", cnt_i + 1, stu[cnt_i].id); // int id
//		printf("\n학생 %d 전공 : %s\n", cnt_i + 1, stu[cnt_i].major); // char major 배열
//		printf("\n학생 %d 이름 : %d\n", cnt_i + 1, stu[cnt_i].age); // int age
//		printf("\n학생 %d 주소 : %s\n", cnt_i + 1, stu[cnt_i].addr); // char addr 배열
//	}
//
//	printf("\n");
//
//}
//
////실습 4
//
//typedef struct _PROFILE_ {
//	char name[32];
//	double grade;
//	int engilsh;
//}PROFILE; // PROFILE 이라는 구조체를 선언한
//
//// void로 불러와서 sp 라는 변수를 만들어서* 로 구조체에 저장하는거 int size는 나중에 이 함수를 사용할때 받아드릴 학생 수를 작성하는 공간으로 변수 선언
//void input_data(PROFILE* sp, int size)
//{
//	int i;
//
//	printf("이름 학점 영어점수 입력.\n");
//	for (i = 0; i < size; i++)
//	{
//		printf("%d-th 학생: \n", i + 1);
//		scanf("%s %lf %d", sp[i].name, &sp[i].grade, &sp[i].engilsh); //&연산자로 주소의 값 넘겨주기
//	}
//}
//
//void elite(PROFILE* sp, int size) {
//	int i;
//
//	printf("\n[elite student!]\n");
//	for (i = 0; i < size; i++)
//	{
//		if ((sp + i)->grade >= 4.0 && (sp + i)->engilsh >= 900) {
//			printf("%s%.1lf%d", sp[i].name, &sp[i].grade, &sp[i].engilsh);
//		}
//	}
//}
//
//void week1_example_4() {
//	PROFILE new_staff[5];
//
//	input_data(new_staff, 5);
//	elite(new_staff, 5);
//}
//
////실습 5
//
//#define INCREASING  1 //컴퓨터가 그냥 숫자 1로 이해함 내가 오름차순으로 코드 작성해줌
//#define DECREASING  2 //내림차순
//
//#define NAME        1
//#define ID          2
//#define HEIGHT      3
//
//typedef struct _STUDENT_ {
//	char name[32];
//	int id;
//	double height;
//}STUDENT;
//
//
//void insertionSort(STUDENT data[], int size, int dir, int type)
//{
//	int cnt_i, cnt_j;
//	STUDENT key;
//
//	if (dir == INCREASING)
//	{
//		for (cnt_i = 1; cnt_i < size; cnt_i++)
//		{
//			key = data[cnt_i];
//
//			//key보다 더 작은 값을 찾을 때까지 계속 수행 키는 가장 큰거부터 내려옴
//			for (cnt_j = cnt_i - 1; cnt_j >= 0; cnt_j--) {
//				if (type == NAME) { //이름은 strcmp 함수를 이용해 앞에서부터 한글자씩 아스키 코드 값으로 비교함
//					if (strcmp(data[cnt_j].name, key.name) <= 0) { 
//						break;
//					}
//				}
//				else if (type == ID)
//				{
//					if (data[cnt_j].id <= key.id) {
//						break;
//					}
//				}
//				else if (type == HEIGHT)
//				{
//					if (data[cnt_j].height <= key.height) {
//						break;
//					}
//				}
//
//				data[cnt_j + 1] = data[cnt_j];
//			} //name, id, height중 하나라도 그 전값도 작으면 밀어내고 새로 저장됨 따라서 오름차순
//			data[cnt_j + 1] = key;
//		}
//	}
//	else if (dir == DECREASING)
//	{
//		for (cnt_i = 1; cnt_i < size; cnt_i++)
//		{
//			key = data[cnt_i];
//
//			for (cnt_j = cnt_i - 1; cnt_j <= 0; cnt_j--) {
//				if (type == NAME) {
//					if (strcmp(data[cnt_j].name, key.name) <= 0) {
//						break;
//					}
//				}
//				else if (type == ID)
//				{
//					if (data[cnt_j].id <= key.id) {
//						break;
//					}
//				}
//				else if (type == HEIGHT)
//				{
//					if (data[cnt_j].height <= key.height) {
//						break;
//					}
//				}
//
//				data[cnt_j + 1] = data[cnt_j];
//			}
//			data[cnt_j + 1] = key;
//		}
//	}
//}
//
//void week1_example_5() {
//	STUDENT stu[5] = { {0x00, }, }; //첫번째 {}에서는 구조체 초기화 안쪽의 {}는 내부배열 초기화
//	int cnt_i;
//
//	printf("[학생 정보 입력]\n");
//	for (cnt_i = 0; cnt_i < sizeof(stu) / sizeof(STUDENT); cnt_i++)
//	{
//		printf("\n%d 번째 학생 이름 입력:\n", cnt_i);
//		scanf("%s", stu[cnt_i].name);
//		printf("%d 번째 학생 id 입력:\n", cnt_i);
//		scanf("%d", &stu[cnt_i].id);
//		printf("%d 번째 학생 height 입력:\n", cnt_i);
//		scanf("%lf", &stu[cnt_i].height);
//	}
//
//	printf("[학생 정보 출력]\n");
//	for (cnt_i = 0; cnt_i < sizeof(stu) / sizeof(STUDENT); cnt_i++)
//	{
//		printf("%d 번째 학생 이름: %s\n", cnt_i + 1, stu[cnt_i].name);
//		printf("%d 번째 학생 id: %d\n", cnt_i + 1, stu[cnt_i].id);
//		printf("%d 번째 학생 height: %lf\n", cnt_i + 1, stu[cnt_i].height);
//	}
//	printf("[이름 정렬]\n");
//	insertionSort(stu, sizeof(stu) / sizeof(STUDENT), INCREASING, NAME);
//	for (cnt_i = 0; cnt_i < sizeof(stu) / sizeof(STUDENT); cnt_i++)
//	{
//		printf("%d 번째 학생 이름: %s\n", cnt_i + 1, stu[cnt_i].name);
//		printf("%d 번째 학생 id: %d\n", cnt_i + 1, stu[cnt_i].id);
//		printf("%d 번째 학생 height: %lf\n", cnt_i + 1, stu[cnt_i].height);
//	}
//	printf("[id 정렬]\n");
//	insertionSort(stu, sizeof(stu) / sizeof(STUDENT), INCREASING, ID);
//	for (cnt_i = 0; cnt_i < sizeof(stu) / sizeof(STUDENT); cnt_i++)
//	{
//		printf("%d 번째 학생 이름: %s\n", cnt_i + 1, stu[cnt_i].name);
//		printf("%d 번째 학생 id: %d\n", cnt_i + 1, stu[cnt_i].id);
//		printf("%d 번째 학생 height: %lf\n", cnt_i + 1, stu[cnt_i].height);
//	}
//	printf("[height 정렬]\n");
//	insertionSort(stu, sizeof(stu) / sizeof(STUDENT), INCREASING, HEIGHT);
//	for (cnt_i = 0; cnt_i < sizeof(stu) / sizeof(STUDENT); cnt_i++)
//	{
//		printf("%d 번째 학생 이름: %s\n", cnt_i + 1, stu[cnt_i].name);
//		printf("%d 번째 학생 id: %d\n", cnt_i + 1, stu[cnt_i].id);
//		printf("%d 번째 학생 height: %lf\n", cnt_i + 1, stu[cnt_i].height);
//	}
//}
//
////실습 6
//
//void insertionSort2(STUDENT* data[], int size, int dir, int type)
//{
//	int cnt_i, cnt_j;
//	STUDENT* key;
//
//	if (dir == INCREASING)
//	{
//		for (cnt_i = 1; cnt_i < size; cnt_i++)
//		{
//			key = data[cnt_i];
//
//			//key보다 더 작은 값을 찾을 때까지 계속 수행
//			for (cnt_j = cnt_i - 1; cnt_j >= 0; cnt_j--) {
//				if (type == NAME) { //*로 주소값을 불러오기 때문에 ->로 주소 값에 저장함
//					if (strcmp(data[cnt_j]->name, key->name) <= 0) {
//						break;
//					}
//				}
//				else if (type == ID)
//				{
//					if (data[cnt_j]->id <= key->id) {
//						break;
//					}
//				}
//				else if (type == HEIGHT)
//				{
//					if (data[cnt_j]->height <= key->height) {
//						break;
//					}
//				}
//
//				data[cnt_j + 1] = data[cnt_j];
//			}
//			data[cnt_j + 1] = key;
//		}
//	}
//	else if (dir == DECREASING)
//	{
//		for (cnt_i = 1; cnt_i < size; cnt_i++)
//		{
//			key = data[cnt_i];
//
//			for (cnt_j = cnt_i - 1; cnt_j <= 0; cnt_j--) {
//				if (type == NAME) {
//					if (strcmp(data[cnt_j]->name, key->name) <= 0) {
//						break;
//					}
//				}
//				else if (type == ID)
//				{
//					if (data[cnt_j]->id <= key->id) {
//						break;
//					}
//				}
//				else if (type == HEIGHT)
//				{
//					if (data[cnt_j]->height <= key->height) {
//						break;
//					}
//				}
//
//				data[cnt_j + 1] = data[cnt_j];
//			}
//			data[cnt_j + 1] = key;
//		}
//	}
//}
//
//
//void week1_example_6()
//{
//	STUDENT stu[5] = { { 0x00, }, };
//	STUDENT *stuPtr[5] = { 0x00, };
//	int cnt_i;
//
//	for (cnt_i = 0; cnt_i < sizeof(stu) / sizeof(STUDENT); cnt_i++)
//	{
//		stuPtr[cnt_i] = &stu[cnt_i];
//	}
//	printf("[학생 정보 입력]\n");
//	for (cnt_i = 0; cnt_i < sizeof(stu) / sizeof(STUDENT); cnt_i++)
//	{
//		printf("\n%d 번째 학생 이름 입력:\n", cnt_i);
//		scanf("%s", stuPtr[cnt_i]->name);
//		printf("%d 번째 학생 id 입력:\n", cnt_i);
//		scanf("%d", &(stuPtr[cnt_i])->id);
//		printf("%d 번째 학생 height 입력:\n", cnt_i);
//		scanf("%lf", &(stuPtr[cnt_i])->height);
//	}
//
//	printf("[학생 정보 출력]\n");
//	for (cnt_i = 0; cnt_i < sizeof(stu) / sizeof(STUDENT); cnt_i++)
//	{
//		printf("%d 번째 학생 이름: %s\n", cnt_i + 1, stuPtr[cnt_i]->name);
//		printf("%d 번째 학생 id: %d\n", cnt_i + 1, stuPtr[cnt_i]->id);
//		printf("%d 번째 학생 height: %lf\n", cnt_i + 1, stuPtr[cnt_i]->height);
//	}
//
//	printf("[이름 정렬]\n");
//	insertionSort(stuPtr, sizeof(stu) / sizeof(STUDENT), INCREASING, NAME);
//	for (cnt_i = 0; cnt_i < sizeof(stu) / sizeof(STUDENT); cnt_i++)
//	{
//		printf("%d 번째 학생 이름: %s\n", cnt_i + 1, stuPtr[cnt_i]->name);
//		printf("%d 번째 학생 id: %d\n", cnt_i + 1, stuPtr[cnt_i]->id);
//		printf("%d 번째 학생 height: %lf\n", cnt_i + 1, stuPtr[cnt_i]->height);
//	}
//	printf("[id 정렬]\n");
//	insertionSort(stuPtr, sizeof(stu) / sizeof(STUDENT), INCREASING, ID);
//	for (cnt_i = 0; cnt_i < sizeof(stu) / sizeof(STUDENT); cnt_i++)
//	{
//		printf("%d 번째 학생 이름: %s\n", cnt_i + 1, stuPtr[cnt_i]->name);
//		printf("%d 번째 학생 id: %d\n", cnt_i + 1, stuPtr[cnt_i]->id);
//		printf("%d 번째 학생 height: %lf\n", cnt_i + 1, stuPtr[cnt_i]->height);
//	}
//	printf("[height 정렬]\n");
//	insertionSort(stuPtr, sizeof(stu) / sizeof(STUDENT), INCREASING, HEIGHT);
//	for (cnt_i = 0; cnt_i < sizeof(stu) / sizeof(STUDENT); cnt_i++)
//	{
//		printf("%d 번째 학생 이름: %s\n", cnt_i + 1, stuPtr[cnt_i]->name);
//		printf("%d 번째 학생 id: %d\n", cnt_i + 1, stuPtr[cnt_i]->id);
//		printf("%d 번째 학생 height: %lf\n", cnt_i + 1, stuPtr[cnt_i]->height);
//	}
//}


int main() {
	week1();

	//week1_example_1();

	//week1_example_2();

	//week1_example_3();

	//week1_example_4();
	
	//week1_example_5();

	//week1_example_6();
	
	return 0;
}


