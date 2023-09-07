#include<stdio.h>
#include<stdlib.h>
#include<errno.h>

typedef int dataType;

typedef struct TreeNode
{
	dataType data;
	struct TreeNode* leftChild;
	struct TreeNode* rightChild;
	int height;
}TreeNode;

//初始化AVL树
void initAVLTree(TreeNode** rootnode)
{
	if(rootnode == NULL){
		perror("not that AVLTree");
		exit(1);
	}
	*rootnode = NULL;
}

//创建树节点
TreeNode* createTreeNode(dataType data)
{
	TreeNode* tmp = (TreeNode*)malloc(sizeof(TreeNode));
	if(tmp == NULL){
		perror("create TreeNode error");
		exit(1);
	}
	tmp->data = data;
	tmp->leftChild = NULL;
	tmp->rightChild = NULL;
	tmp->height = 1;
	return tmp;
}

int maxValue(int x, int y)
{
	return (x>y)?x:y;
}

//获取树高
int getTreeHeight(TreeNode** rootnode)
{
	if(*rootnode == NULL) return 0;
	return (*rootnode)->height;
}

//获取平衡因子
int getBalanceValue(TreeNode** rootnode)
{
	if((*rootnode) == NULL) return 0;
	return getTreeHeight(&(*rootnode)->leftChild) - getTreeHeight(&(*rootnode)->rightChild);
}

//左左单旋
void LL_Rotate(TreeNode** rootnode)
{
	TreeNode* tmp = *rootnode;
	TreeNode* temp = (*rootnode)->leftChild->rightChild;

	*rootnode = (*rootnode)->leftChild;
	(*rootnode)->rightChild = tmp;
	(*rootnode)->rightChild->leftChild = temp;

	(*rootnode)->rightChild->height = maxValue(getTreeHeight(&(*rootnode)->rightChild->leftChild),getTreeHeight(&(*rootnode)->rightChild->rightChild)) + 1;
    (*rootnode)->height = maxValue(getTreeHeight(&(*rootnode)->leftChild),getTreeHeight(&(*rootnode)->rightChild)) + 1;
}

//右有单旋
void RR_Rotate(TreeNode** rootnode)
{
	TreeNode* tmp = *rootnode;
	TreeNode* temp = (*rootnode)->rightChild->leftChild;

	*rootnode = (*rootnode)->rightChild;
	(*rootnode)->leftChild = tmp;
	(*rootnode)->leftChild->rightChild = temp;

	(*rootnode)->leftChild->height = maxValue(getTreeHeight(&(*rootnode)->leftChild->leftChild),getTreeHeight(&(*rootnode)->leftChild->rightChild)) + 1;
    (*rootnode)->height = maxValue(getTreeHeight(&(*rootnode)->leftChild),getTreeHeight(&(*rootnode)->rightChild)) + 1;;

}

//左右双旋
void LR_Rotate(TreeNode** rootnode)
{
	RR_Rotate(&(*rootnode)->leftChild);
	LL_Rotate(rootnode);
}

//右左双旋
void RL_Rotate(TreeNode** rootnode)
{
	LL_Rotate(&(*rootnode)->rightChild);
	RR_Rotate(rootnode);
}

void insertRootNode(TreeNode** rootnode, dataType data)
{
	if(*rootnode != NULL){
		perror("rootnode is not NULL");
		exit(1);
	}
	*rootnode = createTreeNode(data);
}

//插入树节点，先正常插入节点，再根据平衡因子判断是否需要调整
void insertTreeNode(TreeNode** rootnode, dataType data)
{
	if(*rootnode == NULL){
		*rootnode = createTreeNode(data);
		return;
	}

	if(data < (*rootnode)->data){
		insertTreeNode(&(*rootnode)->leftChild, data);
	}
	else if(data > (*rootnode)->data){
		insertTreeNode(&(*rootnode)->rightChild, data);
	}

	(*rootnode)->height = maxValue(getTreeHeight(&(*rootnode)->leftChild), getTreeHeight(&(*rootnode)->rightChild)) + 1;

	int balancer = getBalanceValue(rootnode);
	if(balancer > 1 && data < (*rootnode)->leftChild->data){
		LL_Rotate(rootnode);	//左左单旋
	}
	if(balancer > 1 && data > (*rootnode)->leftChild->data){
		LR_Rotate(rootnode);	//左右双旋
	}
	if(balancer < -1 && data < (*rootnode)->rightChild->data){
		RL_Rotate(rootnode);	//右左双旋
	}
	if(balancer < -1 && data > (*rootnode)->rightChild->data){
		RR_Rotate(rootnode);	//右有单旋
	}
}

//删除AVL树
void dropAVLTree(TreeNode** rootnode)
{
	if(*rootnode){
		dropAVLTree(&(*rootnode)->leftChild);
		dropAVLTree(&(*rootnode)->rightChild);
		free(*rootnode);
		*rootnode = NULL;
	}
}

//查找AVL树是否存在某值
int searchValue(TreeNode** rootnode, dataType value)
{
	if(*rootnode == NULL) return 0;
	if(value == (*rootnode)->data) return 1;
	if(value < (*rootnode)->data){
		searchValue(&(*rootnode)->leftChild, value);
	}
	else if(value > (*rootnode)->data){
		searchValue(&(*rootnode)->rightChild, value);
	}
}

//前序遍历
void proPrintAVLTree(TreeNode** rootnode)
{
	if(*rootnode){
		printf("%d\n", (*rootnode)->data);
		proPrintAVLTree(&(*rootnode)->leftChild);
		proPrintAVLTree(&(*rootnode)->rightChild);
	}
}

//中序遍历
void inoPrintAVLTree(TreeNode** rootnode)
{
	if(*rootnode){
		inoPrintAVLTree(&(*rootnode)->leftChild);
		printf("%d\n", (*rootnode)->data);
		inoPrintAVLTree(&(*rootnode)->rightChild);
	}
}

//后序遍历
void posPrintAVLTree(TreeNode** rootnode)
{
	if(*rootnode){
		posPrintAVLTree(&(*rootnode)->leftChild);
		posPrintAVLTree(&(*rootnode)->rightChild);
		printf("%d\n", (*rootnode)->data);
	}
}

int main()
{
	TreeNode* tree;
	initAVLTree(&tree);
	insertTreeNode(&tree, 15);
	insertTreeNode(&tree, 7);
	insertTreeNode(&tree, 20);
	insertTreeNode(&tree, 4);
	insertTreeNode(&tree, 9);
	insertTreeNode(&tree, 8);
	//dropAVLTree(&tree);
	proPrintAVLTree(&tree);
	//inoPrintAVLTree(&tree);
	//posPrintAVLTree(&tree);
	printf("%d\n",searchValue(&tree, 9));
	return 0;
}
