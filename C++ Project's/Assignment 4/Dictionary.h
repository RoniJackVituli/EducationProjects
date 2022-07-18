//
//  Dictionary.hpp
//  Dictionary
//
//  Created by Roni Jack Vituli on 15/05/2020.
//  Copyright © 2020 Roni Jack Vituli. All rights reserved.
//

#ifndef Dictionary_h
#define Dictionary_h
#include "Definition.h"
#include <stdio.h>


class Dictionary{
    
private:
    
    int num_of_Definition;
    Definition** book_of_def;
    
public:
    Dictionary(); //dctor
    Dictionary(int);//ctor
    Dictionary(const Dictionary&);//cctor
    ~Dictionary();//dtor
    
    
    void alphaBetDef();
    Definition** get_book_of_def();
    int get_num_of_Definiton();
    
    void checkExplanation();
    
    
    Dictionary& operator =(const Dictionary&);
    bool operator ==(const Dictionary&)const;
    friend ostream& operator <<(ostream&,const Dictionary&);
    friend istream& operator >>(istream&,Dictionary&);
    void operator -=(int);
    void operator +=(const Definition&);
    const Definition& operator [](int index)const; //right value
    Definition& operator [] (int index); // left value
    
    
};



#endif /* Dictionary_h */
