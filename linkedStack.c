#include<stdio.h>
#include<stdlib.h>
#include<error.h>

typedef struct StackNode  //定义链栈节点
{
	int data;          //数据域，存储整型数据
	struct StackNode* pNext;   //指针域
}StackNode;

void createHeadNode(StackNode** phead)  //初始化表头
{
	*phead = NULL;
}

StackNode* createStackNode(int value)   //创建链栈节点
{
	StackNode* newnode = (StackNode*)malloc(sizeof(StackNode));
	if(newnode == NULL){
		perror("create StackNode error!\n");
		exit(1);
	}
	newnode->data = value;
	newnode->pNext = NULL;
	return newnode;
}

void pushStackNode(StackNode** phead, int value)    //压栈操作，以头插法模拟
{
	if(*phead){
		StackNode* tmp = createStackNode(value);
		tmp->pNext = *phead;
		*phead = tmp;
	}else{
		*phead = createStackNode(value);
	}
}

int linked_stackIsEmpty(StackNode** phead)	//判断栈空
{
	if(!*phead) return 1;
	else return 0;
}

int topLinkedStack(StackNode** phead)	  //查看栈顶元素
{
	if(*phead == NULL){
		perror("LinkedStack is empty");
		exit(1);
	}
	return (*phead)->data;
}

int popLinkedStack(StackNode** phead)	  //弹栈操作
{
	if(*phead){
		StackNode* tmp = *phead;
		*phead = tmp->pNext;
		int temp = tmp->data;
		free(tmp);
		return temp;
	}else{
		perror("LinkedStack is empty");
		exit(1);
	}
}

int getLinkedStackLength(StackNode** phead)	//获取链栈大小
{
	int temp = 0;
	StackNode* tmp = *phead;
	if(tmp == NULL) return 0;
	while(tmp){
		temp++;
		tmp = tmp->pNext;
	}
	return temp;
}

void printLinkedStack(StackNode** phead)	//遍历链栈
{
	StackNode* tmp = *phead;
	if(tmp == NULL){
		printf("LinkedStack is empty!\n");
		return;
	}
	while(tmp){
		printf("%d\n",tmp->data);
		tmp = tmp->pNext;
	}
}

int main(int argc, char* argv[])
{
	StackNode* phead;
	createHeadNode(&phead);
	pushStackNode(&phead,11);
	pushStackNode(&phead,22);
	pushStackNode(&phead,33);
	pushStackNode(&phead,44);
	pushStackNode(&phead,55);
	printLinkedStack(&phead);
	printf("%d\n",topLinkedStack(&phead));
	printf("%d\n",popLinkedStack(&phead));
	printLinkedStack(&phead);
	printf("%d\n",getLinkedStackLength(&phead));
    return 0;
}
