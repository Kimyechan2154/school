#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define STACK_SIZE 100

typedef int element;

//실습 1-1

//element stack[STACK_SIZE]; //STACK_SIZE 크기의 스택이 정해짐
//int top = -1;
//
//void init()
//{
//	top = -1;
//}
//
//int isEmpty() {
//	if (top == -1) return 1;
//	else return 0;
//}
//
//int isFull() {
//	if (top == STACK_SIZE - 1) return 1;
//	else return 0;
//}
//
//void push(element item) { //매개변수 item을 받음
//	if (isFull()) { //꽉 차있다면
//		printf("\n\n Stack is FULL \n");
//		return;
//	}
//	else stack[++top] = item; //top 숫자 1 증가 후 그 값에 item을 작성
//}
//
//element pop () {
//	if (isEmpty()) { //비었다면
//		printf("\n\n Stack is Empty \n");
//		return 0;
//	}
//	else return stack[top--]; //원소 삭제후 숫자 감소
//}
//
//element peek() {
//	if (isEmpty()) { //비었다면
//		printf("\n\n Stack is Empty \n");
//		exit(1); //비었다면 출력후 탈출
//	}
//	else return stack[top]; //스택 숫자 리턴
//}
//
//void exercise1_1() {
//	int cnt_i = 0;
//	element item;
//	printf("\n** stack list ** \n");
//	printStack();
//
//	for (cnt_i = 0; cnt_i < 10; cnt_i++)
//	{
//		push(cnt_i);
//		printStack();
//	}
//	//오버플로우
//	push(cnt_i);
//	printStack();
//
//	item = peek(); printStack();
//	printf("peek => %d", item);
//
//	for (cnt_i = 0; cnt_i < 10; cnt_i++)
//	{
//		item = pop(); //tkrwp
//		printf("\t pop => %d", item);
//	}
//	item = pop(); printStack();
//
//	getchar();
//}

//실습 1-2

//typedef struct _ARRAY_STACK_ {
//	element stackArr[STACK_SIZE]; //스택 할당
//	int topIndex;
//	int stackSize;
//}ARRAY_STACK;
//
//void init(ARRAY_STACK* stack, int size)
//{
//	stack->stackSize = size; //size의 크기로 스택 용량 저장
//	stack->topIndex = -1; //스택 초기화
//}
//
//int isEmpty(ARRAY_STACK* stack) {
//	if (stack->stackSize == -1) return 1;
//	else return 0;
//}
//
//int isFull(ARRAY_STACK* stack) {
//	if (stack->topIndex == (stack->stackSize - 1)) return 1;
//	else return 0;
//}
//
//void push(ARRAY_STACK* stack, element item) { //매개변수 item을 받음
//	if (isFull(stack)) { //꽉 차있다면
//		printf("\n\n Stack is FULL \n");
//		return;
//	}
//	else stack->stackArr[++(stack->topIndex)] = item; //top 숫자 1 증가 후 그 값에 item을 작성
//}
//
//element pop (ARRAY_STACK* stack) {
//	if (isEmpty(stack)) { //비었다면
//		printf("\n\n Stack is Empty \n");
//		return 0;
//	}
//	else return stack->stackArr[(stack->topIndex--)]; //원소 삭제후 숫자 감소
//}
//
//element peek(ARRAY_STACK* stack) {
//	if (isEmpty(stack)) { //비었다면
//		printf("\n\n Stack is Empty \n");
//		exit(1); //비었다면 출력후 탈출
//	}
//	else return stack->stackArr[stack->topIndex--]; //스택 숫자 리턴
//}
//
//void printStack(ARRAY_STACK* stack) {
//	int i;
//	printf("\n STACK [ ");
//	for (i = stack->topIndex; i >= 0; i--) 
//		printf("%d ", stack->stackArr[i]);
//	printf("] ");
//
//	} 
//
//void exercise1_2() {
//	int cnt_i = 0;
//	element item;
//	ARRAY_STACK stack;
//	printf("\n** stack list ** \n");
//	
//	init(&stack, 10);
//	printStack(&stack);
//	
//	for (cnt_i = 0; cnt_i < 10; cnt_i++)
//	{
//		push(&stack, cnt_i);
//		printStack(&stack);
//	}
//
//	push(&stack, cnt_i);
//	printStack(&stack);
//
//	item = peek(&stack); printStack(&stack);
//	printf("peek => %d", item);
//
//	for (cnt_i = 0; cnt_i < 10; cnt_i++)
//	{
//		item = pop(&stack); //tkrwp
//		printf("\t pop => %d", item);
//	}
//	item = pop(&stack); printStack(&stack);
//
//	getchar();
//}

//실습 2

typedef int element; // element data; == int data

typedef struct stackNode {
	element data;
	struct stackNode* link;
}stackNode;

stackNode* top;

void init()
{ //동적 할당시 
	top = NULL;
}

int isEmpty() {
	if (top == NULL) return 1;
	else return 0;
}

void push(element item) {
	stackNode* temp = (stackNode *)calloc(1, sizeof(stackNode));
	temp->data = item;
	temp->link = top;
	top = temp;
}

element pop() {
	element item;
	stackNode* temp = top;

	if (top == NULL) {
		printf("\n\n Stack is empty!\n");
		return 0;
	}
	else {
		item = temp->data; //삭제할 변수 복사
		top = temp->link;  //top안의 내용물을 temp->link로 이동시킨후 없애버림
		free(temp);  //노드 삭제
		return item; //삭제된 변수 반환
	}
}

element peek() {
	if (top == NULL) {
		printf("\n\n Stack is empty !\n");
		return 0;
	}
	else {
		return(top->data);
	}
}

void printStack() {
	stackNode* p = top;
	printf("\n STACK [ ");
	while (p) { //p가 널이 될때까지
		printf("%d ", p->data); //p의 값 노드를 옮겨서 출력
		p = p->link; //p의 값 아래 노드로 내림
	}
	printf("] ");
}

void freeStack()
{
	stackNode* pre = NULL; //메모리 해제
	stackNode* cur = NULL; //리스트 따라 이동

	pre = cur = top; //맨위부터 시작
	while (cur != NULL)
	{
		pre = cur; //노드 위치 pre에 저장
		cur = cur->link; 
		free(pre);
		pre = NULL; //포인터 초기화
	}
}

void exercise2()
{
	element item;
	int cnt_i;

	top = NULL;
	printf("\n** Connected Stack Sum **\n");
	printStack();

	for (cnt_i = 0; cnt_i < 10; cnt_i++)
	{
		push(cnt_i); //10개의 노드에 값을 할당
		printStack();
	}

	item = peek(); printStack();
	printf("peek => %%d", item);

	for (cnt_i = 0; cnt_i < 10; cnt_i++)
	{
		item = pop();  //10개의 노드에 값을 할당
		printStack();
		printf("\t pop => %d", item);
	}
	freeStack();

	getchar();

}

int main() {

	//exercise1_1();

	//exercise1_2();

	exercise2();

	return 0;
}
