//  main.cpp
//  Template & Excption
//
//  Created by Roni Jack Vituli on 16/06/2020.
//  Copyright © 2020 Roni Jack Vituli. All rights reserved.

#include "Employee.h"
#include "Set.h"

int main() {
    string Fname,Lname,ID;
    double Salary = 0;
    int Hours = 0;
    Set<double> D1 ,D2 ;
    int size1 , size2;
    double d1 , d2;
    cout << "###################### " << type(D1) << " ######################" << endl << endl;
    cout << "Please Enter the number of elements you want in the first set" << endl;
    cin >> size1;
    cout << "Please enter " << size1 << " elements" << endl;
    for (int i = 0; i < size1; i++) {
        cin >> d1;
        D1 += d1;
    }
    cout << "Please Enter the number of elements you want in the second set" << endl;
    cin >> size2;
    cout << "Please enter " << size2 << " elements" << endl;
    for (int i = 0; i < size2; i++) {
        cin >> d2;
        D2 += d2;
    }
    Set<Employee> Em1 ,Em2;
    int sizeEm1, sizeEm2;
     cout << "########################## " << type(Em1) << " ##########################" << endl << endl;
    cout << "Please Enter the number of elements you want in the first set" << endl;
    cin >> sizeEm1;
    cout << "Please enter " << sizeEm1 << " elements" << endl;
    for (int i = 0; i < sizeEm1; i++) {
        cout << endl << "Enter FULL NAME and ID" << endl;
        cin >> Fname >> Lname >> ID;
        cout << "How many housrs you have and what is your salary?" << endl;
        cin >> Hours >> Salary;
        try{
            Employee em1(ID,Fname,Lname,Salary,Hours);
            Em1 += em1;
        }catch(const char* msg){
            cout <<"ERROR"<< endl << msg << endl;
            return 0;
        }catch(const double num){
            cout << "ERROR" << endl << "You cant put negative num " << num <<endl;
            return 0;
        }catch(const int num){
            cout << "ERROR" << endl << "You cant put negative num " << num <<endl;
            return 0;
        }
    }
    cout << "Please Enter the number of elements you want in the first set" << endl;
    cin >> sizeEm2;
    cout << "Please enter " << sizeEm2 << " elements" << endl;
    for (int i = 0; i < sizeEm2; i++) {
         cout << endl << "Enter FULL NAME and ID" << endl;
         cin >> Fname >> Lname >> ID;
         cout << "How many housrs you have and what is your salary?" << endl;
         cin >> Hours >> Salary;
         try{
             Employee em2(ID,Fname,Lname,Salary,Hours);
             Em2 += em2;
         }catch(const char* msg){
             cout <<"ERROR"<< endl << msg << endl;
         }catch(const double num){
             cout << "ERROR" << endl << "You cant put negative num " << num <<endl;
         }catch(const int num){
             cout << "ERROR" << endl << "You cant put negative num " << num <<endl;
         }
     }
    cout << endl << "########################## " << type(D1) <<" ##########################" << endl << endl;
    cout << "Enter element" << endl;
    cin >> d1;
    D1 += d1;
    cout << "Set1(D1) after adding an element: " << endl << D1 << endl;
    cout <<"The result of the union of Set1(D1) and Set2(D2) is: " << endl << D1 + D2 << endl;
    cout <<"The result of the intersection of Set1(D1) and Set2(D2) is: " << endl << D1 - D2 << endl;
    cout << endl << "########################## END " << type(D1) <<" ##########################" << endl << endl;
    cout << "########################## " << type(Em1) <<" ##########################" << endl << endl;
    cout << "Enter FULL NAME and ID" << endl;
    cin >> Fname >> Lname >> ID;
    cout << "How many housrs you have and what is your salary?" << endl;
    cin >> Hours >> Salary;
    try{
        Employee em1(ID,Fname,Lname,Salary,Hours);
        Em1 += em1;
        cout << endl << "Set1(Em1) after adding an element: " << endl << Em1 << endl;
        cout <<"The result of the union of Set1(Em1) and Set2(Em2) is: " << endl << Em1+Em2 << endl;
        cout <<"The result of the intersection of Set1(Em1) and Set2(Em2) is: " << endl << Em1 - Em2 << endl;
    }catch(const char* msg){
        cout <<"ERROR"<< endl << msg << endl;
        return 0;
    }catch(const double num){
        cout << "ERROR" << endl << "You cant put negative num " << num <<endl;
        return 0;
    }catch(const int num){
        cout << "ERROR" << endl << "You cant put negative num " << num <<endl;
        return 0;
    }
    cout << endl << "########################## END " << type(Em1) <<" ##########################" << endl << endl;

    return 0;

    
}
