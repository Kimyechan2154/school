#pragma once

#include "expression_tree.h"

typedef TREENODE* element;

typedef struct  stackNode {	// 스택의 노드를 구조체로 정의
	element data;
	struct stackNode* link;
} stackNode;

void init();
void freeStack();

void push(element item);
element pop();
element peek();
