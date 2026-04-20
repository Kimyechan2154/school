#include <stdio.h>
#include <stdlib.h>

#define TRUE	1
#define FALSE	0

#define Q_SIZE 10


typedef int element;		// 큐 원소(element)의 자료형을 int로 정의
typedef struct {
	element queue[Q_SIZE];	// 1차원 배열 큐 선언
	int front, rear;		// 삽입, 삭제를 위한 위치 변수
} QueueType;

// 공백 순차 큐를 생성
QueueType* createQueue()
{
	QueueType* Q;
	Q = (QueueType*)calloc(1, sizeof(QueueType));
	Q->front = -1;	// front 초기 설정
	Q->rear = -1;	// rear 초기 설정
	return Q;
}

// 순차 큐가 포화상태인지 검사
int isFull(QueueType* Q)
{
	if (Q->rear == Q_SIZE - 1) {
		printf("Queue is full!\n");
		return TRUE;
	}
	else {
		return FALSE;
	}
}

// 순차 큐가 공백상태인지 검사
int isEmpty(QueueType* Q)
{
	if (Q->front == Q->rear) {
		printf("Queue is empty!\n");
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

// 순차 큐의 rear에 원소 삽입
void enQueue(QueueType* Q, element item)
{
	if (isFull(Q)) return;
	else {
		Q->rear++; //rear 숫자 증가
		Q->queue[Q->rear] = item; //값을 삽입하는거라 리턴 값이 없어도 됨
	}
}

// 순차 큐의 front에서 원소를 삭제
element deQueue(QueueType* Q)
{
	if (isEmpty(Q)) return;
	else {
		Q->front++;
		return 	Q->queue[Q->front + 1];
	}
}

// 순차 큐의 가장 앞에 있는 원소를 검색
element peek(QueueType* Q) {
	if (isEmpty(Q)) return;
	else {
		return Q->queue[Q->front + 1];
	}
}

void printQ(QueueType* Q) {
	int i;
	printf("Queue: (front: %d), rear: %d)[", Q->front, Q->rear);
	for (i = Q->front + 1; i <= Q->rear; i++)
	{
		printf("%d, ", Q->queue[i]);
	}
	printf("]\n");
}

int main()
{
	int cnt_i;
	QueueType* Q = createQueue();		// 큐생성
	QueueType* Q2 = createQueue();		// 큐생성
	element data;

	printf("[큐 삽입]\n");
	for (cnt_i = 0; cnt_i < 11; cnt_i++)
	{
		printf("%d 삽입\n", cnt_i);
		enQueue(Q, cnt_i);
		printQ(Q);
	}

	data = peek(Q);
	printf("\nFirst item in Queue: %d\n", data);

	printf("\n[큐 삭제]\n");
	for (cnt_i = 0; cnt_i < 11; cnt_i++)
	{
		data = deQueue(Q);
		printf("%d 삭제\n", data);
		printQ(Q);
	}

	printf("\n[거짓포화]\n");
	for (cnt_i = 0; cnt_i < 11; cnt_i++)
	{
		printf("enQueue: ");
		enQueue(Q2, cnt_i);
		printQ(Q2);

		printf("deQueue: ");
		deQueue(Q2);
		printQ(Q2);
	}

	getchar();
}

// EOF 
