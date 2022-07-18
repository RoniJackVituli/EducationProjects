//
//  Patient.h
//  Hospital
//
//  Created by Roni Jack Vituli on 05/06/2020.
//  Copyright © 2020 Roni Jack Vituli. All rights reserved.
//

#ifndef Patient_h
#define Patient_h
#include "Person.h"

class Patient: public Person{
    
private:
    string Hospital_Name;
    int NumTestCorona;
    int NegativeTests;
    
public:
    Patient(string hos):Hospital_Name(hos),NumTestCorona(0),NegativeTests(0){}
    Patient(string,string,string,string,int,int);
    ~Patient(){}; //virtual
    
    void Print() const; //virtual
    void whoIam() const; // virtual person
    int get_NegativeTests() const;
    void InPut();
    string get_Hospital_Name(){return this->Hospital_Name;}
    
    void add_NumTestCorona(){this->NumTestCorona++;}
    void add_NegativeTests(){this->NegativeTests++; this->NumTestCorona++;}
    
    bool operator==(const Patient&)const;
    
    friend ostream& operator <<(ostream&,const Patient&);
    friend istream& operator >>(istream&,Patient&);
    
    
    
};

#endif /* Patient_h */
