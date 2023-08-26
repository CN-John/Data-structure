#include<stdio.h>
#include<stdlib.h>
#include<error.h>

typedef struct ListNode  //表节点结构体
{
	int dataArea;   	 //数据域
	struct ListNode* pNext;  //指针域
}ListNode;

void initHeadPoint(ListNode** phead)  //传入头指针的地址，初始化头指针
{
	*phead = NULL;
}

/*
void createHeadNode(ListNode** phead)  //创建初始化头节点
{
      ListNode* head = (ListNode*)malloc(sizeof(ListNode));
      if(head == NULL){
          perror("create HeadNode error!");
          exit(1);
      }
      head->pNext = NULL;
      *phead = head;
}
*/

ListNode* createListNode(int value)    //创建表节点
{
	ListNode* newnode = (ListNode*)malloc(sizeof(ListNode));
	if(newnode == NULL){     //申请内存失败
		perror("Create ListNode error!\n");
		return NULL;
	}
	newnode->dataArea = value;
	newnode->pNext = NULL;
}

int insertListNode(ListNode** phead, int index, int value)  //根据序号插入表节点
{
	if(index < 1) return 0;  //插入位置在头节点及以前的位置，出错
	else if(index == 1){     //在头节点后插入
		ListNode* p = createListNode(value);
		p->pNext = *phead;
		*phead = p;
		return 1;
	}else{                   //在其余位置插入
		ListNode* tmp = *phead;
		int count = 1;
		while(tmp && count < index - 1){
			tmp = tmp->pNext;
			count++;
		}	
		if(index - count < 3){
			ListNode* p = createListNode(value);
			p->pNext = tmp->pNext;
			tmp->pNext = p;
			return 1;
		}else return 0;
	}
}

int deleteListNode(ListNode** phead, int index)  //按序号删除表节点
{
	if(index < 1) return -1;
	if(index == 1){
		ListNode* tmp = *phead;
		*phead = (*phead)->pNext;
		free(tmp);
		return 0;
	}else{
		ListNode* tmp = *phead, *pnow;
		int i = 2,len = getSLinkedListLength(&phead);
		if(index > len) return -1;
		else{
			do{
				pnow = tmp;
				tmp = tmp->pNext;
				i++;
			}while(i < index);
			pnow->pNext = tmp->pNext;
			free(tmp);
			return 0;
		}
	}
}

void printSLinkedList(ListNode** phead)  //遍历单链表
{
	if(*phead == NULL){
		printf("SLinkedList is empty!\n");
	}else{
		ListNode* p = *phead;
		while(p){
			printf("%d\n", p->dataArea);
			p = p->pNext; 	
		}
	}
}

void displaySLinkedListLength(ListNode** phead)  //打印链表大小
{
	if(*phead == NULL){
		printf("SLinkedList is empty!\n");
	}else{
		int count = 0;
		ListNode* p = *phead;
		while(p){
			p = p->pNext;
			count++;
		}
		printf("Length = %d\n", count);
	}	
}

int getSLinkedListLength(ListNode** phead)   //获取链表大小
{
	if(&phead == NULL) return -1;
	else{
		int count = 0;
		ListNode* p = *phead;
		while(p){
			p = p->pNext;
			count++;
		}
		return count;
	}	
}

int dropSLinkedList(ListNode** phead) //删除单链表
{
	ListNode* tmp;
	while(*phead){
		tmp = (*phead)->pNext;
		free(*phead);
		*phead = tmp;
	}
	return 0;
}

int main(int argc, char* argv[])
{
	ListNode* phead;  //定义头指针
	initHeadPoint(&phead);
	//createHeadNode(&phead);
	insertListNode(&phead,1,11);
	insertListNode(&phead,1,22);
	insertListNode(&phead,3,33);
	insertListNode(&phead,2,44);
	insertListNode(&phead,2,55);
	insertListNode(&phead,2,66);
	deleteListNode(&phead,1);
	//dropSLinkedList(&phead);
	printSLinkedList(&phead);
	displaySLinkedListLength(&phead);
    return 0;
}

