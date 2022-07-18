//
//  Nurse.cpp
//  Hospital
//
//  Created by Roni Jack Vituli on 12/06/2020.
//  Copyright © 2020 Roni Jack Vituli. All rights reserved.
//

#include "Nurse.h"
Nurse::Nurse(string Hos):Hospital_Name(Hos),amout_Courses(0){}


istream& operator >>(istream& input,Nurse& nurse){
    nurse.InPut();
    return input;
}

ostream& operator <<(ostream& output, const Nurse& nurse){
    nurse.Print();
    return output;
}

void Nurse::InPut(){
    cout << endl << "-------- Nurse ---------" << endl << endl;
    Worker::InPut();
    bool big = false;
    do{
        cout << "How many courses you did?" << endl;
        cin >> amout_Courses;
        if(amout_Courses >= 0)
            big = true;
        else
            cout << "You cannot enter a negative number, Please try again" << endl;
    }while(!big);
}

double Nurse::Salery() const{
    return Basis_Salery+(amout_Courses*50);
}

void Nurse::Print() const{
    Worker::Print();
    cout << "All the courses i did: " << amout_Courses << endl;
}

bool Nurse::Excllent(){
    if(amout_Courses >= get_Years_of_seniority())
        return true;
    return false;
}

void Nurse::whoIam() const{
    cout << "I am a Nurse"<<endl;
}
bool Nurse::operator==(const Nurse& sec)const{
    if(this->Person::get_ID() == sec.Person::get_ID())
        return true;
    return false;
}

