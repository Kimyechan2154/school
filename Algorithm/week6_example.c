#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define STACK_SIZE 100

//typedef int element; //element를 int 처럼 사용
//
////실습 1-1
//
//element stack[STACK_SIZE]; //STACK_SIZE 크기의 스택이 정해짐
//int top = -1;
//
//void init()
//{
//	top = -1;
//}
//
//int isEmpty() { //비어있으면 T 안비어있으면 F
//	if (top == -1) return 1;
//	else return 0;
//}
//
//int isFull() { //꽉차있으면 T 안차있으면 F
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
//element peek() { //맨 위값 확인
//	if (isEmpty()) { //비었다면
//		printf("\n\n Stack is Empty \n");
//		exit(1); //비었다면 출력후 탈출
//	}
//	else return stack[top]; //스택 숫자 리턴
//}
//
//void printStack() {
//	int i;
//	printf("\n STACK [ ");
//	for (i = top; i >= 0; i--)
//		printf("%d ", stack[i]);
//	printf("] ");
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
//	item = peek(); printStack(); //현재 top 출력
//	printf("peek => %d", item);
//
//	for (cnt_i = 0; cnt_i < 10; cnt_i++)
//	{
//		item = pop(); //삭제
//		printf("\t pop => %d", item);
//	}
//	item = pop(); printStack(); //오버플로우
//
//	getchar();
//}
//
////실습 1-2
//
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
//	else return stack->stackArr[stack->topIndex]; //현재 top원소 확인
//}
//
//void printStack(ARRAY_STACK* stack) {
//	int i;
//	printf("\n STACK [ ");
//	for (i = stack->topIndex; i >= 0; i--) //역순 출력
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
//
////실습 2
//
//typedef struct stackNode {
//	element data;
//	struct stackNode* link;
//}stackNode;
//
//stackNode* top;
//
//void init()
//{ //동적 할당시 
//	top = NULL;
//}
//
//int isEmpty() {
//	if (top == NULL) return 1;
//	else return 0;
//}
//
//void push(element item) {
//	stackNode* temp = (stackNode *)calloc(1, sizeof(stackNode)); //선언과 동시에 초기화
//	temp->data = item; // 데이터 저장       newNode->data, x
//	temp->link = top;  // 이전 노드와 연결  newNode->link = L->head;
//	top = temp;        // 시작 지점 갱신    L->head = newNode;
//}
//
//element pop() {
//	element item;
//	stackNode* temp = top;
//
//	if (top == NULL) {
//		printf("\n\n Stack is empty!\n");
//		return 0;
//	}
//	else {
//		item = temp->data; //삭제할 변수 복사
//		top = temp->link;  //top안의 내용물을 temp->link로 이동시킨후 없애버림
//		free(temp);  //노드 삭제
//		return item; //삭제된 변수 반환
//	}
//}
//
//element peek() {
//	if (top == NULL) {
//		printf("\n\n Stack is empty !\n");
//		return 0;
//	}
//	else {
//		return(top->data);
//	}
//}
//
//void printStack() {
//	stackNode* p = top;
//	printf("\n STACK [ ");
//	while (p) { //p가 널이 될때까지
//		printf("%d ", p->data); //p의 값 노드를 옮겨서 출력
//		p = p->link; //p의 값 아래 노드로 내림
//	}
//	printf("] ");
//}
//
//void freeStack()
//{
//	stackNode* pre = NULL; //메모리 해제
//	stackNode* cur = NULL; //리스트 따라 이동
//
//	pre = cur = top; //맨위부터 시작
//	while (cur != NULL)
//	{
//		pre = cur; //노드 위치 pre에 저장
//		cur = cur->link; 
//		free(pre);
//		pre = NULL; //포인터 초기화
//	}
//}
//
//void exercise2()
//{
//	element item;
//	int cnt_i;
//
//	top = NULL;
//	printf("\n** Connected Stack Sum **\n");
//	printStack();
//
//	for (cnt_i = 0; cnt_i < 10; cnt_i++)
//	{
//		push(cnt_i); //10개의 노드에 값을 할당
//		printStack();
//	}
//
//	item = peek(); printStack();
//	printf("peek => %%d", item);
//
//	for (cnt_i = 0; cnt_i < 10; cnt_i++)
//	{
//		item = pop();  //10개의 노드에 값을 할당
//		printStack();
//		printf("\t pop => %d", item);
//	}
//	freeStack();
//
//	getchar();
//
//}

#include <crtdbg.h>			// 메모리 누수를 확인하기 위해 CRT 디버그 함수 사용

#define TRUE	1
#define FALSE	0

typedef char element;		// 스택 요소(element)의 자료형을 char로 정의

typedef struct  stackNode {	// 스택의 노드를 구조체로 정의
	element data;
	struct stackNode* link;
} stackNode;

stackNode* top;				// 스택의 top 노드를 지정하기 위해 포인터 top 선언

// 스택이 공백 상태인지 확인하는 연산
int isEmpty() {
	if (top == NULL) return TRUE;
	else return FALSE;
}

// 스택의 top에 원소를 삽입하는 연산
// top 노드는 이전 top 노드를 가리키도록 해야함
void push(element item) {
	stackNode* temp = (stackNode*)calloc(1, sizeof(stackNode));
	temp->data = item;
	temp->link = top;		// 삽입 노드를 top의 위에 연결
	top = temp;				// top 위치를 삽입 노드로 이동
}

// 스택의 top에서 원소를 삭제하는 연산
element pop() {
	element item;
	stackNode* temp = top;

	if (top == NULL) {		// 스택이 공백 리스트인 경우
		printf("\n\n Stack is empty !\n");
		return 0;
	}
	else {					// 스택이 공백 리스트가 아닌 경우
		item = temp->data;
		top = temp->link;	// top 위치를 삭제 노드 아래로 이동
		free(temp);			// 삭제된 노드의 메모리 반환
		return item;		// 삭제된 원소 반환
	}
}

// 스택의 원소를 top에서 bottom 순서로 출력하는 연산
void printStack() {
	stackNode* p = top;
	printf("\n STACK [ ");
	while (p) {
		printf("%c ", p->data);
		p = p->link;
	}
	printf("] ");
}

// 수식의 괄호를 검사하는 연산
int testPair(char* exp) {
	char symbol, open_pair;
	// char형 포인터 매개변수로 받은 수식 exp의 길이를 계산하여 length 변수에 저장
	int i, length = strlen(exp); //문자열 길이 구하고
	top = NULL;

	for (i = 0; i < length; i++) {

		printStack();

		symbol = exp[i]; //문자열 하나씩 검증
		switch (symbol) { //괄호 숫자 연산자 분류하는 함수
			// (1) 왼쪽 괄호는 스택에 삽입
		case '(':
		case '[':
		case '{':
			push(symbol); break;
			// (2) 오른쪽 괄호를 읽으면,
		case ')':
		case ']':
		case '}':
			if (top == NULL) return FALSE;
			else {
				// (2)-1 스택에서 마지막으로 읽은 괄호를 꺼냄
				open_pair = pop();
				// (2)-2 괄호 쌍이 맞는지 검사
				if ((open_pair == '(' && symbol != ')') ||
					(open_pair == '[' && symbol != ']') ||
					(open_pair == '{' && symbol != '}'))
					// (2)-3 괄호 쌍이 틀리면 수식 오류
					return FALSE;
				// (2)-4 괄호 쌍이 맞으면 다음 symbol 검사를 계속함
				else break;
			}
		}
	}
	if (top == NULL) return TRUE;// 수식 검사를 마친 후 스택이 공백이면 1을 반환
	else return FALSE;            // 공백이 아니면 0을 반환(수식 괄호 틀림)
}

/*
 * stack의 top 노드에서부터 0번째 index로 메모리를 해제함
 */
void freeStack()
{
	stackNode* pre = NULL;
	stackNode* cur = NULL;

	pre = cur = top;
	while (cur != NULL)
	{
		pre = cur;
		cur = cur->link;
		free(pre);
		pre = NULL;
	}
}

void exer3_bracket()
{
	char* express = "{(A+B)-3}*5+[{cos(x+y)+7}-1]*4";
	printf("%s", express);

	if (testPair(express) == 1)
		printf("\n\n수식의 괄호가 맞게 사용되었습니다!");
	else
		printf("\n\n수식의 괄호가 틀렸습니다!");

	getchar();
}

void main(void) {

	exer3_bracket();
	freeStack();
}
// EOF


//실습 4

typedef struct  stackNode {	// 스택의 노드를 구조체로 정의
	element data;
	struct stackNode* link;
} stackNode;

stackNode* top;				// 스택의 top 노드를 지정하기 위해 포인터 top 선언

/*
 * 연산자의 우선순위를 반환함
 */
int precedence(char op)
{
	switch (op) {
	case '(': case ')': return 0;
	case '+': case '-': return 1;
	case '*': case '/': case '%': return 2;
	}
	return -1;
}

void init()
{
	top = NULL;
}

// 스택의 원소를 top에서 bottom 순서로 출력하는 연산
void printStack() {
	stackNode* p = top;
	printf("\n STACK [ ");
	while (p) {
		printf("%c ", p->data);
		p = p->link;
	}
	printf("] ");
}

void freeStack()
{
	stackNode* pre = NULL;
	stackNode* cur = NULL;

	pre = cur = top;
	while (cur != NULL)
	{
		pre = cur;
		cur = cur->link;
		free(pre);
		pre = NULL;
	}
}

// 스택이 공백 상태인지 확인하는 연산
int isEmpty() {
	if (top == NULL) return 1;
	else return 0;
}

// 스택의 top에 원소를 삽입하는 연산
void push(element item) {
	stackNode* temp = (stackNode*)calloc(1, sizeof(stackNode));
	temp->data = item;
	temp->link = top;		// 삽입 노드를 top의 위에 연결
	top = temp;				// top 위치를 삽입 노드로 이동
}

// 스택의 top에서 원소를 삭제하는 연산
element pop() {
	element item;
	stackNode* temp = top;

	if (top == NULL) {		// 스택이 공백 리스트인 경우
		printf("\n\n Stack is empty !\n");
		return 0;
	}
	else {					// 스택이 공백 리스트가 아닌 경우
		item = temp->data;
		top = temp->link;	// top 위치를 삭제 노드 아래로 이동
		free(temp);			// 삭제된 노드의 메모리 반환
		return item;		// 삭제된 원소 반환
	}
}

// 스택의 top 원소를 검색하는 연산
element peek() {
	if (top == NULL) {		// 스택이 공백 리스트인 경우
		printf("\n\n Stack is empty !\n");
		return 0;
	}
	else {					// 스택이 공백 리스트가 아닌 경우
		return(top->data);  // 현재 top의 원소 반환
	}
}

// 수식의 괄호를 검사하는 연산
int testPair(char* exp) {
	char symbol, open_pair;
	// char형 포인터 매개변수로 받은 수식 exp의 길이를 계산하여 length 변수에 저장
	int i, length = strlen(exp);
	top = NULL;

	for (i = 0; i < length; i++) {

		//printStack();

		symbol = exp[i];
		switch (symbol) {
			// (1) 왼쪽 괄호는 스택에 삽입
		case '(':
		case '[':
		case '{':
			push(symbol); break;
			// (2) 오른쪽 괄호를 읽으면,
		case ')':
		case ']':
		case '}':
			if (top == NULL) return 0;
			else {
				// (2)-1 스택에서 마지막으로 읽은 괄호를 꺼냄
				open_pair = pop();
				// (2)-2 괄호 쌍이 맞는지 검사
				if ((open_pair == '(' && symbol != ')') ||
					(open_pair == '[' && symbol != ']') ||
					(open_pair == '{' && symbol != '}'))
					// (2)-3 괄호 쌍이 틀리면 수식 오류
					return 0;
				// (2)-4 괄호 쌍이 맞으면 다음 symbol 검사를 계속함
				else break;
			}
		}
	}
	if (top == NULL) return 1;// 수식 검사를 마친 후 스택이 공백이면 1을 반환
	else return 0;            // 공백이 아니면 0을 반환(수식 괄호 틀림)
}

void infix_to_postfix(char* infix, char* postfix)
{
	int cnt_i = 0;
	int cnt_j = 0;
	char c, op;


	// 코드 작성 필요..
}

// 후위 표기법 수식을 계산하는 연산
element evalPostfix(char* exp) {
	int opr1, opr2, value, i = 0;
	// char형 포인터 매개변수로 받은 수식 exp의 길이를 계산하여 length 변수에 저장
	int length = strlen(exp);
	char symbol;
	top = NULL;

	// 코드 작성 필요..
}

void exer4_postfix_eval()
{
	int result;
	int cnt_i;
	char infix_expr[13][80] = { "3*5-6/2",
		"((4+2)/4)-(3+70/(7*5))",
		"((((5*6)+7)-8)*9)",
		"((((5*6)+7)-8)*9)+(9+8)*7",
		"((((5*6)+7)-8)*9)+(((9+8)*7)%4)",
		"(((((((((1*2)*3)*4)*5)*6)*7)*8)*9)*10)",
		"1*2+3*4+6/2+8%3+9-8",
		"70+80*9-10+(60+70+80*2-10)",
		"(9-(4/2+1))*(5*2-2)",
		"((80*87)/4)*2-705",
		"100*((90-80+20*5)-(30*20-10/5))",
		"(9-(4/2+1+(10*5)+7*6))*(50*20-10%2)",
		"123+456*(789+(90-80+20*5)-(30*20-10/5))",
	};
	char postfix_expr[320] = { 0x00, };

	for (cnt_i = 0; cnt_i < 13; cnt_i++)
	{
		printf("[%02d]-th 수식 평가\n", cnt_i);
		if (testPair(infix_expr[cnt_i]) == 1) {
			printf("괄호 개수가 일치함\n");
		}
		else {
			printf("괄호 개수가 불일치함\n");
		}

		memset(postfix_expr, 0, sizeof(postfix_expr));

		init();
		infix_to_postfix(infix_expr[cnt_i], postfix_expr);

		printf("\n\ninfix: %s -> postfix: %s\n", infix_expr[cnt_i], postfix_expr);

		printf("후위 표기식 : %s", postfix_expr);

		result = evalPostfix(postfix_expr);
		printf("\n\n연산 결과 => %d\n\n", result);
		freeStack();
		getchar();
	}
}

void main(void) {

	exer4_postfix_eval();

	getchar();
}

// EOF



int main() {

	exercise1_1();

	//exercise1_2();

	//exercise2();

	return 0;
}
