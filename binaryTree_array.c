#include<stdio.h>
#include<stdlib.h>
#include<errno.h>

#define MAX_NUM 100

typedef int dataType;

//树节点
typedef struct TreeNode
{
	dataType data;
	int parent;
	int Lchild;
	int Rchild;
}TreeNode;

//二叉树结构体
typedef struct BiTree
{
	TreeNode Tnode[MAX_NUM];
	int nodeNum;
}BiTree;


//初始化二叉树
void initBinaryTree(BiTree* bitree)
{
	bitree->nodeNum = 0;
}

//初始化树节点
void initTreeNode(BiTree* bitree, dataType data, int prnt)
{
	bitree->Tnode[bitree->nodeNum].data = data;
	bitree->Tnode[bitree->nodeNum].parent = prnt;
	bitree->Tnode[bitree->nodeNum].Lchild = 0;
	bitree->Tnode[bitree->nodeNum].Rchild = 0;
	bitree->nodeNum++;
}

//插入根节点
void insertRootNode(BiTree* bitree, dataType data)
{
	bitree->Tnode[0].data = data;
	bitree->Tnode[0].parent = -1;
	bitree->Tnode[0].Lchild = bitree->Tnode[0].Rchild = 0;
	bitree->nodeNum++;
}

//插入树节点
void insertTreeNode(BiTree* bitree, dataType data, int prnt, int LorR)
{	
	if(bitree->nodeNum < prnt + 1){
		perror("insert TreeNode error");
		exit(1);
	}else{
		if(LorR == -1){
			if(!bitree->Tnode[prnt].Lchild){
				initTreeNode(bitree, data, prnt);
				return;
			}
		}
		if(LorR == 1){
			if(!bitree->Tnode[prnt].Rchild){
				initTreeNode(bitree, data, prnt);
				return;
			}
		}
	}
}

//遍历二叉树
void printBinaryTree(BiTree* bitree)
{
	for(int i = 0; i < bitree->nodeNum; i++){
		printf("%d\n", bitree->Tnode[i].data);
	}
}

//输出此节点的值
void printTreeNode(BiTree* bitree, int prnt)
{
	if(prnt > bitree->nodeNum){
		perror("print error");
		exit(1);
	}
	printf("%d\n", bitree->Tnode[prnt].data);
}

//输出双亲节点的值
void printParent(BiTree* bitree, int prnt)
{
	if(prnt > bitree->nodeNum){
		perror("print error");
		exit(1);
	}
		printf("%d\n", bitree->Tnode[bitree->Tnode[prnt].parent].data);
}

int main()
{
	BiTree tree;
	initBinaryTree(&tree);
	insertRootNode(&tree, 11);
	insertTreeNode(&tree, 22, 0, -1);
	insertTreeNode(&tree, 33, 0, 1);
	insertTreeNode(&tree, 44, 2, -1);
	insertTreeNode(&tree, 55, 2, 1);
	insertTreeNode(&tree, 66, 4, -1);
	insertTreeNode(&tree, 77, 4, 1);
	printBinaryTree(&tree);
	printf("%d\n",tree.nodeNum);
	printTreeNode(&tree, 5);
	printParent(&tree, 5);
	return 0;
}
