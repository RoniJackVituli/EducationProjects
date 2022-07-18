//
//  Worker.hpp
//  Hospital
//
//  Created by Roni Jack Vituli on 10/06/2020.
//  Copyright © 2020 Roni Jack Vituli. All rights reserved.
//

#ifndef Worker_h
#define Worker_h
#include "Person.h"

class Worker : public Person{
    
protected:
    int Years_of_seniority;
    double Basis_Salery = 6500;
public:
    Worker():Years_of_seniority(0){}
    //Worker(string Fname, string Lname,string ID, int years);
  
    ~Worker(){};
    
  
    void Print() const; // virtual from person.
    virtual double Salery() const = 0;
    virtual bool Excllent() = 0;
    int get_Years_of_seniority() const;
    void InPut();
 
    
    
    friend ostream& operator <<(ostream&,const Worker&);
    friend istream& operator >>(istream&,Worker&);
    bool operator==(const Worker&)const;

    
    
};


#endif /* Worker_h */
