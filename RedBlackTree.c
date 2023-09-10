#include<stdio.h>
#include<stdlib.h>
#include<errno.h>

//存放数据类型
typedef int dataType;

//颜色枚举类型
typedef enum { RED = 'R', BLACK = 'B' } Color;

//红黑树节点
typedef struct TreeNode
{
	dataType data;
	Color color;
	struct TreeNode* parent;
	struct TreeNode* leftChild;
	struct TreeNode* rightChild;
}TreeNode;

void initRedBlackTree(TreeNode** rootnode)
{
	*rootnode = NULL;
}

TreeNode* createTreeNode(dataType data)
{
	TreeNode* tmp = (TreeNode*)malloc(sizeof(TreeNode));
	if (tmp == NULL) {
		perror("create TreeNode error");
		exit(1);
	}
	tmp->data = data;
	tmp->color = RED;
	tmp->parent = NULL;
	tmp->leftChild = NULL;
	tmp->rightChild = NULL;
	return tmp;
}

void insertRootNode(TreeNode** rootnode, dataType data)
{
	*rootnode = createTreeNode(data);
	(*rootnode)->color = BLACK;
}

int getTreeHeight(TreeNode** rootnode)
{
	int cnt1 = 1, cnt2 = 1;
	if ((*rootnode)->leftChild) {
		(*rootnode) = (*rootnode)->leftChild;
		cnt1++;
	}
	if ((*rootnode)->rightChild) {
		(*rootnode) = (*rootnode)->rightChild;
		cnt2++;
	}
}

void Left_Rotate(TreeNode** rootnode)
{
	TreeNode* tmp = *rootnode;
	TreeNode* temp = (*rootnode)->rightChild->leftChild;
	TreeNode* prnt = (*rootnode)->parent;

	*rootnode = (*rootnode)->rightChild;
	(*rootnode)->leftChild = tmp;
	(*rootnode)->leftChild->rightChild = temp;
	(*rootnode)->parent = prnt;
	tmp->parent = *rootnode;
	if (temp) {
		temp->parent = (*rootnode)->leftChild;
	}
}

void Right_Rotate(TreeNode** rootnode)
{
	TreeNode* tmp = (*rootnode);
	TreeNode* temp = tmp->leftChild->rightChild;
	TreeNode* prnt = tmp->parent;

	*rootnode = tmp->leftChild;
	(*rootnode)->rightChild = tmp;
	(*rootnode)->rightChild->leftChild = temp;
	(*rootnode)->parent = prnt;
	tmp->parent = *rootnode;
	if (temp) {
		temp->parent = (*rootnode)->rightChild;
	}
}

void updateColor(TreeNode** rootnode, TreeNode* child)
{
	if (*rootnode == NULL ) return;
	if (child == (*rootnode)->leftChild) {
		if (child->color == BLACK) return;
		else {
			if ((*rootnode)->rightChild == NULL) {
				if (child->leftChild) {
					child->color = BLACK;
					(*rootnode)->color = RED;
					Right_Rotate(rootnode);
					return;
				}
				else {
					child->rightChild->color = BLACK;
					(*rootnode)->color = RED;
					Left_Rotate(&(*rootnode)->leftChild);
					Right_Rotate(rootnode);
					return;
				}
			}
			else {
				child->color = BLACK;
				(*rootnode)->rightChild->color = BLACK;
				(*rootnode)->color = RED;
				return;
			}
		}
	}
	else {
		if (child->color == BLACK) return;
		else {
			if ((*rootnode)->leftChild == NULL) {
				if (child->rightChild) {
					child->color = BLACK;
					(*rootnode)->color = RED;
					Left_Rotate(rootnode);
					return;
				}
				else {
					child->rightChild->color = BLACK;
					(*rootnode)->color = RED;
					Right_Rotate(&(*rootnode)->rightChild);
					Left_Rotate(rootnode);
					return;
				}
			}
			else {
				child->color = BLACK;
				(*rootnode)->rightChild->color = BLACK;
				(*rootnode)->color = RED;
				return;
			}
		}
	}
}

void insertTreeNode(TreeNode** rootnode, TreeNode* prnt, dataType data)
{
	if (*rootnode == NULL) {
		*rootnode = createTreeNode(data);
		(*rootnode)->parent = prnt;
		return;
	}
	if (data < (*rootnode)->data) {
		insertTreeNode(&(*rootnode)->leftChild, *rootnode, data);
		if ((*rootnode)->leftChild && ((*rootnode)->leftChild->leftChild || (*rootnode)->leftChild->rightChild)) {
			updateColor(rootnode, (*rootnode)->leftChild);
		}
		else return;
	}
	else if (data > (*rootnode)->data) {
		insertTreeNode(&(*rootnode)->rightChild, *rootnode, data);
		if ((*rootnode)->rightChild && ((*rootnode)->rightChild->leftChild || (*rootnode)->rightChild->rightChild)) {
			updateColor(rootnode, (*rootnode)->rightChild);
		}
		else return;
	}

	if ((*rootnode)->parent == NULL) {
		(*rootnode)->color = BLACK;
	}
}

void proPrintRedBlackTree(TreeNode** rootnode)
{
	if (*rootnode) {
		printf("%d %c|", (*rootnode)->data, (*rootnode)->color);
		proPrintRedBlackTree(&(*rootnode)->leftChild);
		proPrintRedBlackTree(&(*rootnode)->rightChild);
	}
}

void inoPrintRedBlackTree(TreeNode** rootnode)
{
	if (*rootnode) {
		inoPrintRedBlackTree(&(*rootnode)->leftChild);
		printf("%d %c|", (*rootnode)->data, (*rootnode)->color);
		inoPrintRedBlackTree(&(*rootnode)->rightChild);
	}
}

void posPrintRedBlackTree(TreeNode** rootnode)
{
	if (*rootnode) {
		posPrintRedBlackTree(&(*rootnode)->leftChild);
		posPrintRedBlackTree(&(*rootnode)->rightChild);
		printf("%d %c|", (*rootnode)->data, (*rootnode)->color);
	}
}

int main()
{
	TreeNode* tree;
	initRedBlackTree(&tree);
	insertRootNode(&tree, 15);
	insertTreeNode(&tree, NULL, 10);
	insertTreeNode(&tree, NULL, 20);
	insertTreeNode(&tree, NULL, 17);
	// printf("%d\n", tree->rightChild->data);
	// insertRootNode(&tree, 15);
	// insertTreeNode(&tree, NULL, 10);
	// insertTreeNode(&tree, NULL, 20);
	// insertTreeNode(&tree, NULL, 11);
	// insertTreeNode(&tree, NULL, 9);
	// insertTreeNode(&tree, NULL, 8);
	// insertTreeNode(&tree, NULL, 35);
	proPrintRedBlackTree(&tree);
	// printf("\n");
	// inoPrintRedBlackTree(&tree);
	// printf("\n");
	//posPrintRedBlackTree(&tree);
	printf("\n");
	return 0;
}
