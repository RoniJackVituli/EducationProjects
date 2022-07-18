//
//  Employee.cpp
//  Template & Excption
//
//  Created by Roni Jack Vituli on 16/06/2020.
//  Copyright © 2020 Roni Jack Vituli. All rights reserved.
//
#include "Employee.h"


Employee::Employee(string id , string Fname, string Lname,double salary, int hours):ID(id),First_name(Fname),Last_name(Lname),Salary(salary),All_Hours(hours){
    if(!CheckID())
        throw "you put worng ID";
    if(this->Salary < 0)
        throw this->Salary;
    if(this->All_Hours < 0)
        throw this->All_Hours;
}

bool Employee::CheckID(){
     if(ID.length() != 9)
          return false;
      for (int i = 0; ID[i] != '\0'; i++) {
          if(ID[i] < '0' || ID[i] > '9')
              return false;
      }
      return true;
}
bool Employee::operator >(const Employee& other) const{
    if(this->Salary > other.Salary)
        return true;
    return false;
}

void Employee::PrintEmployee() const{
    cout << endl << "My Name: " << this->First_name << " " << this->Last_name << endl;
    cout << "My ID: " << this->ID << endl;
    cout << "My Salary is: " << this->Salary << endl;
    cout << "All my hours: " << this->All_Hours << endl << endl;
    
}

ostream& operator <<(ostream& input ,const Employee& obj) {
    obj.PrintEmployee();
    return input;
}

bool Employee::operator==(const Employee& obj) const{
    if(this->ID.compare(obj.ID) == 0)
        return true;
    return false;
}
    

