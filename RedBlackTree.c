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

void Left_Rotate(TreeNode** rootnode, TreeNode* node)
{
	TreeNode* tmp = node->rightChild;
	node->rightChild = tmp->leftChild;

	if(tmp->leftChild != NULL){
		tmp->leftChild->parent = node;
	}

	tmp->parent = node->parent;

	if(node->parent == NULL){
		*rootnode = tmp;
	}
	else if(node == node->parent->leftChild){
		node->parent->leftChild = tmp;
	}
	else if(node == node->parent->rightChild){
		node->parent->rightChild = tmp;
	}

	tmp->leftChild = node;
	node->parent = tmp;
}

void Right_Rotate(TreeNode** rootnode, TreeNode* node)
{
	TreeNode* tmp = node->leftChild;
	node->leftChild = tmp->rightChild;

	if(tmp->rightChild != NULL){
		tmp->rightChild->parent = node;
	}

	tmp->parent = node->parent;
	if(node->parent == NULL){
		*rootnode = tmp;
	}
	else if(node == node->parent->leftChild){
		node->parent->leftChild = tmp;
	}
	else if(node == node->parent->rightChild){
		node->parent->rightChild = tmp;
	}

	tmp->rightChild = node;
	node->parent = tmp;
}

void updateColor(TreeNode** rootnode, TreeNode* newnode)
{
	while(newnode->parent != NULL && newnode->parent->color == RED){
		if (newnode->parent == newnode->parent->parent->leftChild) {
			if (newnode->parent->parent->rightChild == NULL) {
				if (newnode == newnode->parent->leftChild) {
						newnode->parent->color = BLACK;
						newnode->parent->parent->color = RED;
						Right_Rotate(rootnode, newnode->parent->parent);
						return;
					}
					else {
						newnode->color = BLACK;
						newnode->parent->parent->color = RED;
						newnode = newnode->parent;
						Left_Rotate(rootnode, newnode);
						Right_Rotate(rootnode, newnode->parent->parent);
						return;
					}
				}
			else {
				newnode->parent->color = BLACK;
				newnode->parent->parent->rightChild->color = BLACK;
				newnode->parent->parent->color = RED;
				return;
			}
		}
	else {
		if (newnode->parent->parent->leftChild == NULL) {
			if (newnode == newnode->parent->rightChild) {
					newnode->parent->color = BLACK;
					newnode->parent->parent->color = RED;
					Left_Rotate(rootnode, newnode->parent->parent);
					return;
				}
				else {
					newnode->color = BLACK;
					newnode->parent->parent->color = RED;
					newnode = newnode->parent;
					Right_Rotate(rootnode, newnode);
					Left_Rotate(rootnode, newnode->parent->parent);
					return;
				}
			}
			else {
				newnode->parent->color = BLACK;
				newnode->parent->parent->leftChild->color = BLACK;
				newnode->parent->parent->color = RED;
				return;
			}
		}
	}
	
	if (newnode->parent == NULL) {
		newnode->color = BLACK;
	}
}

void insertTreeNode(TreeNode** rootnode, dataType data)
{
	TreeNode* tmp = *rootnode;
	TreeNode* prnt = NULL;

	while(tmp){
		prnt = tmp;
		if(data < tmp->data){
			tmp = tmp->leftChild;
		}
		else if(data > tmp->data){
			tmp = tmp->rightChild;
		}
	}

	tmp = createTreeNode(data);
	if(tmp->data < prnt->data){
		prnt->leftChild = tmp;
	}else{
		prnt->rightChild = tmp;
	}
	tmp->parent = prnt;

    updateColor(rootnode,tmp);

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
	insertRootNode(&tree, 7);
	insertTreeNode(&tree, 3);
	insertTreeNode(&tree, 18);
	insertTreeNode(&tree, 10);
	insertTreeNode(&tree, 22);
	insertTreeNode(&tree, 8);
	insertTreeNode(&tree, 11);
	insertTreeNode(&tree, 26);
	insertTreeNode(&tree, 2);
	insertTreeNode(&tree, 6);
	insertTreeNode(&tree, 13);
	proPrintRedBlackTree(&tree);
	// printf("\n");
	// inoPrintRedBlackTree(&tree);
	// printf("\n");
	//posPrintRedBlackTree(&tree);
	printf("\n");
	return 0;
}
