//
//  Person.h
//  Hospital
//
//  Created by Roni Jack Vituli on 05/06/2020.
//  Copyright © 2020 Roni Jack Vituli. All rights reserved.
//

#ifndef Person_h
#define Person_h

#include <iostream>
#include <typeinfo>
#include <string>

using namespace std;


class Person{
    
private:
    string First_Name;
    string Last_Name;
    string ID;
public:
    Person();
    Person(string Fname, string Lname, string ID):First_Name(Fname), Last_Name(Lname), ID(ID){ cout << "Ctor Person" << endl;}
   
    virtual ~Person(){};
    
    
    string Fix_Space(string);
    string change_Char_Small_To_Big(string);
    virtual void Print() const;
    bool checkID();
    virtual void whoIam() const = 0;
    
    virtual void InPut();
   // virtual void OutPut()const;
    string get_Fname()const;
    string get_Lname()const;
    string get_ID()const;
    
    friend ostream& operator <<(ostream&,const Person&);
    friend istream& operator >>(istream&,Person&);
    //virtual bool operator ==(const Person&)const;
};




#endif /* Person_h */

