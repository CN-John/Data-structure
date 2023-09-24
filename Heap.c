#include<stdio.h>
#include<stdlib.h>
#include<errno.h>

typedef int dataType; 

typedef struct Heap 	//堆结构体
{
	dataType* data;
	int capacity;
	int size;
}Heap;

void swap(dataType *a, dataType *b) {
    dataType temp = *a;
    *a = *b;
    *b = temp;
}

void permeateUp(Heap* heap, int index)
{
	dataType tmp;
	tmp = heap->data[index - 1];
	heap->data[index - 1] = heap->data[index/2 - 1];
	heap->data[index/2 - 1] = tmp;
}

void permeateDown(Heap* heap, int i) 	//向下调整
{
	int leftChild = i*2 + 1;
	int rightChild = i*2 + 2;
	if(heap->data[i] > heap->data[leftChild] && leftChild < heap->size){
		swap(&heap->data[i], &heap->data[leftChild]);
		permeateDown(heap, leftChild);
	}else if(heap->data[i] > heap->data[rightChild] && rightChild < heap->size){
		swap(&heap->data[i], &heap->data[rightChild]);
		permeateDown(heap, rightChild);
	}else return;
}

void cover(Heap* heap, int index, dataType temp)
{
	heap->data[index/2 - 1] = temp;
}

void initHeap(Heap* heap, int capa)
{
	heap->data = (int*)malloc(sizeof(int)*capa);
	heap->capacity = capa;
	heap->size = 0;
}

void insertMinHeap(Heap* heap, dataType data) 	//向堆插入元素
{
	if(heap->size == heap->capacity){
		perror("heap is full");
		exit(1);
	}
	heap->data[heap->size] = data;
	heap->size++;
	int index = heap->size;
	dataType temp = data;
	while(index > 1 && temp < heap->data[index/2 - 1]){
		permeateUp(heap, index);
		temp = heap->data[index/2 - 1];
		index = index/2;
	}
}

dataType deleteMinValue(Heap* heap) 	//删除最小元素并获取，也就是堆顶元素，删除后需要先恢复完全二叉树的结构
{									//再判断是否还满足堆的性质，否则进行调整	
	int value = heap->data[0];		
	int index = heap->size;
	dataType temp = heap->data[index - 1];
	while(index > 1){
		dataType tmp = heap->data[index/2 - 1];
		cover(heap, index, temp);
		index = index/2;
		temp = tmp;
	}
	heap->size--;
	permeateDown(heap, 0);
	return value;
}

void changValue(Heap* heap, dataType data, dataType newdata) 	//将堆中某值进行调整
{
	int i = 0;
	while(heap->data[i] != newdata && i < heap->size){
		if(heap->data[i] == data){
			heap->data[i] = newdata;
			int index = i + 1;
			dataType temp = newdata;
			while(index > 1 && temp < heap->data[index/2 - 1]){
				permeateUp(heap, index);
				temp = heap->data[index/2 - 1];
				index = index/2;
			}
		}
		i++;
	}
}

void clearHeap(Heap* heap)
{
	heap->size = 0;
}

void dropHeap(Heap* heap)
{
	free(heap->data);
}

dataType getMinValue(Heap* heap)
{
	if(heap->size == 0){
		perror("heap is empty");
		exit(1);
	}
	return heap->data[0];
}

void printHeap(Heap* heap)
{
	if(heap->size == 0){
		perror("heap is empty");
		exit(1);
	}
	for(int i = 0; i < heap->size; i++){
		printf("%d ", heap->data[i]);
	}
}

//堆排序
void heapSort(Heap* heap)
{
	for(int i = 0; i < heap->size; i++){
		printf("%d ",deleteMinValue(heap));
	}
}

int main()
{
	Heap h;
	initHeap(&h, 20);
	insertMinHeap(&h, 10);
	insertMinHeap(&h, 5);
	insertMinHeap(&h, 15);
	insertMinHeap(&h, 20);
	insertMinHeap(&h, 9);
	insertMinHeap(&h, 22);
	insertMinHeap(&h, 6);
	//heapSort(&h);
	//deleteMinValue(&h);
	//changValue(&h, 22, 1);
	//clearHeap(&h);
	//dropHeap(&h);
	printHeap(&h);
	return 0;
}
