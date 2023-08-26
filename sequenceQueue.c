#include<stdio.h>
#include<stdlib.h>
#include<error.h>

typedef struct Queue      //定义队列结构体
{
	int* data;            //顺序表模拟
	int capacity;
	int front;
	int rear;
}Queue;

void initQueue(Queue* qu, int capa)        //初始化队列
{
	if(qu == NULL){
		perror("No that queue");
		exit(1);
	}
	qu->data =(int*)malloc(sizeof(int)*capa);
	qu->capacity = capa;
	qu->front = 0;
	qu->rear = 0;
}

int enQueue(Queue* qu, int value)        //入队
{
	if(queueIsFull(qu)){
		perror("Queue full");
		exit(1);
	}
	qu->data[qu->rear++] = value;
	return value;
}

int deQueue(Queue* qu)        //出队
{
	if(queueIsEmpty(qu)){
		perror("Queue empty");
		exit(1);
	}
	int tmp = qu->data[qu->front], i;
	for(i = 0; i < (qu->rear) - 1; i++){
		qu->data[i] = qu->data[i + 1];
	}
	qu->rear--;
	return tmp;
}

int queueIsFull(Queue* qu)        //判断队满
{
	if(qu->front == qu->capacity){
		return 1;
	}return 0;	
}

int queueIsEmpty(Queue* qu)        //判断队空
{
	if(qu->front == qu->rear){
		return 1;
	}return 0;
}

void printQueue(Queue* qu)        //遍历队元素
{
	int i = 0;
	if(queueIsEmpty(qu)){
		perror("Queue empty");
		exit(1);
	}
	while(i < qu->rear){
		printf("%d\n",qu->data[i]);
		i++;
	}
}

void dropQueue(Queue* qu)        //清空队元素
{
	while(qu->rear){
		deQueue(qu);
	}	
}

int main(int argc, char* argv[])
{
	Queue q;
	initQueue(&q, 5);
	enQueue(&q, 11);
	enQueue(&q, 22);
	enQueue(&q, 33);
	enQueue(&q, 44);
	printQueue(&q);
	deQueue(&q);
	dropQueue(&q);
	printQueue(&q);
    return 0;
}
