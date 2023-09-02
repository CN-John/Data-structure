#include<stdio.h>
#include<stdlib.h>
#include<error.h>

typedef struct QueueNode      //队节点
{
	int data;
	struct QueueNode* pNext;
}QueueNode;

typedef struct LinkedQueue    //链队
{
	QueueNode* front;
	QueueNode* rear;
	int capacity;
}LinkedQueue;

QueueNode* createQueueNode(int value)      //创建一个队节点
{	
	QueueNode* qnode = (QueueNode*)malloc(sizeof(QueueNode));
	if(qnode == NULL){
		perror("create QueueNode error");
		exit(1);
	}
	qnode->data = value;
	qnode->pNext = NULL;
}

void initLinkedQueue(LinkedQueue* linkedque, int capa)      //初始化链队
{
	linkedque->front = NULL;
	linkedque->rear = NULL;
	linkedque->capacity = capa;
}

int linkedQueueIsFull(LinkedQueue* linkedque)          //判断队满
{
	int cnt = 0;
	QueueNode* tmp = linkedque->front;
	while(tmp != NULL){
		tmp = tmp->pNext;
		cnt++;
	}
	if(cnt == linkedque->capacity) return 1;
	return 0;
}

int linkedQueueIsEmpty(LinkedQueue* linkedque)        //判断队空
{
	if(linkedque->front == NULL) return 1;
	return 0;
}

void enLinkedQueue(LinkedQueue* linkedque, int value)    //入队
{
	if(linkedQueueIsFull(linkedque)){
		perror("LinkedQueue is full");
		exit(1);
	}
	QueueNode* tmp = createQueueNode(value);
	if(linkedque->front == NULL){
		linkedque->front = tmp;
		linkedque->rear = tmp;
	}else{
		linkedque->rear->pNext = tmp;
		linkedque->rear = tmp;
	}
}

void deLinkedQueue(LinkedQueue* linkedque)          //出队
{
	if(linkedQueueIsEmpty(linkedque)){
		perror("LinkedQueue is empty");
		exit(1);
	}
	QueueNode* tmp = linkedque->front;
	linkedque->front = tmp->pNext;
	free(tmp);
}

void printLinkedQueue(LinkedQueue* linkedque)      //遍历链队
{
	if(linkedQueueIsEmpty(linkedque)){
		perror("LinkedQueue is empty");
		exit(1);
	}
	int cnt = 0;
	QueueNode* tmp = linkedque->front;
	while(tmp != NULL){
		printf("%d\n",tmp->data);
		tmp = tmp->pNext;
	}
}

int getLinkedQueueSize(LinkedQueue* linkedque)        //获取链队大小
{
	int cnt = 0;
	QueueNode* tmp = linkedque->front;
	while(tmp != NULL){
		tmp = tmp->pNext;
		cnt++;
	}
	return cnt;
}

int main(int argc, char* argv[])
{
	LinkedQueue qu;
	initLinkedQueue(&qu, 5);
	enLinkedQueue(&qu,11);
	enLinkedQueue(&qu,22);
	enLinkedQueue(&qu,33);
	enLinkedQueue(&qu,44);
	enLinkedQueue(&qu,55);
	//enLinkedQueue(&qu,66);
	deLinkedQueue(&qu);
	printLinkedQueue(&qu);
	printf("%d\n",getLinkedQueueSize(&qu));
    return 0;
}
