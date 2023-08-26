#include<stdio.h>
#include<stdlib.h>
#include<error.h>

typedef struct ListNode        //定义表节点
{
	int dataArea;
	struct ListNode* pNext;
}ListNode;

void initHeadPoint(ListNode** phead)        //初始化头指针
{
	*phead = NULL;
}

void createHeadNode(ListNode** phead)        //创建头节点
{
	ListNode* head = (ListNode*)malloc(sizeof(ListNode));
	if(head == NULL){
		perror("create HeadNode error!");
		exit(1);
	}
	head->pNext = head;                        //循环单链表的核心，尾节点的pNext需要指向头节点
	*phead = head;
}

ListNode* createListNode(int value)          //创建一个表节点
{
	ListNode* newnode = (ListNode*)malloc(sizeof(ListNode));
	if(newnode == NULL){
		perror("Create ListNode error!\n");
		return NULL;
	}
	newnode->dataArea = value;
	newnode->pNext = NULL;
	return newnode;
}

int insertListNode(ListNode** phead, int index, int value)      //插入一个表节点
{
	if(index < 1) return 0;
	else if(index == 1){
		ListNode* p = createListNode(value);
		p->pNext = (*phead)->pNext;
		(*phead)->pNext = p;
		return 1;
	}else{
		ListNode* tmp = *phead;
		int count = 1;
		while(tmp->pNext != *phead && count < index){
			tmp = tmp->pNext;
			count++;
		}	
		if(count == index){
			ListNode* p = createListNode(value);
			p->pNext = tmp->pNext;
			tmp->pNext = p;
		}else if(index - count < 2){
			ListNode* p = createListNode(value);
			p->pNext = *phead;                      //循环单链表的核心，尾节点的pNext需要指向头节点
			tmp->pNext = p;
			return 1;
		}else return 0;
	}
}

int deleteListNode(ListNode** phead, int index)        //删除一个表节点
{
	if(index < 1) return -1;
	if(index == 1 && (*phead)->pNext != *phead){
		ListNode* tmp = *phead;
		tmp->pNext = tmp->pNext->pNext;
		free(tmp);
		return 0;
	}else{
		ListNode* tmp = (*phead)->pNext, *pnow;
		int i = 1,len = getSCircularLinkedListLength(phead);
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

void printSCircularLinkedList(ListNode** phead)        //遍历循环单链表
{
	if(*phead == NULL){
		printf("SLinkedList is empty!\n");
	}else{
		ListNode* p = (*phead)->pNext;
		while(p && p != *phead){
			printf("%d\n", p->dataArea);
			p = p->pNext; 	
		}
	}
}

void displaySCircularLinkedListLength(ListNode** phead)        //显示链表大小
{
	if(*phead == NULL){
		printf("SLinkedList is empty!\n");
	}else{
		int count = 0;
		ListNode* p = (*phead)->pNext;
		while(p && p != *phead){
			p = p->pNext;
			count++;
		}
		printf("Length = %d\n", count);
	}	
}

int getSCircularLinkedListLength(ListNode** phead)        //获取链表大小
{
	if(phead == NULL) return -1;
	else{
		int count = 0;
		ListNode* p = (*phead)->pNext;
		while(p && p != *phead){
			p = p->pNext;
			count++;
		}
		return count;
	}	
}

int dropSCircularLinkedList(ListNode** phead)        //删除链表
{
	ListNode* tmp = (*phead)->pNext;
	while(tmp != *phead){
		ListNode* temp = tmp->pNext;
		free(tmp);
		tmp = temp;
	}
	tmp->pNext = NULL;
	free(tmp);
	return 0;
}

int main(int argc, char* argv[])
{
	ListNode* phead;
	initHeadPoint(&phead);
	createHeadNode(&phead);
	insertListNode(&phead,1,11);
	insertListNode(&phead,1,22);
	insertListNode(&phead,3,33);
	insertListNode(&phead,2,44);
	insertListNode(&phead,2,55);
	insertListNode(&phead,2,66);
	displaySCircularLinkedListLength(&phead);
	deleteListNode(&phead,5);
	printSCircularLinkedList(&phead);
	dropSCircularLinkedList(&phead);
	printSCircularLinkedList(&phead);
	displaySCircularLinkedListLength(&phead);
    return 0;
}
