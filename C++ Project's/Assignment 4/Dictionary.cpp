//
//  Dictionary.cpp
//  Dictionary
//
//  Created by Roni Jack Vituli on 15/05/2020.
//  Copyright © 2020 Roni Jack Vituli. All rights reserved.
//

#include "Dictionary.h"

Dictionary::Dictionary():num_of_Definition(0),book_of_def(NULL){} // defualt ctor


Dictionary::Dictionary(int num){ // ctor
    if(num < 0){
        cout << "Dictionary -> ERROR NUMBER" <<endl;
        exit(1);
    }
    this->num_of_Definition = num;
    this->book_of_def = new Definition*[num_of_Definition];
    for (int i = 0; i < num_of_Definition; i++){
        this->book_of_def[i] = new Definition();
        cin >> *(book_of_def)[i];
    }
    this->alphaBetDef();
}

Dictionary& Dictionary::operator=(const Dictionary& dic){ // c'tor
    this->num_of_Definition = dic.num_of_Definition;
    this->book_of_def = new Definition*[this->num_of_Definition];
    for (int i = 0; i < this->num_of_Definition; i++) {
        this->book_of_def[i] = new Definition();
    }
    for (int i = 0 ; i <this->num_of_Definition; i++) {
        *(this->book_of_def[i]) = *(dic.book_of_def[i]);
    }
    return *this;
    
}


bool Dictionary::operator==(const Dictionary& dic)const{ // check two dictionary if they equal.
    if(this == &dic)
        return true;
    else if(this->num_of_Definition == dic.num_of_Definition){
        for (int i = 0; i < this->num_of_Definition; i++) {
            if(!(*(this->book_of_def[i]) == *(dic.book_of_def[i])))
                return false;
        }
        return true;
    }
    return false;
}


ostream& operator << (ostream& output , const Dictionary& dic){ // print the dictionary(output)
    output <<endl<< "\t----------Dictionary----------"<< endl << endl;
    for (int i = 0; i < dic.num_of_Definition; i++) {
        output << *(dic.book_of_def[i]) << endl;
    }
    return output;
}

istream& operator >> (istream& input, Dictionary& dic){ //create dictionary (input)
    cout << "How many definition do have?" << endl;
    input >> dic.num_of_Definition;
    if(dic.num_of_Definition > 0){
        getchar();
        dic.book_of_def = new Definition*[dic.num_of_Definition];
        for (int i = 0; i<dic.num_of_Definition; i++){
          dic.book_of_def[i] = new Definition();
            input >> *(dic.book_of_def)[i];
        }
        dic.alphaBetDef();
    }else{
        cout << "Dictionary -> ERROR NUMBER" <<endl;
    }
    return input;
}

void Dictionary::operator-=(int num){ // delete one of the definition from dictionary/
    Definition* temp = NULL;
    if(this->num_of_Definition > num && num > 0){
        temp = this->book_of_def[num-1];
        this->book_of_def[num-1] = this->book_of_def[num_of_Definition-1];
        this->book_of_def[num_of_Definition-1] = temp;
        delete temp;
    }
    this->num_of_Definition--;
}

void Dictionary::operator +=(const Definition& def){ // add new definition to dictionary
    int flag = false;
    for (int i = 0; i < num_of_Definition && !flag; i++) {
        if(*book_of_def[i] == def)
            flag = true;
    }
    if(!flag){
        Definition** temp = new Definition*[num_of_Definition+1];
        for (int i = 0; i < num_of_Definition+1; i++)
            temp[i] = new Definition();
        for (int i = 0 ; i<num_of_Definition; i++) {
            *temp[i] = *(this->book_of_def[i]);
        }
        for(int i = 0 ; i <num_of_Definition ; i++)
            delete this->book_of_def[i];
        delete [] this->book_of_def;
        *temp[num_of_Definition] = def;
        this->num_of_Definition++;
        this->book_of_def = temp;
    }
    this->alphaBetDef();
    
}


int Dictionary::get_num_of_Definiton(){
    return this->num_of_Definition;
}

Definition** Dictionary::get_book_of_def(){
    return book_of_def;
}

const Definition& Dictionary::operator [](int index) const{
    if(index < 0 && index >= this->num_of_Definition){
        cout << "\n Error index " << index << "out of range" << endl;
        exit(1);
    }
    return *(book_of_def)[index];
}

Definition& Dictionary::operator[](int index){
    if(index < 0 && index >= this->num_of_Definition){
        cout << "\n Error index " << index << "out of range" << endl;
        exit(1);
    }
    return *(book_of_def)[index];
}

void Dictionary::alphaBetDef(){ //Arrangement the dictionary by alphabet
    Definition* D1;
    for (int i = 0 ; i < num_of_Definition; i++) {
        for (int j = i + 1; j < num_of_Definition; j++) {
            if (book_of_def[i]->get_Def_Word().strcmp2(book_of_def[j]->get_Def_Word()) > 0) {
                D1 = book_of_def[i];
                book_of_def[i] = book_of_def[j];
                book_of_def[j] = D1;
            }
        }
    }
}

void Dictionary::checkExplanation(){ // Checks common explanation in various definition.
    if(num_of_Definition > 1){
        int count = 0;
        String S1;
        Definition temp;
        temp = *get_book_of_def()[0];
        for (int i = 1 ; i < num_of_Definition ; i++){
            for (int j = 0; j < book_of_def[i]->get_num_of_explanation(); j++) {
                S1 = *book_of_def[i]->get_explanation()[j];
                temp += S1;
            }
        }
        for (int g = 0; g < temp.get_num_of_explanation(); g++) {
            count = 0;
            for (int i = 0 ; i < num_of_Definition ; i++){
                for (int j = 0; j < book_of_def[i]->get_num_of_explanation(); j++) {
                    if (*temp.get_explanation()[g] == *book_of_def[i]->get_explanation()[j])
                        count++;
                }
            }
            if(count > 1){
                cout << "Common Explanation: " << "'" << *temp.get_explanation()[g] << "'" << endl;
                for (int i = 0 , h = 0; i < num_of_Definition; i++) {
                    for (int j = 0 ; j < book_of_def[i]->get_num_of_explanation(); j++) {
                        if (*temp.get_explanation()[g] == *book_of_def[i]->get_explanation()[j]){
                            cout << "("<<h+1<<") "<< book_of_def[i]->get_Def_Word() << endl;
                            h++;
                        }
                    }
                }
            }
        }
    }else{
        cout << "***** you have only one definition *****" << endl;
    }
}

Dictionary::~Dictionary(){
    for (int i = 0; i<num_of_Definition; i++) {
        delete book_of_def[i];
    }
    delete [] book_of_def;
}

