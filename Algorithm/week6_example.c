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

typedef struct _ARRAY_STACK_ {
	element stackArr[STACK_SIZE]; //스택 할당
	int topIndex;
	int stackSize;
}ARRAY_STACK;

void init(ARRAY_STACK* stack, int size)
{
	stack->stackSize = size; //size의 크기로 스택 용량 저장
	stack->topIndex = -1; //스택 초기화
}

int isEmpty(ARRAY_STACK* stack) {
	if (stack->stackSize == -1) return 1;
	else return 0;
}

int isFull(ARRAY_STACK* stack) {
	if (stack->topIndex == (stack->stackSize - 1)) return 1;
	else return 0;
}

void push(ARRAY_STACK* stack, element item) { //매개변수 item을 받음
	if (isFull(stack)) { //꽉 차있다면
		printf("\n\n Stack is FULL \n");
		return;
	}
	else stack->stackArr[++(stack->topIndex)] = item; //top 숫자 1 증가 후 그 값에 item을 작성
}

element pop (ARRAY_STACK* stack) {
	if (isEmpty(stack)) { //비었다면
		printf("\n\n Stack is Empty \n");
		return 0;
	}
	else return stack->stackArr[(stack->topIndex--)]; //원소 삭제후 숫자 감소
}

element peek(ARRAY_STACK* stack) {
	if (isEmpty(stack)) { //비었다면
		printf("\n\n Stack is Empty \n");
		exit(1); //비었다면 출력후 탈출
	}
	else return stack->stackArr[stack->topIndex--]; //스택 숫자 리턴
}

void printStack(ARRAY_STACK* stack) {
	int i;
	printf("\n STACK [ ");
	for (i = stack->topIndex; i >= 0; i--) 
		printf("%d ", stack->stackArr[i]);
	printf("] ");

	} 

void exercise1_2() {
	int cnt_i = 0;
	element item;
	ARRAY_STACK stack;
	printf("\n** stack list ** \n");
	
	init(&stack, 10);
	printStack(&stack);
	
	for (cnt_i = 0; cnt_i < 10; cnt_i++)
	{
		push(&stack, cnt_i);
		printStack(&stack);
	}

	push(&stack, cnt_i);
	printStack(&stack);

	item = peek(&stack); printStack(&stack);
	printf("peek => %d", item);

	for (cnt_i = 0; cnt_i < 10; cnt_i++)
	{
		item = pop(&stack); //tkrwp
		printf("\t pop => %d", item);
	}
	item = pop(&stack); printStack(&stack);

	getchar();
}

int main() {

	exercise1_2();

	return 0;
}
