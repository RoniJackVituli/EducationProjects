//
//  String.cpp
//  Dictionary
//
//  Created by Roni Jack Vituli on 13/05/2020.
//  Copyright © 2020 Roni Jack Vituli. All rights reserved.
//

#include "String.h"


String::String():size(0),string(NULL){} // defualt ctor

String::String(int SIZE){ // ctor
    size = SIZE;
    string = new char[SIZE];
}

String::String(const String& other){ //c'tor
    this->size = other.size;
    this->string = new char[other.size];
    strcopy(other.string);
}

String::~String(){ //dtor
    delete [] string;
}
bool String::strcmp(const String& sec)const{ // check if two string are eqaul str1==str2
    for (int i = 0; this->string[i] != '\0'; i++) {
        if (this->string[i] != sec.string[i])
            return false;
    }
    return true;
}
int String::strcmp2(const String& sec)const{ // check about the charters if they small or big lettr
    int i = 0;
    while ( string[i] != '\0' ){
        if( sec.string[i] == '\0' )
            return 1;
        else if( string[i] < sec.string[i])
            return -1;
    
        else if( string[i] > sec.string[i])
            return 1;
        i++;
    }
    return 0;
}


int String::strlen(const char* str){ // bring the size of the string
    int count = 0 , i = 0;
    if(str != NULL){
        while (str[i] != '\0') {
            count++;
            i++;
        }
        return count;
    }
    return 0;
}

void String::setSize(int size){ // function set
    this->size = size;
}

void String::setString(char* buffer){ // set
    this->string = buffer;
//    FixSpace();
}


int String::getSize(){
    return this->size;
}

char* String::getString(){
    return this->string;
}

void String::strcopy(const char* str){ // copy string to another string.
    if (this->string == str)
        exit(0);
    int i = 0;
    while (str[i] != '\0') {
        this->string[i] = str[i];
        i++;
        if (str[i+1] == '\0')
            this->string[i+1] = str[i+1];
    }
}

ostream& operator << (ostream& output, const String& str){ // print string.
    int i = 0;
    while (str.string[i] != '\0') {
        output << str.string[i] ;
        i++;
    }
    return output;
}

istream& operator >> (istream& input, String& str){ //get string.
    char* temp = new char[SENTENCE];
    cin.getline(temp,SENTENCE);
    str.size = SENTENCE;
    str.string = temp;
    str.FixSpace();
    return input;
}
bool String::operator==(const String& str)const{ // operator == check between to obj if they equal.
    int flag = true;
    if (this == &str) 
        return true;
    if(this->size == str.size){
        for (int i = 0; this->string[i] != '\0' && flag == true; i++) {
            if (this->string[i] == str.string[i])
                i++;
            else
                flag = false;
        }
        if (flag)
            return true;
    }
    return false;
}
String& String:: operator =(const String& str){ //
    if (this == &str) {
        exit(0);
    }
    this->size = str.size;
    this->string =new char[this->size+1];
    for (int i = 0; str.string[i] != '\0'; i++) {
        this->string[i] = str.string[i];
        if(str.string[i+1] == '\0')
            this->string[i+1] = str.string[i+1];
    }
    this->FixSpace();
    return *this;
}

void String::operator-=(char ch){ // delete char from the string exp: "hello" ch = 'e' , "hllo"
    int count = 0;
    for (int i = 0; string[i] != '\0'; i++) {
        if(string[i] != ch)
            count++;
    }
    char* temp = new char[count+1];
    for (int i = 0, j = 0; string[i] != '\0'; i++) {
        if(string[i] != ch){
            temp[j] = string[i];
            j++;
        }
    }
    this->size = count+1;
    delete [] string;
    string = temp;
    
}

void String::operator+=(char ch){ // and char to the end of the string.
    int newSize = strlen(string);
    char* temp = new char[newSize];
    for (int i = 0; string[i] != '\0'; i++) {
        temp[i] = string[i];
    }
    temp[newSize] = ch;
    delete [] string;
    string = temp;
}

const char& String::operator [](int index) const{ // bring the char in place on index.
    if(index < 0 || index >= size){
        cout << "\n Error index " << index << "out of range" << endl;
        exit(1);
    }
    
    return string[index];
}

char& String::operator[](int index){
    if(index < 0 || index >= size){
        cout << "\n Error index " << index << "out of range" << endl;
        exit(1);
    }
    else
        return string[index];
}

void String::FixSpace(){ // fix the string make one space between two words.
    char* buffer = new char[strlen(string)+1];
    char ch;
    int count = 0 , index = 0;
       for (int i = 0 , j = 0; string[i] != '\0';) {
           while(string[i] != ' ' && string[i] != ',' && string[i] != ':' && string[i] != '.' && string[i] != '\0'){
                buffer[j] = string[i];
                j++;
                i++;
            }
            ch = nextChar(string, i);
            while(string[i] == ' '){
                if(ch == ',' || ch == ':' || ch == '.'){
                    i++;
                }else{
                    count++;
                    i++;
                }
            }
            index = i - count;
            if(buffer[j] != ' ' && buffer[j-1] != ' ' && buffer[0] != '\0'){
                buffer[j] = string[index];
                if(buffer[j] == ' ')
                    j++;
            }
            if(string[i] == ',' || string[i] == ':' || string[i] == '.'){
                buffer[j+1] = ' ';
                j=j+2;
                i++;
            }
            count = 0;
        }
    if(string != NULL)
        delete [] string;                 
    string = buffer;
    this->size = strlen(buffer);
    changeCharSmallToBig();
    dynamicMemory();
}

void String::dynamicMemory(){ // create dynamic memory on size of the string.
    int count = 0;
    for (int i=0; string[i] != '\0'; i++)
        count++;
    if (count != size) {
        this->size = count;
        char* buffer = new char[count+1];
        for (int i=0; string[i] !='\0'; i++){
            buffer[i] = string[i];
            if(string[i+1] == '\0')
                buffer[i+1] = string[i+1];
        }
        delete [] string;
        string = buffer;
    }
}

void String::changeCharSmallToBig(){ // change the char from small to big and oppsite
    if(string[0] >= 'a' && string[0] <= 'z')
        string[0] = string[0] - 32;
    for (int i = 1; string[i] != '\0'; i++) {
        if(string[i] == '.' && (string[i+2] >= 'a' && string[i+2] <= 'z')){
            string[i+2] -= 32;
            i += 2;
        }
        else if(string[i] >= 'A' && string[i] <= 'Z')
            string[i] += 32;
    }
    
}

char String::nextChar(char* str,int i){ // bring me the next char. (help me from fixspace).
    while(str[i] == ' '){
        if (str[i+1] == ',' || str[i+1] == ':' || str[i+1] == '.')
            return str[i+1];
        else if((str[i+1] >= 'a' && str[i+1] <= 'z') || (str[i+1] >= 'A' && str[i+1] <= 'Z'))
            return str[i+1];
        i++;
    }
    return str[i];
}
