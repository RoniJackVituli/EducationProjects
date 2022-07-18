//
//  Corona Department.h
//  Hospital
//
//  Created by Roni Jack Vituli on 05/06/2020.
//  Copyright © 2020 Roni Jack Vituli. All rights reserved.
//

#ifndef Corona_Department_h
#define Corona_Department_h

#include <typeinfo>

#include "Doctor.h"
#include "Nurse.h"
#include "Patient.h"


class Corona_Department{ // מחלקת קורונה
    
    string Hospital_Name;
    Doctor** D;
    int Dsize;
    Patient** P;
    int Psize;
    Nurse** N;
    int Nsize;
    
public:
    Corona_Department();
    Corona_Department(string);
    ~Corona_Department();
    
    void ADD_Doctor(Doctor&,string);
    void ADD_Nurse(Nurse&,string);
    void ADD_Patient(Patient&,string);
    
    
    
// ---------------------- my functions--------------
    bool checkHospital();
    void FixSpace();
    void changeCharSmallToBig();
    void Print_The_Department()const;
    bool checkID(Person*);
    
    friend ostream& operator <<(ostream&,Corona_Department&);
    friend class Corona_Management;
    
};

#endif /* Corona_Department_h */
