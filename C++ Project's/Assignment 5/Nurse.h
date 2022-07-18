//
//  Nurse.h
//  Hospital
//
//  Created by Roni Jack Vituli on 12/06/2020.
//  Copyright © 2020 Roni Jack Vituli. All rights reserved.
//

#ifndef Nurse_h
#define Nurse_h

#include "Worker.h"

class Nurse: public Worker{
    
private:
    
    string Hospital_Name;
    int amout_Courses;
    
public:
    Nurse(string);
    Nurse(string,string,string,int,string,int);
    ~Nurse(){}; //virtual dtor
    
    void whoIam() const; // pure virtual
    bool Excllent();
    void Print() const;
    double Salery() const;
    void InPut();
    
    friend ostream& operator <<(ostream&,const Nurse&);
    friend istream& operator >>(istream&,Nurse&);
    bool operator==(const Nurse&)const;
};

#endif /* Nurse_h */

