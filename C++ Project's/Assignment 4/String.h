//
//  String.hpp
//  Dictionary
//
//  Created by Roni Jack Vituli on 13/05/2020.
//  Copyright © 2020 Roni Jack Vituli. All rights reserved.
//

#ifndef String_h
#define String_h

#define NO_ERROR 0
#define WORD 80
#define SENTENCE 200
#include <iostream>
using namespace::std;


class String{
    
private:
    
    int size;
    char* string;
    
public:
    String(); // dctor
    String(int); // ctor
    ~String(); // dtor
    String(const String&); //cctor
    
    bool strcmp(const String&)const;
    int strcmp2(const String& sec)const;
    int strlen(const char*);
    void strcopy(const char* str);
    void FixSpace();
    void dynamicMemory();
    void changeCharSmallToBig();
    char nextChar(char*,int);
    
    void setSize(int);
    void setString(char*);
    int getSize();
    char* getString();
    
    //all operators
    const char& operator [](int index)const; //right value
    char& operator [] (int index); // left value
    String& operator =(const String& );
    bool operator ==(const String& )const;
    friend ostream& operator << (ostream&, const String&);
    friend istream& operator >> (istream&, String&);
    void operator +=(char);
    void operator -=(char);
    
    
};

#endif /* String_h */
