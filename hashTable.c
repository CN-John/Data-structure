#include<stdio.h>
#include<stdlib.h>
#include<errno.h>

#define MAX_SIZE 100

typedef int keyType;
typedef int valueType;

typedef struct HashTable
{
	keyType key[MAX_SIZE];
	valueType value[MAX_SIZE];
	size_t size;
}HashTable;

void initHashTable(HashTable* table)
{
	table->size = 0;
}

valueType searchValue(HashTable* table, keyType key)
{
	if(table->size == 0){
		perror("HashTable is empty");
		exit(1);
	}
	for(int i = 0; i < table->size; i++){
		if(key == table->key[i]){
			return table->value[i];
		}
	}
	perror("not that value");
	exit(1);
}

keyType hashFunction(keyType key)
{
	return key % MAX_SIZE;
}

void AddElem(HashTable* table, keyType key, valueType value)
{
	if(table->size == MAX_SIZE){
		perror("HashTable is full");
		exit(1);
	}
	table->key[table->size] = key;
	table->value[table->size] = value;
	table->size++;
}

void deleteElem(HashTable* table, keyType key)
{
	if(searchValue(table, key)){
		int now;
		for(int i = 0; i < table->size; i++){
			if(key == table->key[i]){
				now = i;
			}
		}
		for(; now < table->size - 1; now++){
			table->key[now] = table->key[now + 1];
			table->value[now] = table->value[now + 1];
		}
		table->size--;
	}else{
		perror("not that value");
		exit(1);
	}
}

void dropHashTable(HashTable* table)
{
	table->size = 0;
}

void printHashTable(HashTable* table)
{
	printf("key|value\n");
	for(int i = 0; i < table->size; i++){
		printf(" %d|%d\n", table->key[i],table->value[i]);
	}
}

int getHashTableSize(HashTable* table)
{
	return table->size;
}

int main()
{
	HashTable tb;
	initHashTable(&tb);
	AddElem(&tb, 11, 1);
	AddElem(&tb, 22, 3);
	AddElem(&tb, 33, 5);
	AddElem(&tb, 44, 7);
	AddElem(&tb, 55, 9);
	deleteElem(&tb, 11);
	//dropHashTable(&tb);
	printHashTable(&tb);
	//printf("%d\n", searchValue(&tb, 55));
}
