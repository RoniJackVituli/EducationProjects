//
//  Patient.cpp
//  Hospital
//
//  Created by Roni Jack Vituli on 05/06/2020.
//  Copyright © 2020 Roni Jack Vituli. All rights reserved.
//

#include "Patient.h"


Patient::Patient(string fn,string ln, string Id,string Hos,int Test ,int Ntest):Person(fn, ln, Id),Hospital_Name(Hos),NumTestCorona(Test),NegativeTests(Ntest){ cout << "Ctor Patient" << endl;}

void Patient::whoIam() const{
    cout << "I am Patient" << endl;
}

void Patient::Print()const{
    Person::Print();
    cout << "Negative Tests: " << NegativeTests << endl;
}

int Patient::get_NegativeTests() const{
    return NegativeTests;
}

void Patient::InPut(){
    cout << endl << "-------- Patient ---------" << endl << endl;
    bool flag = false;
    Person::InPut();
    do{
        cout << "How many corona test you did?" << endl;
        cin >> NumTestCorona;
        if(NumTestCorona >= 0)
            flag = true;
        else
            cout << "****** ERROR ******" << endl << "try again!" << endl;
    }while(!flag);
    flag = false;
    do{
        cout << "How many negative?" << endl;
        cin >> NegativeTests;
        if((NumTestCorona >= NegativeTests) && (NegativeTests >= 0))
            flag = true;
        else
            cout << "****** ERROR ******" << endl << "try again!" << endl;
        }while(!flag);
}


ostream& operator <<(ostream& output,const Patient& patient){
    patient.Print();
    return output;
}

istream& operator >>(istream& input,Patient& patient){
    patient.InPut();
    return input;
}


bool Patient::operator==(const Patient& sec)const{
    if(this->Person::get_ID()==sec.Person::get_ID())
        return true;
    return false;
}
