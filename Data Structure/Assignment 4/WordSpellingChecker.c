#include "WordSpellingChecker.h"
#define ALPHA 26
#define CHECKS 5


int isWordInDictionary(HashTable* dictionaryTable, char* word){
    //check if the word in the dict
    if(word == NULL)
        return False;
    if(search(dictionaryTable, word))
        return True;
    return False;
}

LinkedList* addSpaceCheck(HashTable* dictionaryTable, char* word){
    //function bulid space between to chars and check if the two word are in the dict and return the new word with space.
    LinkedList* head = NULL , *list = head;
    char* temp = NULL, *pch;
    int counter = 0;
    for (int i = 0; word[i] != '\0'; i++) {
        temp = createSpace(word, i, i+1);
        pch = strtok(temp, " ");
        while(pch !=NULL){
            if(search(dictionaryTable, pch))
                counter++;
            pch = strtok(NULL, " ");
        }
        if(counter == TWO){
            if(head == NULL){
                head = BuildNode(createSpace(word, i, i+1));
                list = head;
            }else{
                list->next = BuildNode(createSpace(word, i, i+1));
                list = list->next;
            }
        }
        free(temp);
        temp = NULL;
        counter = 0;
    }
    return head;
}

LinkedList* replaceCharacterCheck(HashTable* dictionaryTable, char* word){
    //the function changes each character in the string to all the alphabet options and returns a word that exists in the dict
    LinkedList* head = NULL , *list = head;
    char* temp;
    char alphabet[ALPHA] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
    for(int i = 0; word[i] != '\0'; i++){
        for (int j = 0; alphabet[j] != '\0' ; j++) {
            temp = newWord(word, alphabet[j], i);
            if(isWordInDictionary(dictionaryTable, temp)){
                if(head == NULL){
                    head = BuildNode(newWord(word, alphabet[j], i));
                    list = head;
                }else{
                    list->next = BuildNode(newWord(word, alphabet[j], i));
                    list = list->next;
                }
            }
            free(temp);
            temp = NULL;
        }
    }
    return head;
}


LinkedList* deleteCharacterCheck(HashTable* dictionaryTable, char* word){
    //the function deletes every other character in the string for all alphabetical possibilities and returns a word that exists in the dict
    LinkedList* head = NULL , *list = head;
    char* temp;
    for(int i = 0; word[i] != '\0'; i++){
        temp = deleteChar(word, i);
        if(search(dictionaryTable, temp)){
            if(head == NULL){
                head = BuildNode(temp);
                list = head;
            }else{
                list->next = BuildNode(temp);
                list = list->next;
            }
        }else{
            free(temp);
            temp = NULL;
        }
    }
    return head;
}



LinkedList* addCharacterCheck(HashTable* dictionaryTable, char* word){
    //the function adds a character between two characters in a word and creates a new word and checks if it is in the dict.
    LinkedList* head = NULL , *list = head;
    char alphabet[ALPHA] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
    char* temp;
    for(int i = 0; word[i] != '\0' ; i++){
        for (int j = 0; alphabet[j]; j++) {
            temp = addChar(word, alphabet[j], i);
            if(isWordInDictionary(dictionaryTable, temp)){
                if(head == NULL){
                    head = BuildNode(temp);
                    list = head;
                }else{
                    list->next = BuildNode(temp);
                    list = list->next;
                }
            }else{
                free(temp);
                temp = NULL;
            }
            if(word[i+1] == '\0' && search(dictionaryTable, addChar(word, alphabet[j], i+1))){
                if(head == NULL){
                    head = BuildNode(addChar(word, alphabet[j], i+1));
                    list = head;
                }else{
                    list->next = BuildNode(addChar(word, alphabet[j], i+1));
                    list = list->next;
                }
            }
        }
    }
    return head;
}


LinkedList* switchAdjacentCharacterCheck(HashTable* dictionaryTable, char* word){
    //Replaces two adjacent characters in a word and creates a new word and checks if it is in the dict
    LinkedList* head = NULL , *list = head;
    char* temp = NULL;
    for (int i = 0; word[i] != '\0' ; i++) {
        temp = swapChars(word, i);
        if(isWordInDictionary(dictionaryTable, temp)){
            if(head == NULL){
                head = BuildNode(temp);
                list = head;
            }else{
                list->next = BuildNode(temp);
                list = list->next;
            }
        }else{
            free(temp);
            temp = NULL;
        }
    }
    return head;
}

LinkedList* getWordSuggestions(HashTable* dictionaryTable, char* word){
    //the function gets a word and returns to us the list of suggestions made up of words according to each of the five functions described above.
    LinkedList* head = NULL , *list = head;
    for (int i = 0; i < CHECKS; i++) {
        if(head == NULL){
            head = ChecksAllFunctions(i+1, dictionaryTable, word);
            list = head;
        }else{
            for (; list->next != NULL; list = list->next);
            list->next = ChecksAllFunctions(i+1, dictionaryTable, word);
        }
    }
    return head;
}

LinkedList* ChecksAllFunctions(int index, HashTable* dictionaryTable, char* word){
    switch (index) {
        case ONE:
            return deleteCharacterCheck(dictionaryTable, word);
            break;
        case TWO:
            return replaceCharacterCheck(dictionaryTable, word);
            break;
        case THREE:
            return addSpaceCheck(dictionaryTable,word);
            break;
        case FOUR:
            return addCharacterCheck(dictionaryTable,word);
            break;
        case FIFVE:
            return switchAdjacentCharacterCheck(dictionaryTable,word);
            break;
        default:
            printf("NO FIND THE FUNCTION\n");
            return NULL;
            break;
    }
}


char* newWord(char* word, char ch, int index){
    //Constructs a new word with the character sent to it.
    char* temp = (char*)malloc((strlen(word)+1)*sizeof(char));
    for (int i = 0; i < strlen(word) + 1 && temp != NULL ; i++) {
        if(index == i){
            temp[i] = ch;
            continue;
        }
        temp[i] = word[i];
        if(i+1 == strlen(word)+1)
            temp[i+1] ='\0';
    }
    if(strcmp(temp, word) == 0)
        return NULL;
    return temp;
}

char* deleteChar(char* word, int index){
    //deletes a character from the word
    char* temp = (char*)malloc(strlen(word)*sizeof(char));
    for (int i = 0 ,j = 0; word[i] != '\0' && temp != NULL ; i++) {
        if(i == index)
            continue;
        temp[j++] = word[i];
        if(word[i+1] == '\0')
            temp[j+1] = '\0';
    }
    return temp;
}

char* createSpace(char* word, int indexOne, int indexTwo){
    //creates a space between two characters
    char* temp = (char*)malloc((strlen(word)+1)*sizeof(char));
    for (int i = 0, j = 0; word[i] != '\0' && temp != NULL ; i++) {
        if(i == indexTwo){
            temp[j++] = SPACE;
            temp[j++] = word[i];
            continue;
        }
        temp[j++] = word[i];
    }
    return temp;
}


char* addChar(char* word, char ch, int index){
    //adds a character to the word
    char* newWord = (char*)malloc((strlen(word) + TWO)*sizeof(char));
    if(index != strlen(word)){
        for (int i = 0, j = 0 ; word[i] != '\0' && newWord != NULL  ; i++) {
            if(i == index){
                newWord[j++] = ch;
                newWord[j++] = word[i];
                continue;
            }
            newWord[j++] = word[i];
            if(word[i+1] == '\0')
                newWord[++j] = '\0';
        }
    }else{
        for (int i = 0; word[i] != '\0' && newWord != NULL ; i++)
            newWord[i] = word[i];
        newWord[index++] = ch;
        newWord[index] = '\0';
    }
    return newWord;
}

char* swapChars(char* word, int index){
    //swaps two adjacent characters
    char* temp = (char*)malloc((strlen(word)+1)*sizeof(char));
    for (int i = 0; word[i] != '\0' && temp != NULL; i++) {
        if(i == index){
            temp[i] = word[i+1];
            temp[i+1] = word[i];
            i++;
            continue;
        }
        temp[i] = word[i];
        if(word[i+1] == '\0')
            temp[i+1] = '\0';
    }
    return temp;
}
