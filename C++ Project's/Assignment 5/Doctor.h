//
//  Doctor.h
//  Hospital
//
//  Created by Roni Jack Vituli on 05/06/2020.
//  Copyright © 2020 Roni Jack Vituli. All rights reserved.
//

#ifndef Doctor_h
#define Doctor_h
#include "Worker.h"

class Doctor: public Worker{
    
    string Hospital_Name;
    bool the_doc_is_Pro;
    int feedback;
    
public:
    Doctor(string);//:Hospital_Name(hos),the_doc_is_Pro(false),feedback(0){}
    Doctor(string,string,string,int,string,bool,int);
    Doctor(const Doctor&);
    ~Doctor(){}; // virtual
    
    
    bool checkChoice(char);
    double Salery() const; 
    bool Excllent(); // check if the doctor are excllent.
    void whoIam() const; //pure virtual
    void Print()const; // virtual from person
    void InPut();
    
    friend ostream& operator <<(ostream&,const Doctor&);
    friend istream& operator >>(istream&, Doctor&);
    bool operator==(const Doctor&)const;
};

#endif /* Doctor_h */

