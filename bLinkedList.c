#include<stdio.h>
#include<stdlib.h>
#include<error.h>

typedef struct ListNode       //定义双链表结构体
{
	struct ListNode* pPrev;     //指向前一个节点
	int data;                   //数据域
	struct ListNode* pNext;     //指向后一个节点
}ListNode;

void initHeadTailPoint(ListNode** phead, ListNode** ptail)       //初始化头尾指针
{
	*phead = NULL;
	*ptail = NULL;
}

void createHeadTailNode(ListNode** phead, ListNode** ptail)      //创建头节点(尾节点)，初始头尾指针指向同一个节点
{
	ListNode* tmp = (ListNode*)malloc(sizeof(ListNode));
	if(tmp == NULL){
		perror("create HeadNode error!");
		exit(1);
	}
	tmp->pPrev = NULL;
	tmp->pNext = NULL;
	*phead = tmp;
	*ptail = tmp;
}

ListNode* createListNode(int value)          //创建一个节点
{
	ListNode* tmp = (ListNode*)malloc(sizeof(ListNode));
	if(tmp == NULL){
		perror("create ListNode error!");
		exit(1);
	}
	tmp->pPrev = NULL;
	tmp->pNext = NULL;
	tmp->data = value;
	return tmp;
}

int insertListNode(ListNode** phead, ListNode** ptail, int index, int value)  //按位置插入节点
{
	int count = 1;
	ListNode* tmp = (*phead)->pNext;
	if(index < 1 && index > getBLinkedListLength(phead)+1) return -1;
	ListNode* ins = createListNode(value);
	if(index == 1){                         //判断在头节点后一个节点插入
		if((*phead)->pNext == NULL){          //头节点后没有节点，需要移动尾指针
			(*phead)->pNext = ins;
			ins->pPrev = *phead;
			*ptail = ins;
			return 0;
		}else{                                //头节点后有节点，不需要移动尾指针
			ins->pNext = (*phead)->pNext;
			(*phead)->pNext = ins;
			ins->pPrev = *phead;
			ins->pNext->pPrev = ins;	
			return 0;
		}
	}else if(index > 1 && index <= getBLinkedListLength(phead)){     //判断在除头尾节点后以外的其他节点插入
		while(count < index - 1){
			count++;
			tmp = tmp->pNext;
		}
		ListNode* temp = tmp->pNext;
		ins->pNext = tmp->pNext;
		tmp->pNext = ins;
		ins->pPrev = temp->pPrev;
		temp->pPrev = ins;
		return 0;
	}else{                            //判断在为节点后插入，需要移动尾指针
		while(count < index - 1){
			count++;
			tmp = tmp->pNext;
		}
		tmp->pNext = ins;
		ins->pPrev = tmp;
		*ptail = ins;
		return 0;
	}
}

int deleteListNode(ListNode** phead, ListNode** ptail, int index)       //删除节点
{	
	int count = 1;
	ListNode* tmp = (*phead)->pNext;
	if(index < 1 && index > getBLinkedListLength(phead)+1) return -1;
	if(index == 1){
		if((*phead)->pNext == NULL) return -1;
		else{
			(*phead)->pNext = (*phead)->pNext->pNext;
			tmp->pNext->pPrev = *phead;
			free(tmp);
			return 0;
		}
	}else if(index > 1 && index < getBLinkedListLength(phead)){
		while(count < index - 1){
			count++;
			tmp = tmp->pNext;
		}
		ListNode* temp = tmp->pNext;
		tmp->pNext = temp->pNext;
		temp->pNext->pPrev = tmp;
		free(temp);
		return 0;
	}else{
		while(count < index - 1){
			count++;
			tmp = tmp->pNext;
		}
		*ptail = tmp;
		tmp = tmp->pNext;
		free(tmp);
		(*ptail)->pNext =NULL;
		return 0;
	}
}

int getBLinkedListLength(ListNode** phead)      //获取双链表大小
{
	int count = 0;
	if(*phead == NULL){
		perror("not that BLinkedList!");
		exit(1);
	}
	ListNode* tmp = (*phead)->pNext;
	while(tmp){
		tmp = tmp->pNext;
		count++;
	}
	return count;
}

void sequencePrintBLinkedList(ListNode** phead)      //顺序遍历双链表
{
	ListNode* tmp = (*phead)->pNext;
	while(tmp){
		printf("%d\n",tmp->data);
		tmp = tmp->pNext;
	}
}

void reversedPrintBLinkedList(ListNode** ptail)    //逆序遍历双链表
{
	ListNode* tmp = *ptail;
	while(tmp->pPrev != NULL){
		printf("%d\n",tmp->data);
		tmp = tmp ->pPrev;
	}
}

int dropBLinkedList(ListNode** phead)      //清除双链表
{
	ListNode* tmp;
	while(*phead){
		tmp = (*phead)->pNext;
		free(*phead);
		*phead = tmp;
	}
}

int main(int argc, char* argv[])
{
	ListNode* phead;
	ListNode* ptail;
	initHeadTailPoint(&phead, &ptail);
	createHeadTailNode(&phead,&ptail);
	insertListNode(&phead, &ptail, 1, 11);
	insertListNode(&phead, &ptail, 1, 22);
	insertListNode(&phead, &ptail, 2, 33);
	insertListNode(&phead, &ptail, 4, 44);
	insertListNode(&phead, &ptail, 4, 55);
	insertListNode(&phead, &ptail, 4, 66);
	deleteListNode(&phead, &ptail, 6);
	printf("%d\n",getBLinkedListLength(&phead));
	reversedPrintBLinkedList(&ptail);
	dropBLinkedList(&phead);
	printf("%d\n",getBLinkedListLength(&phead));
    return 0;
}
