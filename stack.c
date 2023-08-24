#include<stdio.h>
#include<stdlib.h>

typedef struct stack
{
	int* data;
	int top;
	int capacity;
}Stack;

void initStack(Stack* sak, int capa)
{
	sak->data = (int*)malloc(sizeof(int)*capa);
	sak->capacity = capa;
	sak->top = 0;
}

int stackIsFull(const Stack* sak)
{
	return sak->top == sak->capacity;
}

int stackIsEmpty(const Stack* sak)
{
	return sak->top == 0;
}

int stackPush(Stack* sak, int value)
{
	if(stackIsFull(sak)) return 0;
	sak->data[sak->top++] = value;
	return 1;
}

int stackTop(Stack* sak)
{
	if(stackIsEmpty(sak)) return 0;
	return sak->data[sak->top - 1];
}

int stackPop(Stack* sak)
{
	if(stackIsEmpty(sak)) return 0;
	int value;
	value = sak->data[--(sak->top)];
	return value;
}

void printStack(Stack* sak)
{
	Stack* st = sak;
	while(st->top != 0){
		printf("%d\n",stackPop(sak));
	}
}
	
int main(int argc, char* argv[])
{
	Stack st;
	initStack(&st,3);
	stackPush(&st,11);
	stackPush(&st,22);
	stackPush(&st,33);
	//stackPush(&st,44);
	//printf("%d\n",stackTop(&st));
	stackPop(&st);
	stackPop(&st);
	printStack(&st);
    return 0;
}

