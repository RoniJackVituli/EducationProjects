#define _CRT_SECURE_NO_WARNINGS
#include "WordSpellingChecker.h"
#include "HashTable.h"
#define SIZE 100
#define HASHSIZE 150 // Choice what size you want...
//------Functions----------------
int parseWordsToTable(char* path, HashTable* ht);
char* cleanTheWord(char []);
SpellingSuggestion* spellingCheck(char* text);
SpellingSuggestion* BuildNodeSuggestion(char* ,LinkedList*);
SpellingSuggestion* addToStartSuggestion(LinkedList *, char*);
SpellingSuggestion* FreeListSuggestion(SpellingSuggestion* head);
char* createNewWord(char*,int*);
int isInListSuggestion(SpellingSuggestion* head, char* str);
void printSpellingSuggestions(SpellingSuggestion* spellingSuggestions);




int main()
{
	char* text = "iam afraid youare about to become teh immexdiate pst president of teh eing alive club ha ha glados";
	SpellingSuggestion* spellingSuggestions = spellingCheck(text);
    printSpellingSuggestions(spellingSuggestions);
    FreeListSuggestion(spellingSuggestions);
	return 0;
}

int parseWordsToTable(char* path, HashTable* ht){
    //open the the file of dictionary.txt and put all the word to hashtable.
    FILE* ptr = fopen(path, "r");
    char str[SIZE];
    if(ptr == NULL){
        printf("Error to open file\n");
        return False;
    }
    while (fgets(str, SIZE, ptr) != NULL) {
        if(!insert(ht, cleanTheWord(str)))
            return False;
    }
    fclose(ptr);
    return True;
}

char* cleanTheWord(char word[] ){
    //clean the word and delete the charts '\r' and '\n';
    char* str= (char*)malloc((strlen(word) - 1) * sizeof(char));
    if(str == NULL)
        exit(6);
    for (int i = 0; word[i] != '\r' ; i++){
        str[i] = word[i];
        if(word[i+1] == '\r')
            str[i+1] = '\0';
    }
    return str;
}

SpellingSuggestion* spellingCheck(char* text){
    // builds a list with all the words that have spelling errors
    char* filePath = "/Users/ronijackvituli/Desktop/Assignment/dictionary.txt";
    char* pch;
    HashTable* ht = initTable(HASHSIZE , HASH_FUNCTION);
    SpellingSuggestion* head = NULL , *list = head;
    if(parseWordsToTable(filePath, ht)){
        for(int i = 0; text[i] != '\0'; i++){
            pch = createNewWord(text, &i);
            if(!isWordInDictionary(ht, pch) && !isInListSuggestion(head, pch)){
              if(head == NULL){
                  head = BuildNodeSuggestion(pch, getWordSuggestions(ht,pch));
                  list = head;
              }else{
                   list->next = BuildNodeSuggestion(pch, getWordSuggestions(ht,pch));
                   list = list->next;
              }
            }else{
                free(pch);
                pch = NULL;
            }
        }
    }else{
        printf("THE WORDS NOT INSERT TO HASHTABLE.\n\n");
    }
    FreeHash(ht);
    return head;
}
    
SpellingSuggestion* BuildNodeSuggestion(char* str, LinkedList* suggestions){
    //this function creates a new node
    SpellingSuggestion* node = (SpellingSuggestion*)malloc(sizeof(SpellingSuggestion));
    node->originalWord = str;
    node->suggestions = suggestions;
    node->next = NULL;
    return node;
}


char* createNewWord(char* text,int* index){
    //This function takes one word from the text we received.
    int count = 0;
    if(text[*index] == ' ')
        *index += 1;
    for (int i = *index ; text[i] != ' ' && text[i] != '\0' ; i++) {
        count++;
    }
    char* temp = (char*)malloc((count+1)*sizeof(char));
    for (int i = *index, j = 0 ; temp != NULL && text[i] != ' ' && text[i] != '\0' && j < count ; i++ ,j++) {
        temp[j] = text[i];
        if(text[i+1] == ' ' || text[i+1] == '\0'){
            *index = i;
            temp[j+1] = '\0';
        }
    }
    return temp;
}

int isInListSuggestion(SpellingSuggestion* head, char* str){
    //checks that if a word is found that has already been added to the list
    SpellingSuggestion* temp = head;
    for(; temp != NULL ; temp = temp->next)
        if((temp->originalWord != NULL) && (strcmp(temp->originalWord, str) == 0))
            return True;
    return False;
}

void printSpellingSuggestions(SpellingSuggestion* head){
    //prints the list including the possible correction
    SpellingSuggestion* temp = head;
    if(temp == NULL){
        printf("The list is empty\n");
    }else{
        while (temp != NULL) {
            if(temp->suggestions != NULL){
                printf("The word ""\"%s\" was misspelled. Did you mean:\n",temp->originalWord);
                PrintList(temp->suggestions);
                printf("\n, ");
                temp = temp->next;
            }else{
                printf("The word ""\"%s\" was misspelled. No suggestions found for this word.\n",temp->originalWord);
                temp = temp->next;
            }
            
        }
    }
}

SpellingSuggestion* FreeListSuggestion(SpellingSuggestion* head){
    //Releases all memory!
    SpellingSuggestion* temp;
    while (head != NULL)
    {
        temp = head;
        free(temp->originalWord);
        FreeList(temp->suggestions);
        head = head->next;
        free(temp);
    }
    return NULL;
}
