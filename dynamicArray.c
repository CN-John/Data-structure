#include<stdio.h>
#include<stdlib.h>
#include<error.h>

typedef struct dynamicArray  //动态数组又名顺序表
{
	int* arr;  //存放整型数据
	int size;   //数组当前大小
	int capacity;  //容量
}dynamicArray;

void dynamicArray_Init(dynamicArray* da, int capacity)  //初始化数组
{
	da->arr = (int*)malloc(sizeof(int)*da->capacity);
	da->size = 0;
	da->capacity = capacity;
}

void dynamicArray_Append(dynamicArray* da, int value)  //追加元素
{
	if(da->size == da->capacity){  			//自动扩容
		da->capacity *= 2;
		da->arr = (int*)realloc(da->arr,sizeof(int)*da->capacity);
	}
	da->arr[da->size++] = value;
}

void dynamicArray_Insert(dynamicArray* da, int sub, int value) //插入元素
{
	if(sub > da->size || sub < 0){
		perror("Insert:sub error");
		exit(0);
	}
	else if(sub < da->size){                              //自动扩容
		if(da->size == da->capacity){
			da->capacity *= 2;
			da->arr = (int*)realloc(da->arr,sizeof(int)*da->capacity);
		}
		int i = da->size;
		for(i = da->size; i > sub; i--){
			da->arr[i] = da->arr[i - 1];
		}
		da->arr[sub] = value;
		da->size++;
	}
	else if(sub == da->size) dynamicArray_Append(da, value);
}

void dynamicArray_Delete(dynamicArray* da, int sub)       //按位置删除元素
{
	if(sub > da->size - 1 || sub < 0){
		perror("Delete:sub error");
		exit(0);
	}
	int i = sub;
	for(i = sub; i < da->size - 1; i++){
		da->arr[i] = da->arr[i + 1];
	}
	da->arr[i] = 0;
	da->size--;
}

void dynamicArray_Print(dynamicArray* da)             //遍历数组
{
	int i = 0;
	for(i = 0; i < da->size; i++){
		printf("%d ", da->arr[i]);
	}
	printf("\n");
}

int dynamicArray_getSize(dynamicArray* da)            //获取数组当前尺寸
{
	return da->size;
}

int dynamicArray_getValue(dynamicArray* da, int sub)   //根据位置获取值
{
	if(sub > da->size - 1 || sub < 0){
		perror("get sub error");
		exit(0);
	}
	return da->arr[sub];
}

int dynamicArray_findValue(dynamicArray* da, int value)   //根据元素寻找位置
{
	int i = 0;
	for(i = 0; i < da->size - 1; i++){
		if(value == da->arr[i])
			return i;
	}
	printf("cannot find that value...\n");
	return -1;
}

void dynamicArray_Destroy(dynamicArray* da)  //清除动态数组
{
	free(da->arr);
}

int main(int argc, char* argv[])
{
	dynamicArray A;
	dynamicArray_Init(&A, 6);
	dynamicArray_Append(&A, 1);
	dynamicArray_Append(&A, 2);
	dynamicArray_Append(&A, 3);
	dynamicArray_Append(&A, 4);
	dynamicArray_Delete(&A, 1);
	dynamicArray_Delete(&A, 0);
	dynamicArray_Insert(&A, 0, 10);
	dynamicArray_Print(&A);
	printf("%d\n",dynamicArray_getSize(&A));
	printf("%d\n", dynamicArray_getValue(&A, 1));
	printf("%d\n",dynamicArray_findValue(&A, 1));
	dynamicArray_Destroy(&A);
    return 0;
}

