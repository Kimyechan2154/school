#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <crtdbg.h>			// 메모리 누수를 확인하기 위해 CRT 디버그 함수 사용


#define MAX_STUDENT	10

typedef struct _STUDENT_ {
	char name[32];
	int age;
}STUDENT;

typedef struct _STUDENT_LIST_ {
	STUDENT list[MAX_STUDENT]; //10 넣은거
	int numOfStudents;
}STUDENT_LIST;

/*
 * @brief list에 들어있는 학생 수 출력
 */
int getNumStudents(STUDENT_LIST* stuList)
{//stuList가 numOfStudents의 주소를 가르킴
	return stuList->numOfStudents;
}

/*
 * @brief list에 들어있는 학생정보 출력
 */
void printStudents(STUDENT_LIST* stuList)
{
	int cnt_i;

	printf("\nPrint students list\n");
	for (cnt_i = 0; cnt_i < stuList->numOfStudents; cnt_i++)
	{
		printf("%d-th student: %s, %d\n", cnt_i, stuList->list[cnt_i].name, stuList->list[cnt_i].age);
	}
}

/*
 * @brief list의 시작위치에 학생 정보 삽입
 */
void addStudentAtStart(STUDENT_LIST* stuList, STUDENT* student)
{
	int cnt_i;

	if (MAX_STUDENT <= stuList->numOfStudents)
	{
		fprintf(stderr, "Error, too many students\n");
		return;
	}
	else
	{
		for (cnt_i = stuList->numOfStudents - 1; cnt_i >= 0; cnt_i--)
		{
			stuList->list[cnt_i + 1] = stuList->list[cnt_i];
		}
		stuList->list[0] = *student;
		stuList->numOfStudents += 1;
	}
}

/*
 * @brief list의 마지막 위치에 학생정보 삽입
 */
void addStudentAtLast(STUDENT_LIST* stuList, STUDENT* student)
{

	if (MAX_STUDENT <= stuList->numOfStudents)
	{
		fprintf(stderr, "Error, too many students\n");
		return;
	}
	else
	{/*stuList->numOfStudents 현재 학생수 그래서 다음 순번이 들어갈 수 있게됨
	  *student 새학생의 데이터*/
		stuList->list[stuList->numOfStudents] = *student;
		stuList->numOfStudents += 1;
	}
}

/*
 * @brief list의 중간위치에 학생 정보 삽입
 */
void addStudentAtMiddle(STUDENT_LIST* stuList, int pos, STUDENT* student)
{
	int cnt_i;

	if (MAX_STUDENT <= stuList->numOfStudents)
	{
		fprintf(stderr, "Error, too many students\n");
		return;
	}
	else
	{//pos 전까지만 이전 값들을 미뤄주고 나머지 코드 작성
		for (cnt_i = stuList->numOfStudents - 1; cnt_i >= pos; cnt_i--)
		{

			stuList->list[cnt_i + 1] = stuList->list[cnt_i];
		}
		stuList->list[pos] = *student;
		stuList->numOfStudents += 1;
	}
}

/*
 * @brief list의 시작위치에 있는 학생정보 삭제
 */
void deleteStudentAtStart(STUDENT_LIST* stuList)
{
	int cnt_i;

	//0이하로는 안떨어지게
	if (stuList->numOfStudents > 0)
	{
		for (cnt_i = 0; cnt_i < stuList->numOfStudents - 1; cnt_i++)
		{
			stuList->list[cnt_i] = stuList->list[cnt_i + 1];
		}
		memset(&(stuList->list[stuList->numOfStudents - 1]), 0, sizeof(STUDENT));
		stuList->numOfStudents -= 1;
	}
	else
	{
		fprintf(stderr, "Error, there are no students\n");
		return;
	}
}

/*
 * @brief list의 마지막 위치에 있는 학생 정보 삭제
 */
void deleteStudentAtLast(STUDENT_LIST* stuList)
{
	if (stuList->numOfStudents > 0)
	{
		memset(&(stuList->list[stuList->numOfStudents - 1]), 0, sizeof(STUDENT));
		stuList->numOfStudents -= 1;
	}
	else
	{
		fprintf(stderr, "Error, there are no students\n");
		return;
	}
}

/*
 * @brief list의 중간위치에 있는 학생 정보 삭제
 */
void deleteStudentAtMiddle(STUDENT_LIST* stuList, int pos)
{
	int cnt_i;

	//0이하로는 안떨어지게
	if (stuList->numOfStudents > 0)
	{
		for (cnt_i = pos; cnt_i < stuList->numOfStudents - 1; cnt_i++)
		{
			stuList->list[cnt_i] = stuList->list[cnt_i + 1];
		}	
		memset(&(stuList->list[stuList->numOfStudents - 1]), 0, sizeof(STUDENT));
		stuList->numOfStudents -= 1;
	}
	else
	{
		fprintf(stderr, "Error, there are no students\n");
		return;
	}
}

/*
 * @brief list에 들어있는 학생 정보를 파일에 출력
 */
void storeListAtFile(char* fileName, STUDENT_LIST* stuList)
{
	int cnt_i;
	FILE* fp = NULL;

	fp = fopen(fileName, "wb");
	assert(fp != NULL);

	printf("Storing a list at file %s\n", fileName);

	// 필요한 정보만 저장하는 방법
	fwrite(&(stuList->numOfStudents), sizeof(int), 1, fp);
	for (cnt_i = 0; cnt_i < stuList->numOfStudents; cnt_i++)
	{
		fwrite(&(stuList->list[cnt_i]), sizeof(STUDENT), 1, fp);
	}

	if (fp != NULL)
	{
		fclose(fp);
	}
}

/*
 * @brief 파일로 부터 학생 정보를 가져와 list에 저장
 */
void restoreListAtFile(char* fileName, STUDENT_LIST* stuList)
{
	int cnt_i = 0;
	int numStudents = 0;
	FILE* fp = NULL;

	fp = fopen(fileName, "rb");
	assert(fp != NULL);

	printf("Reading a list at file %s\n", fileName);

	fread(&(stuList->numOfStudents), sizeof(int), 1, fp);
	for (cnt_i = 0; cnt_i < stuList->numOfStudents; cnt_i++)
	{
		fread(&(stuList->list[cnt_i]), sizeof(STUDENT), 1, fp);
	}

	if (fp != NULL)
	{
		fclose(fp);
	}
}

/*
 * 선형리스트 테스트 함수
 */
void exec1_linearList()
{
	char buf;
	int sel;
	int cnt_i = 0;
	STUDENT_LIST stuList;
	STUDENT_LIST readStuList;
	STUDENT student = { {0x00, }, };

	memset(&stuList, 0, sizeof(STUDENT_LIST));

	// 학생 3명에 대한 정보 추가
	printf("Input three students information\n\n");
	for (cnt_i = 0; cnt_i < 3; cnt_i++)
	{
		printf("Input %d student info(name, age)\n", cnt_i);
		scanf("%s%d%c", stuList.list[cnt_i].name, &stuList.list[cnt_i].age, &buf);
		//numOfStudents의 숫자를 3으로 정해줌
		stuList.numOfStudents += 1;
	}
	printStudents(&stuList);

	// 리스트의 시작 위치에 새로운 학생 정보 추가
	printf("\nInput a student information at start\n");
	scanf("%s%d%c", student.name, &student.age, &buf);
	addStudentAtStart(&stuList, &student);
	printStudents(&stuList);

	// 리스트의 끝 위치에 새로운 학생 정보 추가
	printf("\nInput a student information at last\n");
	scanf("%s%d%c", student.name, &student.age, &buf);
	addStudentAtLast(&stuList, &student);
	printStudents(&stuList);

	// 리스트의 중간 위치에 새로운 학생 정보 추가
	printf("\nInput a student information\n");
	scanf("%s%d%c", student.name, &student.age, &buf);
	addStudentAtMiddle(&stuList, 3, &student);
	printStudents(&stuList);

	// 리스트의 시작 위치에 있는 학생 정보 삭제
	printf("\nDelete a student information at start\n");
	getchar();
	deleteStudentAtStart(&stuList);
	printStudents(&stuList);

	// 리스트의 끝 위치에 있는 학생 정보 삭제
	printf("\nDelete a student information at last\n");
	getchar();
	deleteStudentAtLast(&stuList);
	printStudents(&stuList);

	// 리스트의 중간 위치에 있는 학생 정보 삭제
	printf("\nDelete a student information at middle\n");
	getchar();
	deleteStudentAtMiddle(&stuList, 1);
	printStudents(&stuList);

	// 원하는 위치에 학생 정보를 삽입해보자
	do {
		printf("\nInput a student information\n");
		scanf("%s%d%c", student.name, &student.age, &buf);
		printf("Which position do you insert it(0~%d, -1: for exit)\n", getNumStudents(&stuList));		// 이렇게 한 이유는 마지막 위치에 집어 넣는 경우도 포함하고자 한 것임
		scanf("%d%c", &sel, &buf);
		if (sel != -1)
		{
			addStudentAtMiddle(&stuList, sel, &student);
			printStudents(&stuList);
		}
	} while (sel != -1);

	// 원하는 위치에 학생 정보를 삭제해보자
	do {
		scanf("%d%c", &sel, &buf);
		if (sel != -1)
		{
			deleteStudentAtMiddle(&stuList, sel);
			printStudents(&stuList);
		}
	} while (sel != -1);

	storeListAtFile("stdList.dat", &stuList);
	restoreListAtFile("stdList.dat", &readStuList);
	printStudents(&readStuList);
}

//실습 2


#define MAXSTRLEN	16

//------------------------------------------------------------
// Week5_exer1
//------------------------------------------------------------
// 단순 연결 리스트의 노드 구조를 구조체로 정의
typedef struct _LISTNODE_ {
	char data[MAXSTRLEN];
	struct _LISTNODE_* link;
} listNode;

// 리스트의 시작을 나타내는 head 노드를 구조체로 정의
typedef struct _LINKEDLIST_H_ {
	listNode* head;
} linkedList_h;

// 공백 연결 리스트를 생성하는 연산
linkedList_h* createLinkedList_h(void) {
	linkedList_h* L;
	L = (linkedList_h*)calloc(1, sizeof(linkedList_h));
	L->head = NULL;		// 공백 리스트이므로 NULL로 설정
	return L;
}

/*
 * 리스트를 순회하며 메모리 반환
 */
void freeLinkedList_h(linkedList_h* L) {
	listNode* p;

	if (L != NULL)
	{
		while (L->head != NULL) {
			p = L->head;
			L->head = L->head->link;
			free(p);
			p = NULL;
		}
		L->head = NULL;		// 리스트의 head 포인터 초기화
	}
	else
	{
		fprintf(stderr, "error: NULL list\n");
		return;
	}
}

// 연결 리스트를 순서대로 출력하는 연산
void printList(linkedList_h* L) {
	listNode* p;
	printf("L = (");
	p = L->head;
	while (p != NULL) {
		printf("%s", p->data);
		p = p->link;
		if (p != NULL) printf(", ");
	}
	printf(") \n");
}

// 첫 번째 노드로 삽입하는 연산
void insertFirstNode(linkedList_h* L, char* x) {
	listNode* newNode;
	newNode = (listNode*)malloc(sizeof(listNode));	// 삽입할 새 노드 할당
	strcpy(newNode->data, x);						// 새 노드의 데이터 필드에 x 저장  
	newNode->link = L->head;
	L->head = newNode;
}

// key 값을 이용하여 오름차순 정렬하여 리스트에 연결
void orderedInsert(linkedList_h* L, char* x)
{
	listNode* pre = NULL;
	listNode* cur = NULL;
	listNode* newNode = NULL;

	newNode = (listNode*)malloc(sizeof(listNode));	// 삽입할 새 노드 할당
	strncpy(newNode->data, x, MAXSTRLEN);
	newNode->link = NULL;

	pre = cur = L->head;

	if (cur == NULL)
	{
		L->head = newNode;
		return;
	}
	else if (cur != NULL)	// 첫번째 노드인 head 노드와 비교
	{
		if (strncmp(cur->data, x, MAXSTRLEN) > 0)	// x보다 더 큰 데이터를 가진 노드를 만나면 break
		{
			newNode->link = cur;
			L->head = newNode;
			return;
		}
	}

	// 두번째 노드부터 비교 수행
	cur = cur->link;
	while (cur != NULL)
	{
		if (strncmp(cur->data, x, MAXSTRLEN) > 0)	// x보다 더 큰 데이터를 가진 노드를 만나면 break
		{
			break;
		}
		pre = cur;			// 이전 노드 정보
		cur = cur->link;	// 다음 노드 정보 접근
	}
	newNode->link = pre->link;
	pre->link = newNode;
}

// 노드를 pre 뒤에 삽입하는 연산
void insertMiddleNode(linkedList_h* L, listNode* pre, char* x) {
	listNode* newNode;

	newNode = (listNode*)malloc(sizeof(listNode));
	strcpy(newNode->data, x);

	if (L->head == NULL) {			// 공백 리스트인 경우
		newNode->link = NULL;		// 새 노드를 첫 번째이자 마지막 노드로 연결
		L->head = newNode;
	}
	else if (pre == NULL) {			// 삽입 위치를 지정하는 포인터 pre가 NULL인 경우
		newNode->link = L->head;
		L->head = newNode;			// 새 노드를 첫 번째 노드로 삽입
	}
	else {
		newNode->link = pre->link;	// 포인터 pre의 노드 뒤에 새 노드 연결
		pre->link = newNode;
	}
}

// 마지막 노드로 삽입하는 연산 
void insertLastNode(linkedList_h* L, char* x) {
	listNode* newNode;
	listNode* temp;
	newNode = (listNode*)malloc(sizeof(listNode));
	strcpy(newNode->data, x);
	newNode->link = NULL;
	if (L->head == NULL) {		// 현재 리스트가 공백인 경우					
		L->head = newNode;		// 새 노드를 리스트의 시작 노드로 연결
		return;
	}
	// 현재 리스트가 공백이 아닌 경우 	
	temp = L->head;
	while (temp->link != NULL) temp = temp->link;	// 현재 리스트의 마지막 노드를 찾음
	temp->link = newNode;							// 새 노드를 마지막 노드(temp)의 다음 노드로 연결 
}

// 리스트에서 노드 p를 삭제하는 연산
void deleteNode(linkedList_h* L, listNode* p) {
	// codes..
}

// 리스트에서 x 노드를 탐색하는 연산
listNode* searchNode(linkedList_h* L, char* x) {
	listNode* temp;
	temp = L->head;
	while (temp != NULL) {
		if (strcmp(temp->data, x) == 0) return temp;
		else temp = temp->link;
	}
	return temp;
}

void exec2_list()
{
	linkedList_h* L;
	linkedList_h* L2;
	linkedList_h* L3;
	listNode* p;

	L = createLinkedList_h();		// 공백 리스트 생성
	L2 = createLinkedList_h();		// 공백 리스트 생성
	L3 = createLinkedList_h();		// 공백 리스트 생성

	printf("\n(1) 리스트에 머리에 노드 삽입하기! \n");
	insertFirstNode(L, "apple");
	insertFirstNode(L, "banana");
	insertFirstNode(L, "cat");
	printList(L);

	printf("\n(2) 리스트에 꼬리에 노드 삽입하기! \n");
	insertLastNode(L2, "apple");
	insertLastNode(L2, "banana");
	insertLastNode(L2, "cat");
	printList(L2);
	getchar();

	printf("\n(3) 리스트에서 노드 탐색하기! \n");
	p = searchNode(L, "banana");
	if (p == NULL) printf("찾는 데이터가 없습니다.\n");
	else printf("[%s]를 찾았습니다.\n", p->data);

	insertMiddleNode(L, p, "test");

	p = searchNode(L, "test");
	if (p == NULL) printf("찾는 데이터가 없습니다.\n");
	else printf("[%s]를 찾았습니다.\n", p->data);

	printf("\n(4) 리스트에서 중간에 노드 삽입하기! \n");
	insertMiddleNode(L, p, "zero");
	printList(L);

	// codes.. 

	freeLinkedList_h(L);		// 리스트의 메모리 해제
	if (L != NULL)
	{
		free(L);
	}

	freeLinkedList_h(L2);		// 리스트의 메모리 해제
	if (L2 != NULL)
	{
		free(L2);
	}

	freeLinkedList_h(L3);		// 리스트의 메모리 해제
	if (L3 != NULL)
	{
		free(L3);
	}

	getchar();
}

void main()
{
	exec2_list();
}
void main()
{
	exec1_linearList();

	exec2_list();
}
