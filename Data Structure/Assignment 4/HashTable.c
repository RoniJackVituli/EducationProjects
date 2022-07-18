//
//  HashTable.c
//  HW4
//
//  Created by Roni Jack Vituli on 25/12/2020.
//

#include "HashTable.h"


int constantStringHashFunction(char* str){
    return THREE;
}

int accumulateStringHashFunction(char* str){
    int sum = ZERO;
    if(str == NULL)
        return ZERO;
    for (int i = 0; str[i] != '\0'; i++)
        sum += (int)str[i];
    return sum;
}

int improvedHashFunction(char* str){
    long sum = ZERO;
    if(str == NULL)
        return ZERO;
    for (int i = 0; str[i] != '\0'; i++)
        sum += ((int)(str[i]))*pow(BASE, strlen(str) - 1 - i);
    return (int)sum;
}

HashTable* initTable(int tableSize, int hashFunction){
    //Build the hashtable.
    HashTable* ht = (HashTable*)malloc(sizeof(HashTable));
    if(ht == NULL)
        exit(1);
    ht->hashFunction = hashFunction;
    ht->tableSize = tableSize;
    ht->hashTable = (HashTableElement*)malloc(ht->tableSize * (sizeof(HashTableElement)));
    if(ht->hashTable == NULL){
        free(ht);
        exit(2);
    }
    for (int i = 0; i < tableSize; i++) {
        ht->hashTable[i].key = i;
        ht->hashTable[i].chain = BuildNode(NULL);
        if(ht->hashTable[i].chain == NULL){
            free(ht->hashTable);
            free(ht);
            exit(3);
        }
    }
    ht->numOfElements = ZERO;
    ht->cellsTaken = ZERO;
    return ht;
}

int hash(char* str, HashTable* ht){
    //return the uninq index for str.
    if(ht->hashFunction == ONE)
        return abs(constantStringHashFunction(str)) % ht->tableSize;
    else if(ht->hashFunction == TWO)
       return abs(accumulateStringHashFunction(str)) % ht->tableSize;
    else if(ht->hashFunction == THREE)
       return abs(improvedHashFunction(str)) % ht->tableSize;
    return ZERO;
}


int insert(HashTable* ht, char* str){
    //insert str to the hashtable
    ht->hashTable->key = hash(str, ht); // get index from hashfunction
    if(str == NULL || search(ht, str))
        return ZERO;
    ht->hashTable[ht->hashTable->key].chain = addToStart(ht->hashTable[ht->hashTable->key].chain, str);
    ht->numOfElements += ONE;
    ht->cellsTaken = updateCellsTaken(ht);
    return ONE;
}


int deleteStr(HashTable* ht, char* str){
    //delete str from hashtable.
    int flag = False;
    LinkedList* temp = NULL;
    if(str == NULL)
        return ZERO;
    int index = hash(str, ht); // get index from hashfunction
    for (temp = ht->hashTable[index].chain; temp != NULL && flag != True ; temp = temp->next) { // check if in cell have the str on the list
        if(strcmp(temp->data, str) == 0)
            flag = True;
    }
    if(flag){
        ht->hashTable[index].chain = DeleteElement(ht->hashTable[index].chain, str);
        ht->numOfElements -= ONE;
        ht->cellsTaken = updateCellsTaken(ht);
        return ONE;
    }
    return ZERO;
}

int search(HashTable* ht, char* str){
    //search str on hashtable.
    if(str == NULL)
        return ZERO;
    if(isInList(ht->hashTable[hash(str, ht)].chain, str))
        return True;
    return False;
}

int updateCellsTaken(HashTable* ht){
    //update how many cell taken on hashtable.
    int CellsTaken = 0;
    for(int i = 0; i < ht->tableSize; i++){
        if(ht->hashTable[i].chain->next != NULL)
            CellsTaken += 1;
    }
    return CellsTaken;
}

HashTable* FreeHash(HashTable* ht){
    
    for (int i = 0; i < ht->tableSize; i++){
        FreeList(ht->hashTable[i].chain);
    }
    free(ht->hashTable);
    free(ht);
    return NULL;
}
