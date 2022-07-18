//
//  Definition.cpp
//  Dictionary
//
//  Created by Roni Jack Vituli on 14/05/2020.
//  Copyright © 2020 Roni Jack Vituli. All rights reserved.
//
#define WORD 80
#define CHARTERS 200

#include "Definition.h"


Definition::Definition(): Def_Word(),num_of_explanation(0),explanation(NULL){} //defualt ctor

Definition::Definition(int amout_exp):num_of_explanation(amout_exp),Def_Word(),explanation(NULL){ //ctor
    char* temp = new char[WORD];
    char* tempEx = new char[CHARTERS];
    cout << "Enter the name of definition"<<endl;
    cin.getline(temp,WORD);
    Def_Word.setString(temp);
    Def_Word.setSize(WORD);
    explanation = new String*[num_of_explanation];
    cout << "Enter the explanation" << endl;
    for (int i = 0 ; i  < num_of_explanation; i++){
        explanation[i] = new String();
        cout << "EXP " << i+1 <<"- " ;
        cin.getline(tempEx,CHARTERS);
        explanation[i]->setString(tempEx);
        explanation[i]->setSize(CHARTERS);
        if(i+1 < num_of_explanation)
            tempEx = new char[CHARTERS];
    }
    this->alphaBetExp();
}

// functions set & get.

void Definition::set_Def_Word(String str){
    Def_Word = str;
}

void Definition::set_num_of_explanation(int num){
    this->num_of_explanation = num;
}

String Definition::get_Def_Word(){
    return Def_Word;
}
String** Definition::get_explanation(){
    return explanation;
}
int Definition::get_num_of_explanation(){
    return num_of_explanation;
}



istream& operator >> (istream& input, Definition& def){ // get new definition. (input)
    char* temp = new char[WORD];
    char* tempEx = new char[CHARTERS];
    cout << "Enter the name of definition"<<endl;
    cin.getline(temp,WORD);
    def.Def_Word.setString(temp);
    def.Def_Word.FixSpace();
    cout << "How many explanation the word have?" << endl;
    cin >> def.num_of_explanation;
    getchar();
    def.explanation = new String*[def.num_of_explanation];
    cout << "Enter the explanation" << endl;
    for (int i = 0 ; i  < def.num_of_explanation; i++){
        def.explanation[i] = new String();
        cout << "EXP " << i+1 <<"- " ;
        cin.getline(tempEx,CHARTERS);
        def.explanation[i]->setString(tempEx);
        def.explanation[i]->FixSpace();
        if(i+1 < def.num_of_explanation)
            tempEx = new char[CHARTERS];
    }
    def.alphaBetExp();
    return input;
}

ostream& operator << (ostream& output, const Definition& D){ // print the definition. (output)
    cout <<endl<< "---------------" <<D.Def_Word << "---------------"<< endl;
    cout << endl;
    for (int i = 0 ; i< D.num_of_explanation; i++) {
        cout << "Exp "<<i+1<<"- "<<D.explanation[i]->getString() << endl; 
    }
    
    return output;
}


bool Definition::operator==(const  Definition& def)const{ // check only if the name of definition equal.
    if(this == &def)
        return true;
    else if(this->Def_Word == def.Def_Word)
        return true;
    return false;
}

Definition& Definition::operator =(const Definition& def){
    this->Def_Word = def.Def_Word;
    this->num_of_explanation = def.num_of_explanation;
    this->explanation = new String*[this->num_of_explanation];
    for (int i = 0; i < this->num_of_explanation; i++)
        this->explanation[i] = new String(CHARTERS);
    for (int i = 0 ; i < this->num_of_explanation; i++) {
        *(this->explanation[i]) = *(def.explanation[i]);
    }
    return *this;
}

void Definition::operator-=(int num){ // delete one off the explanation
    String* temp = NULL;
    
    if(this->num_of_explanation > num && num > 0){
        temp = this->explanation[num-1];
        this->explanation[num-1] = this->explanation[num_of_explanation-1];
        this->explanation[num_of_explanation-1] = temp;
        delete temp;
    }
    this->num_of_explanation--;
}

void Definition::operator +=(String& str){ // add one more explantion.
    if(!checkExplanation(str)){
        int count = 0;
        for (int i=0 ; i<num_of_explanation; i++)
            if(this->explanation[i]->strcmp(str))
                count++;
        if(count != num_of_explanation){
            num_of_explanation += 1;
            String** temp = new String*[num_of_explanation];
            for (int i = 0 ; i<num_of_explanation; i++)
                temp[i] = new String(CHARTERS);
            for (int i = 0; i < num_of_explanation-1 ; i++) {
                temp[i]->strcopy(explanation[i]->getString());
                temp[i]->setSize(explanation[i]->getSize());
            }
            temp[num_of_explanation-1]->strcopy(str.getString());
            temp[num_of_explanation-1]->setSize(str.getSize());
            for (int i = 0; i< num_of_explanation-1; i++){
                delete this->explanation[i];
         }
            delete [] this->explanation;
            explanation = temp;
            this->alphaBetExp();
        
        }
    }
}

bool Definition::checkExplanation(const String& str)const{ // check if explanation exsits on definition.
    for (int j = 0 ; j < num_of_explanation ; j++) {
        if (str == *explanation[j]) {
            return true;
        }
    }
    return false;
}


void Definition::alphaBetExp(){ //Arrangement the explanation by alphabet
    String* T1;
    for (int i = 0 ; i < num_of_explanation; i++) {
        for (int j = i + 1; j < num_of_explanation; j++) {
            if (explanation[i]->strcmp2(*explanation[j]) > 0) {
                T1 = explanation[i];
                explanation[i] = explanation[j];
                explanation[j] = T1;
            }
        }
    }
}



Definition::~Definition(){ // dtor.
    for (int i = 0; i < num_of_explanation; i++) {
        delete explanation[i];
    }
    delete [] explanation;
    
}
