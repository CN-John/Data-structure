#include<stdio.h>
#include<stdlib.h>
#include<errno.h>

typedef char dataType;

typedef struct Vertex
{
	dataType data;
	struct Vertex* next;
}Vertex;

typedef struct AdjacencyList 	//无向图结构体
{
	int V;
	Vertex** Adj; 	//指针数组，每个指针对应一个链表
}UndiGraph;

Vertex* createVertex(dataType data)
{
	Vertex* tmp = (Vertex*)malloc(sizeof(Vertex));
	if(tmp == NULL){
		perror("create error");
		exit(1);
	}
	tmp->data = data;
	tmp->next = NULL;
	return tmp;
}

//初始化图，为指针数组及每个指针所指向区域分配内存
void initUndiGraph(UndiGraph* ugraph, int V)
{
	ugraph->V = V;
	ugraph->Adj = (Vertex**)malloc(sizeof(Vertex*)*V);
	for(int i = 0; i < ugraph->V; i++){
		ugraph->Adj[i] = (Vertex*)malloc(sizeof(Vertex));
		ugraph->Adj[i]->next = NULL;
	}
}

//如果找到对应顶点，返回顶点对于下标，否则返回-1
int searchGraphVertex(UndiGraph* ugraph, dataType data)
{
	int i = 0;
	while(ugraph->Adj[i]->data != data){
		i++;
	}
	if(i < ugraph->V) return i;
	return -1;
}

//插入顶点
void insertGraphVertex(UndiGraph* ugraph, dataType* data)
{
	for(int i = 0; i < ugraph->V; i++){
		ugraph->Adj[i]->data = data[i];
	}
}

//插入边
void insertGraphEdge(UndiGraph* ugraph, dataType data_1, dataType data_2)
{
	if(searchGraphVertex(ugraph, data_1) != -1 && searchGraphVertex(ugraph, data_2) != -1){
		Vertex* tmp = ugraph->Adj[searchGraphVertex(ugraph, data_1)];
		while(tmp->next != NULL){
			tmp = tmp->next;
		}
		tmp->next = createVertex(data_2);
		tmp = ugraph->Adj[searchGraphVertex(ugraph, data_2)];
		while(tmp->next != NULL){
			tmp = tmp->next;
		}
		tmp->next = createVertex(data_1);
	}else{
		perror("insert edge error");
		exit(1);
	}
}

//获取最大度数
int getMaxDegree(UndiGraph* ugraph)
{
	int cnt[ugraph->V];
	for(int i = 0; i < ugraph->V; i++){
		cnt[i] = 0;
		Vertex* tmp = ugraph->Adj[i];
		while(tmp->next != NULL){
			cnt[i]++;
			tmp = tmp->next;
		}
	}
	for(int i = 1; i < ugraph->V; i++){
		if(cnt[0] < cnt[i]){
			cnt[0] = cnt[i];
		}
	}
	return cnt[0];
}

//打印所有顶点
void printAllVertex(UndiGraph* ugraph)
{
	for(int i = 0; i < ugraph->V; i++){
		printf("%c ", ugraph->Adj[i]->data);
	}
}

//打印无向图的邻接表
void printAdjacencyList(UndiGraph* ugraph)
{
	for(int i = 0; i < ugraph->V; i++){
		printf("%c->",ugraph->Adj[i]->data);
		Vertex* tmp = ugraph->Adj[i]->next;
		while(tmp){
			printf("%c ", tmp->data);
			tmp = tmp->next;
		}
		printf("\n");
	}
}

int main()
{
	UndiGraph g;
	char* str = "ABCDE";
	initUndiGraph(&g, 5);
	insertGraphVertex(&g, str);
	insertGraphEdge(&g, 'A', 'B');
	insertGraphEdge(&g, 'A', 'C');
	insertGraphEdge(&g, 'B', 'E');
	insertGraphEdge(&g, 'B', 'D');
	//printf("%d",getMaxDegree(&g));
	printAdjacencyList(&g);
	//printAllVertex(&g);
	return 0;
}
