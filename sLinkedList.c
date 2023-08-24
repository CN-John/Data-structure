#include<stdio.h>
#include<stdlib.h>
#include<error.h>

typedef struct ListNode
{
	int dataArea;
	struct ListNode* pNext;
}ListNode;

void createHeadNode(ListNode** phead)
{
	*phead = NULL;
}

ListNode* createListNode(int value)
{
	ListNode* newnode = (ListNode*)malloc(sizeof(ListNode));
	if(newnode == NULL){
		perror("Create ListNode error!\n");
		return NULL;
	}
	newnode->dataArea = value;
	newnode->pNext = NULL;
}

int insertListNode(ListNode** phead, int index, int value)
{
	if(index < 1) return 0;
	else if(index == 1){
		ListNode* p = createListNode(value);
		p->pNext = *phead;
		*phead = p;
		return 1;
	}else{
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

int deleteListNode(ListNode** phead, int index)
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

void printSLinkedList(ListNode** phead)
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

void displaySLinkedListLength(ListNode** phead)
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

int getSLinkedListLength(ListNode** phead)
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

int dropSLinkedList(ListNode** phead)
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
	ListNode* phead;
	createHeadNode(&phead);
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

