#include "HashTable.h"

typedef struct SpellingSuggestion SpellingSuggestion;

struct SpellingSuggestion {
	char* originalWord;
	LinkedList* suggestions;
	SpellingSuggestion* next;
};

int wordSpellingChecker(HashTable* dictionaryTable);
int isWordInDictionary(HashTable* dictionaryTable, char* word);

LinkedList* addSpaceCheck(HashTable* dictionaryTable, char* word);
LinkedList* replaceCharacterCheck(HashTable* dictionaryTable, char* word);
LinkedList* deleteCharacterCheck(HashTable* dictionaryTable, char* word);
LinkedList* addCharacterCheck(HashTable* dictionaryTable, char* word);
LinkedList* switchAdjacentCharacterCheck(HashTable* dictionaryTable, char* word);
LinkedList* getWordSuggestions(HashTable* dictionaryTable, char* word);
LinkedList* ChecksAllFunctions(int check, HashTable* dictionaryTable, char* word);


char* newWord(char* word, char ch, int index);
char* deleteChar(char* word, int index);
char* createSpace(char* word, int i, int j);
char* WordOne(char* originalWord);
char* WordTwo(char* originalWord);
char* addChar(char* word, char ch, int index);
char* swapChars(char* ,int );





