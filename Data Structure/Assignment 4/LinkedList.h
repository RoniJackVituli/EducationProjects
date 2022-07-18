#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef enum {False = 0, True} BOOL;
typedef struct LinkedList LinkedList;

struct LinkedList {
	char* data;
	LinkedList *next;
};

void PrintList(LinkedList *);
LinkedList * BuildNode(char*);
LinkedList * addToStart(LinkedList *, char*);
LinkedList * FreeList(LinkedList *);
LinkedList * DeleteElement(LinkedList *, char*);
int isInList(LinkedList*, char*);
