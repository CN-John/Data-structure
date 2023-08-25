#include<stdio.h>
#include<stdlib.h>

typedef struct stack //顺序栈结构体
{
	int* data;    //顺序表原型，存放整型数据
	int top;      //模拟栈顶指针，实现堆栈的核心
	int capacity; //栈容量
}Stack;

void initStack(Stack* sak, int capa)  //初始化栈
{
	sak->data = (int*)malloc(sizeof(int)*capa);
	sak->capacity = capa;
	sak->top = 0;
}

int stackIsFull(const Stack* sak)  //判断栈满
{
	return sak->top == sak->capacity;
}

int stackIsEmpty(const Stack* sak)  //判断栈空
{
	return sak->top == 0;
}

int stackPush(Stack* sak, int value)  //压栈
{
	if(stackIsFull(sak)) return 0;
	sak->data[sak->top++] = value;
	return 1;
}

int stackTop(Stack* sak)  //返回栈顶元素，不弹出
{
	if(stackIsEmpty(sak)) return 0;
	return sak->data[sak->top - 1];
}

int stackPop(Stack* sak)  //弹栈
{
	if(stackIsEmpty(sak)) return 0;
	int value;
	value = sak->data[--(sak->top)];
	return value;
}

void printStack(Stack* sak)  //遍历栈元素
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

