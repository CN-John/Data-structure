#include<stdio.h>
#include<stdlib.h>
#include<error.h>

typedef int dataType;           //数据类型

typedef struct TreeNode         //树节点
{
	dataType data;
	struct TreeNode* leftChild;
	struct TreeNode* rightChild;
}TreeNode;

typedef struct BinarySearchTree    //二叉搜索树BST
{
	TreeNode* rootNode;
	int nodeNum;
}BST;

TreeNode* createTreeNode(dataType value)    //创建节点
{
	TreeNode* tmp = (TreeNode*)malloc(sizeof(TreeNode));
	if(tmp == NULL){
		perror("create RootNode error\n");
		exit(1);
	}
	tmp->data = value;
	tmp->leftChild = NULL;
	tmp->rightChild = NULL;
	return tmp;
}

void initBinarySearchTree(BST* bsTree)        //初始化树
{
	bsTree->rootNode = NULL;
	bsTree->nodeNum = 0;
}

void insertRootNode(BST* bsTree, dataType data)      //插入根节点
{
	if(bsTree->rootNode != NULL){
		perror("RootNode is not NULL\n");
		exit(1);
	}
	bsTree->rootNode = createTreeNode(data);
	bsTree->nodeNum = 1;
}

void insertTreeNode(TreeNode* rootnode, dataType data)    //插入树节点
{
	if(data < rootnode->data){
		if(rootnode->leftChild == NULL){
			rootnode->leftChild = createTreeNode(data);
			return;
		}
		insertTreeNode(rootnode->leftChild, data);
	}
	if(data > rootnode->data){
		if(rootnode->rightChild == NULL){
			rootnode->rightChild = createTreeNode(data);
			return;
		}
		insertTreeNode(rootnode->rightChild, data);
	}	
}

void dropBinarySearchTree(TreeNode* rootnode)        //删除二叉搜索树
{
	if(rootnode){
		dropBinarySearchTree(rootnode->leftChild);
		dropBinarySearchTree(rootnode->rightChild);
		free(rootnode);
	}	
}

void proPrintBinarySearchTree(TreeNode* rootnode)      //前序遍历
{
	if(rootnode){
		printf("%d ",rootnode->data);
		proPrintBinarySearchTree(rootnode->leftChild);
		proPrintBinarySearchTree(rootnode->rightChild);
	}
}

void inoPrintBinarySearchTree(TreeNode* rootnode)      //中序遍历，BST的特性决定中序遍历的结果是从小到大排序
{
	if(rootnode){
		inoPrintBinarySearchTree(rootnode->leftChild);
		printf("%d ",rootnode->data);
		inoPrintBinarySearchTree(rootnode->rightChild);
	}
}

void posPrintBinarySearchTree(TreeNode* rootnode)      //后序遍历
{
	if(rootnode){
		posPrintBinarySearchTree(rootnode->leftChild);
		posPrintBinarySearchTree(rootnode->rightChild);
		printf("%d ",rootnode->data);
	}
}

dataType findMaxValue(TreeNode* rootnode)        //获取最大值
{
	if(rootnode->rightChild){
		findMaxValue(rootnode->rightChild);
	}else 
		return rootnode->data;
}

dataType findMinValue(TreeNode* rootnode)       //获取最小值
{
	if(rootnode->leftChild){
		findMinValue(rootnode->leftChild);
	}else 
		return rootnode->data;	
}

int findValue(TreeNode* rootnode, dataType data)    //查看当前树有无该节点
{
	if(rootnode == NULL) return 0;
	if(rootnode->data == data) return 1;
	if(findValue(rootnode->leftChild, data)) return 1;
	if(findValue(rootnode->rightChild, data)) return 1;
	return 0;
}

int main(int argc, char* argv[])
{
	BST tree;
	initBinarySearchTree(&tree);
	insertRootNode(&tree, 20);
	insertTreeNode(tree.rootNode, 10);
	insertTreeNode(tree.rootNode, 5);
	insertTreeNode(tree.rootNode, 30);
	insertTreeNode(tree.rootNode, 15);
	insertTreeNode(tree.rootNode, 25);
	insertTreeNode(tree.rootNode, 40);
	proPrintBinarySearchTree(tree.rootNode);
	printf("\n");
	inoPrintBinarySearchTree(tree.rootNode);
	printf("\n");
	posPrintBinarySearchTree(tree.rootNode);
	printf("\n");
	printf("%d\n",findMaxValue(tree.rootNode));
	printf("%d\n",findMinValue(tree.rootNode));
	printf("%d\n",findValue(tree.rootNode, 10));
	dropBinarySearchTree(tree.rootNode);
    return 0;
}
