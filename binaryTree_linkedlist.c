#include<stdio.h>
#include<stdlib.h>
#include<error.h>

typedef int dataType;

typedef struct TreeNode               //树节点
{
	dataType data;                      //数据域
	struct TreeNode* leftChild;         //左儿子
	struct TreeNode* rightChild;        //右儿子
	int tag;                            //唯一标识一个树节点
}TreeNode;

typedef struct BinaryTree              //二叉树
{
	TreeNode* rootNode;
	int nodeNum;
}BinaryTree;

TreeNode* createTreeNode(dataType value, int tag)          //创建树节点
{
	TreeNode* tmp = (TreeNode*)malloc(sizeof(TreeNode));
	if(tmp == NULL){
		perror("create TreeNode error");
		exit(1);
	}
	tmp->data = value;
	tmp->leftChild = NULL;
	tmp->rightChild = NULL;
	tmp->tag = tag;
	return tmp;
}

void initBinaryTree(BinaryTree* bitree)              //初始化一颗树
{
	bitree->rootNode = NULL;
	bitree->nodeNum = 0;
}

void insertRootNode(BinaryTree* bitree, dataType value, int tag)      //插入根节点
{
	if(bitree->rootNode != NULL){
		perror("insert rootNode error");
		exit(1);
	}
	bitree->rootNode = createTreeNode(value, tag);
	bitree->nodeNum = 1;
}

TreeNode* searchTreeNode(TreeNode* rootnode, int target)          //根据tag寻找数据点
{
	TreeNode* trgt = rootnode;
	if(trgt == NULL) return NULL;
	if(trgt->tag == target) return trgt;
	TreeNode* leftchild = searchTreeNode(trgt->leftChild, target);
	if(leftchild != NULL) return leftchild;
	TreeNode* rightchild = searchTreeNode(trgt->rightChild, target);
	if(rightchild != NULL) return rightchild;
	return NULL;
}

TreeNode* searchValueTreeNode(TreeNode* rootnode, dataType value)      //根据数据域中的值寻找树节点
{
	TreeNode* trgt = rootnode;
	if(trgt == NULL) return NULL;
	if(trgt->data == value) return trgt;
	TreeNode* leftchild = searchValueTreeNode(trgt->leftChild, value);
	if(leftchild != NULL) return leftchild;
	TreeNode* rightchild = searchValueTreeNode(trgt->rightChild, value);
	if(rightchild != NULL) return rightchild;
	return NULL;
}

int  insertTreeNode(TreeNode* rootnode, dataType value, int tag, int parent, int index)        //插入树节点
{
	TreeNode* prnt = searchTreeNode(rootnode, parent);
	if(prnt == NULL){
		perror("insert TreeNode error, not that parent");
		return -1;
	}
	if(index == 0){
		if(prnt->leftChild != NULL){
			printf("%d's leftchild is not NULL\n", prnt->tag);
			return -1;
		}
		TreeNode* tmp = createTreeNode(value, tag);
		prnt->leftChild = tmp;
		return 0;
	}else{
		if(prnt->rightChild != NULL){
			printf("%d's rightchild is not NULL\n", prnt->tag);
			return -1;
		}
		TreeNode* tmp = createTreeNode(value, tag);
		prnt->rightChild = tmp;
		return 0;
	}
}

void proPrintBinaryTree(TreeNode* rootnode)              //前序遍历，根节点->左子树->右子树
{
	if(rootnode){
		printf("%d ",rootnode->data);
		proPrintBinaryTree(rootnode->leftChild);
		proPrintBinaryTree(rootnode->rightChild);
	}
}

void inoPrintBinaryTree(TreeNode* rootnode)              //中序遍历，左子树->根节点->右子树
{
	if(rootnode){
		inoPrintBinaryTree(rootnode->leftChild);
		printf("%d ",rootnode->data);
		inoPrintBinaryTree(rootnode->rightChild);
	}
}

void posPrintBinaryTree(TreeNode* rootnode)              //后序遍历，左子树->右子树->根节点
{
	if(rootnode){
		posPrintBinaryTree(rootnode->leftChild);
		posPrintBinaryTree(rootnode->rightChild);
		printf("%d ",rootnode->data);
	}
}

void dropBinaryTree(TreeNode* rootnode)                //删除二叉树
{
	if(rootnode == NULL) return;
	dropBinaryTree(rootnode->leftChild);
	dropBinaryTree(rootnode->rightChild);
	free(rootnode);
}

int main(int argc, char* argv[])
{
	BinaryTree tree;
	initBinaryTree(&tree);
	insertRootNode(&tree, 11, 0);
	insertTreeNode(tree.rootNode, 22, 1, 0, 0);
	insertTreeNode(tree.rootNode, 33, 2, 0, 1);
	insertTreeNode(tree.rootNode, 44, 3, 1, 0);  
	insertTreeNode(tree.rootNode, 55, 4, 1, 1);
	insertTreeNode(tree.rootNode, 66, 5, 2, 1);
	insertTreeNode(tree.rootNode, 77, 6, 3, 0);
	insertTreeNode(tree.rootNode, 88, 7, 1, 1);
	insertTreeNode(tree.rootNode, 99, 8, 9, 1);
	proPrintBinaryTree(tree.rootNode);
	printf("\n");
	inoPrintBinaryTree(tree.rootNode);
	printf("\n");
	posPrintBinaryTree(tree.rootNode);
	printf("\n");
	printf("%d\n", searchValueTreeNode(tree.rootNode, 66)->tag);
	dropBinaryTree(tree.rootNode);
	//proPrintBinaryTree(tree.rootNode);
    return 0;
}
//				    11
//				   /  \
//				  22  33
//				 /  \   \
//				44  55	66
//			       /
//			      77		
