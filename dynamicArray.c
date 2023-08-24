#include<stdio.h>
#include<stdlib.h>
#include<error.h>

typedef struct Array
{
	int* arr;
	int size;
	int capacity;
}Array;

void array_Init(Array* da, int capacity)
{
	da->arr = (int*)malloc(sizeof(int)*da->capacity);
	da->size = 0;
	da->capacity = capacity;
}

void array_Append(Array* da, int value)
{
	if(da->size == da->capacity){
		da->capacity *= 2;
		da->arr = (int*)realloc(da->arr,sizeof(int)*da->capacity);
	}
	da->arr[da->size++] = value;
}

void array_Insert(Array* da, int sub, int value)
{
	if(sub > da->size || sub < 0){
		perror("Insert:sub error");
		exit(0);
	}
	else if(sub < da->size){
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
	else if(sub == da->size) array_Append(da, value);
}

void array_Delete(Array* da, int sub)
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

void array_Print(Array* da)
{
	int i = 0;
	for(i = 0; i < da->size; i++){
		printf("%d ", da->arr[i]);
	}
	printf("\n");
}

int array_getSize(Array* da)
{
	return da->size;
}

int array_getValue(Array* da, int sub)
{
	if(sub > da->size - 1 || sub < 0){
		perror("get sub error");
		exit(0);
	}
	return da->arr[sub];
}

int array_findValue(Array* da, int value)
{
	int i = 0;
	for(i = 0; i < da->size - 1; i++){
		if(value == da->arr[i])
			return i;
	}
	printf("cannot find that value...\n");
	return -1;
}

void array_Destroy(Array* da)
{
	free(da->arr);
}

int main(int argc, char* argv[])
{
	Array A;
	array_Init(&A, 6);
	array_Append(&A, 1);
	array_Append(&A, 2);
	array_Append(&A, 3);
	array_Append(&A, 4);
	array_Delete(&A, 1);
	array_Delete(&A, 0);
	array_Insert(&A, 0, 10);
	array_Print(&A);
	printf("%d\n",array_getSize(&A));
	printf("%d\n", array_getValue(&A, 1));
	printf("%d\n",array_findValue(&A, 1));
	array_Destroy(&A);
    return 0;
}

