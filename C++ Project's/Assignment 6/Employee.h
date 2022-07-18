//
//  Employee.h
//  Template & Excption
//
//  Created by Roni Jack Vituli on 16/06/2020.
//  Copyright © 2020 Roni Jack Vituli. All rights reserved.
//

#ifndef Employee_h
#define Employee_h
#include <iostream>
#include <string>
using namespace::std;
#pragma warning( disable : 4290 )

class Employee{
    string ID;
    string First_name;
    string Last_name;
    double Salary;
    int All_Hours;
public:
    Employee():ID("000000000"),First_name("UnKnow"),Last_name("UnKnow"),Salary(0),All_Hours(0){}
    Employee(string,string,string,double,int);
    
    bool CheckID();
    void PrintEmployee()const;
    
    bool operator > (const Employee&) const;
    friend ostream& operator << (ostream&,const Employee&);
    bool operator ==(const Employee&) const;
    
};


#endif /* Employee_h */
