//
//  Definition.hpp
//  Dictionary
//
//  Created by Roni Jack Vituli on 14/05/2020.
//  Copyright © 2020 Roni Jack Vituli. All rights reserved.
//

#ifndef Definition_h
#define Definition_h

#include "String.h"
#include <stdio.h>
#include <iostream>



class Definition{
    
private:
    String Def_Word; // name of definition 80 char
    int num_of_explanation; // how many explanation have for definition
    String** explanation; // all the explanation 200 char
    
public:
    
    Definition(); // dctor
    Definition(int); // ctor
    Definition(const Definition&); // cctor
    ~Definition(); //dtor
    
    
    void set_Def_Word(String);
    void set_num_of_explanation(int);
    void set_explanation(String**);
    bool checkExplanation(const String&)const;
  
    String get_Def_Word();
    int get_num_of_explanation();
    String** get_explanation();
    
    void alphaBetExp();
    
    
    Definition& operator =(const Definition&); // operator D1=D2;
    bool operator ==(const Definition&)const; // check objs if they equal.
    void operator -=(int); // take off one of the explanation
    void operator +=(String&); // add explanation to the end of the list.
    friend ostream& operator << (ostream&, const Definition&); // output.
    friend istream& operator >> (istream&, Definition&); // input
    const String& operator [](int index)const; //right value
    String& operator [] (int index); // left value
};





#endif /* Definition_h */
