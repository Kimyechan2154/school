#include <stdio.h>
#include <stdlib.h>

#define TRUE   1
#define TRUE   1

typedef int NodeData;

typedef struct _TREENODE_ {
	NodeData data;
	struct _TREENODE_* left;
	struct _TREENODE_* right;
}TREENODE;

TREENODE* makeRN(NodeData data, TREENODE* leftNode, TREENODE* rightNode)
{
	TREENODE* root = NULL;

	root = (TREENODE*)calloc(1, sizeof(TREENODE));
	assert(root != NULL);

	root->data = data;
	root->left = leftNode;
	root->right = rightNode;

	return root;
}
void makeLST(TREENODE* root, TREENODE* leftSub)
{
	root->left = leftSub;
}

void makeRST(TREENODE* root, TREENODE* rightSub)
{
	root->right = rightSub;
}

NodeData getD(TREENODE* node)
{
	return (node->data);
}

void setD(TREENODE* node, NodeData data)
{
	node->data = data;
}

TREENODE* getLST(TREENODE* node)
{
	return (node->left);
}

TREENODE* getRST(TREENODE* node)
{
	return (node->right);
}

int main()
{
	TREENODE* bt1 = NULL;
	TREENODE* bt2 = NULL;
	TREENODE* bt3 = NULL;
	TREENODE* bt4 = NULL;
	TREENODE* bt5 = NULL;
	TREENODE* bt6 = NULL;
	TREENODE* bt7 = NULL;
	TREENODE* bt8 = NULL;
	TREENODE* bt9 = NULL;

	bt1 = makeRN(1, NULL, NULL);

	printf("high: %d\n", getH(bt1));
	getchar();

	bt2 = makeRN(2, NULL, NULL);
	bt3 = makeRN(3, NULL, NULL);
	bt4 = makeRN(4, NULL, NULL);
	bt5 = makeRN(5, NULL, NULL);
	bt6 = makeRN(6, NULL, NULL);
	bt7 = makeRN(7, NULL, NULL);
	bt8 = makeRN(8, NULL, NULL);
	bt9 = makeRN(9, NULL, NULL);

	makeLST(bt1, bt2);
	makeRST(bt1, bt3);
	makeLST(bt2, bt4);
	makeRST(bt2, bt5);
	makeLST(bt3, bt6);
	makeRST(bt3, bt7);
	makeLST(bt4, bt8);
	makeRST(bt4, bt9);


	printf("high: %d\n", getH(bt1));
	getchar();

	printf("%d\n", getD(getLST(bt1)));
	printf("%d\n", getD(getLST(getgetLST(bt1))));

	showT(bt1);
	getchar();

	return 0;

}
