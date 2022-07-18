#include "LinkedList.h"


LinkedList * BuildNode(char* str){
    LinkedList* node = (LinkedList*) malloc(sizeof(LinkedList));
    node->data = str;
    node->next = NULL;
    return node;
}

LinkedList * addToStart(LinkedList* head, char* str){
    LinkedList* new_ele = BuildNode(str);
    new_ele->next = head;
    return new_ele;
}

LinkedList * DeleteElement(LinkedList * head, char* str){
    LinkedList *previous = head, *current = head->next;
    if (head == NULL)
        return head;
    if (strcmp(head->data, str) == 0){
        LinkedList *temp = head;
        head = head->next;
        free(temp);
        return head;
    }
    while (previous!=NULL){
        if (previous->data == str)
            break;
        current = previous;
        previous = previous->next;
    }
    if (previous != NULL)
        current->next = previous->next;
    free(previous);
    return head;
}

int isInList(LinkedList* head, char* str){
    LinkedList* temp = head;
    for(; temp != NULL ; temp = temp->next)
        if((temp->data != NULL) && (strcmp(temp->data, str) == 0))
            return True;
    return False;
}

void PrintList(LinkedList* head){
    LinkedList* temp = head;
    if(temp == NULL){
        printf("The list is empty\n");
    }else{
        while (temp != NULL) {
            printf("\t%s\n",temp->data);
            temp = temp->next;
        }
    }
}

LinkedList* FreeList(LinkedList* head){
    LinkedList* temp;
    while (head != NULL)
    {
        temp = head;
        head = head->next;
        free(temp->data);
        free(temp);
    }
    return NULL;
}
