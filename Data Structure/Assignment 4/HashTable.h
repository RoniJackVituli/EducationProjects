#ifndef HashTable_h
#define HashTable_h
#include "LinkedList.h"

#define BASE 31
#define HASH_FUNCTION 3

typedef struct HashTableElement HashTableElement;
enum numbers {ZERO, ONE, TWO, THREE, FOUR, FIFVE};

struct HashTableElement{
	int key;
	LinkedList* chain;
};

typedef struct HashTable HashTable;

struct HashTable{
	HashTableElement* hashTable;
	int hashFunction;
	int tableSize;
	int cellsTaken;
	int numOfElements;
};

int constantStringHashFunction(char* str);
int accumulateStringHashFunction(char* str);
int improvedHashFunction(char* str);

int hash(char* str, HashTable* ht);
HashTable* initTable(int tableSize, int hashFunction);
int insert(HashTable* ht, char* str);
int deleteStr(HashTable* ht, char* str);
int search(HashTable* ht, char* str);
int updateCellsTaken(HashTable* ht);
HashTable* FreeHash(HashTable* ht);
#endif /* Header_h */






























