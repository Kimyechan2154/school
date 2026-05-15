#include <stdio.h>
#include <stdlib.h>

#define TRUE	1
#define FALSE	0

#define Q_SIZE 10


//typedef int element;		// 큐 원소(element)의 자료형을 int로 정의
//typedef struct {
//	element queue[Q_SIZE];	// 1차원 배열 큐 선언
//	int front, rear;		// 삽입, 삭제를 위한 위치 변수
//} QueueType;
//
//// 공백 순차 큐를 생성
//QueueType* createQueue()
//{
//	QueueType* Q;
//	Q = (QueueType*)calloc(1, sizeof(QueueType));
//	Q->front = -1;	// front 초기 설정
//	Q->rear = -1;	// rear 초기 설정
//	return Q;
//}
//
//// 순차 큐가 포화상태인지 검사
//int isFull(QueueType* Q)
//{
//	if (Q->rear == Q_SIZE - 1) {
//		printf("Queue is full!\n");
//		return TRUE;
//	}
//	else {
//		return FALSE;
//	}
//}
//
//// 순차 큐가 공백상태인지 검사
//int isEmpty(QueueType* Q)
//{
//	if (Q->front == Q->rear) {
//		printf("Queue is empty!\n");
//		return TRUE;
//	}
//	else
//	{
//		return FALSE;
//	}
//}
//
//// 순차 큐의 rear에 원소 삽입
//void enQueue(QueueType* Q, element item)
//{
//	if (isFull(Q)) return;
//	else {
//		Q->rear++; //rear 숫자 증가
//		Q->queue[Q->rear] = item; //값을 삽입하는거라 리턴 값이 없어도 됨
//	}
//}
//
//// 순차 큐의 front에서 원소를 삭제
//element deQueue(QueueType* Q)
//{
//	if (isEmpty(Q)) return;
//	else {
//		Q->front++;
//		return 	Q->queue[Q->front + 1];
//	}
//}
//
//// 순차 큐의 가장 앞에 있는 원소를 검색
//element peek(QueueType* Q) {
//	if (isEmpty(Q)) return;
//	else {
//		return Q->queue[Q->front + 1];
//	}
//}
//
//void printQ(QueueType* Q) {
//	int i;
//	printf("Queue: (front: %d), rear: %d)[", Q->front, Q->rear);
//	for (i = Q->front + 1; i <= Q->rear; i++)
//	{
//		printf("%d, ", Q->queue[i]);
//	}
//	printf("]\n");
//}
//
//int main()
//{
//	int cnt_i;
//	QueueType* Q = createQueue();		// 큐생성
//	QueueType* Q2 = createQueue();		// 큐생성
//	element data;
//
//	printf("[큐 삽입]\n");
//	for (cnt_i = 0; cnt_i < 11; cnt_i++)
//	{
//		printf("%d 삽입\n", cnt_i);
//		enQueue(Q, cnt_i);
//		printQ(Q);
//	}
//
//	data = peek(Q);
//	printf("\nFirst item in Queue: %d\n", data);
//
//	printf("\n[큐 삭제]\n");
//	for (cnt_i = 0; cnt_i < 11; cnt_i++)
//	{
//		data = deQueue(Q);
//		printf("%d 삭제\n", data);
//		printQ(Q);
//	}
//
//	printf("\n[거짓포화]\n");
//	for (cnt_i = 0; cnt_i < 11; cnt_i++)
//	{
//		printf("enQueue: ");
//		enQueue(Q2, cnt_i);
//		printQ(Q2);
//
//		printf("deQueue: ");
//		deQueue(Q2);
//		printQ(Q2);
//	}
//
//	getchar();
//}
//
//// EOF 
//
//
//typedef int element;		// 큐 원소(element)의 자료형을 int로 정의
//typedef struct {
//	element queue[Q_SIZE];	// 1차원 배열 큐 선언
//	int front, rear;
//} QueueType;
//
//QueueType* createQueue() {
//	QueueType* CQ;
//	CQ = (QueueType*)calloc(1, sizeof(QueueType));
//	CQ->front = 0;       // front 초깃값 설정
//	CQ->rear = 0;        // rear 초깃값 설정
//	return CQ;
//}
//
//// 원형 큐가 공백 상태인지 검사
//int isEmpty(QueueType* CQ) {
//	if (CQ->front == CQ->rear) {
//		printf(" Circular Queue is empty! ");
//		return 1;
//	}
//	else return 0;
//}
//
//// 원형 큐가 포화 상태인지 검사
//int isFull(QueueType* CQ) {
//	if (((CQ->rear + 1) % Q_SIZE) == CQ->front) {
//		printf("  Circular Queue is full! ");
//		return 1;
//	}
//	else return 0;
//}
//
//// 원형 큐의 rear에 원소를 삽입
//void enQueue(QueueType* CQ, element item) {
//	if (isFull(CQ))	return;
//	else {
//		CQ->rear = (CQ->rear + 1) % Q_SIZE;
//		CQ->queue[CQ->rear] = item;
//	}
//}
//
//// 원형 큐의 front에서 원소를 삭제/반환
//element deQueue(QueueType* CQ) {
//	if (isEmpty(CQ)) return;
//	else {
//		CQ->front = (CQ->front + 1) % Q_SIZE;
//		return CQ->queue[CQ->front];
//	}
//}
//
//// 원형 큐의 가장 앞에 있는 원소를 검색하는 연산
//element peek(QueueType* CQ) {
//	if (isEmpty(CQ)) exit(1);
//	else return CQ->queue[(CQ->front + 1) % Q_SIZE];
//}
//
//// 원형 큐의 원소를 출력
//void printQ(QueueType* CQ) {
//	int i, first, last;
//	first = (CQ->front + 1) % Q_SIZE;
//	last = (CQ->rear + 1) % Q_SIZE;
//
//	printf("Circular Queue: (front: %d), rear: %d)[", CQ->front, CQ->rear);
//	i = first;
//	while (i != last) {
//		printf("%d, ", CQ->queue[i]);
//		i = (i + 1) % Q_SIZE;
//	}
//	printf(" ] \n");
//}
//
//int main()
//{
//	int cnt_i;
//	QueueType* Q = createQueue();		// 큐생성
//	QueueType* Q2 = createQueue();		// 큐생성
//	element data;
//
//	printf("[큐 삽입]\n");
//	for (cnt_i = 0; cnt_i < 11; cnt_i++)
//	{
//		printf("%d 삽입\n", cnt_i);
//		enQueue(Q, cnt_i);
//		printQ(Q);
//	}
//
//	data = peek(Q);
//	printf("\nFirst item in Queue: %d\n", data);
//
//	printf("\n[큐 삭제]\n");
//	for (cnt_i = 0; cnt_i < 10; cnt_i++)
//	{
//		data = deQueue(Q);
//		printf("%d 삭제\n", data);
//		printQ(Q);
//	}
//
//	printf("\n[거짓포화]\n");
//	for (cnt_i = 0; cnt_i < 10; cnt_i++)
//	{
//		printf("enQueue: ");
//		enQueue(Q2, cnt_i);
//		printQ(Q2);
//
//		printf("deQueue: ");
//		deQueue(Q2);
//		printQ(Q2);
//	}
//
//	getchar();
//	return 0;
//}

// EOF

//연결리스트 큐 구현 포화상태가 없다.

typedef int element;// 큐 원소(element)의 자료형을 int로 정의

typedef struct _QNODE_ {
	element data;	// 1차원 배열 큐 선언
	struct _QNODE_* link;
} QNODE;

typedef struct _TYPE_ {
	QNODE*front, *rear;
} TYPE;

TYPE* createQueue() {
	TYPE* CQ;
	CQ = (TYPE*)calloc(1, sizeof(TYPE));
	CQ->front = 0;       // front 초깃값 설정
	CQ->rear = 0;        // rear 초깃값 설정
	return CQ;
}

// 원형 큐가 공백 상태인지 검사
int isEmpty(TYPE* CQ) {
	if (CQ->front == NULL) {
		printf(" Circular Queue is empty! ");
		return 1;
	}
	else return 0;
}

// 원형 큐의 front에서 원소를 삭제/반환
element enQueue(TYPE* CQ, element item) {
	QNODE* newNode = NULL;
	newNode = (QNODE*)calloc(1, sizeof(QNODE));
	newNode->data = item;
	newNode->link = NULL;

	if (CQ->front == NULL) //처음꺼 집어넣을때
	{
		CQ->front = newNode;
		CQ->rear = newNode;
	}
	else //처음게 뭔가 있을때
	{
		CQ->rear->link = newNode;
		CQ->rear = newNode;
	}
}

// 원형 큐의 rear에 원소를 삭제
void deQueue(TYPE* CQ) {

	QNODE* old = NULL;
	element item = 0;

	if (isEmpty(CQ))
	{
		return 0;
	}
	else {
		old = CQ->front; //삭제할 값 지정
		CQ->front = CQ->front->link; //새로운 값 지정
		item = old->data; //삭제한 값 리턴

		if (CQ->front == NULL) { //텅 비면 아예 초기화
				CQ->rear = NULL;
			}
			free(old); //값 삭제
			return item;
	}
}

// 원형 큐의 가장 앞에 있는 원소를 검색하는 연산
	element peek(TYPE * CQ) {
	element item;
	if (isEmpty(CQ)) return 0;
	else 
	{
		item = CQ->front->data;
		return item;
	}
}

// 원형 큐의 원소를 출력
void printQ(TYPE* CQ) {
	QNODE* temp = CQ->front;
	printf(" QUEUE: [");
	while (temp) {
		printf("%d, ", temp->data);
		temp = temp->link;
	}
	printf(" ]\n");
}

int main(void)
{
	int cnt_i;
	TYPE* CQ = createLinkedQueue();		// 큐생성
	TYPE* CQ2 = createLinkedQueue();		// 큐생성
	element data;

	printf("[큐 삽입]\n");
	for (cnt_i = 0; cnt_i < 11; cnt_i++)
	{
		printf("%d 삽입\n", cnt_i);
		enQueue(CQ, cnt_i);
		printCQ(CQ);
	}

	data = peek(CQ);
	printf("\nFirst item in Queue: %d\n", data);

	printf("\n[큐 삭제]\n");
	for (cnt_i = 0; cnt_i < 10; cnt_i++)
	{
		data = deQueue(CQ);
		printf("%d 삭제\n", data);
		printCQ(CQ);
	}

	printf("\n[거짓포화]\n");
	for (cnt_i = 0; cnt_i < 10; cnt_i++)
	{
		printf("enQueue: ");
		enQueue(CQ2, cnt_i);
		printCQ(CQ2);

		printf("deQueue: ");
		deQueue(CQ2);
		printCQ(CQ2);
	}

	getchar();
}}
