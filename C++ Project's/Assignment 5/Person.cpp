//
//  Person.cpp
//  Hospital
//
//  Created by Roni Jack Vituli on 05/06/2020.
//  Copyright © 2020 Roni Jack Vituli. All rights reserved.
//

#include "Person.h"


Person::Person():First_Name("UnKnow"),Last_Name("UnKnow"),ID("UnKnow"){}

bool Person::checkID(){
    if(ID.length() != 9)
        return false;
    for (int i = 0; ID[i] != '\0'; i++) {
        if(ID[i] < '0' || ID[i] > '9')
            return false;
    }
    return true;
    
}
void Person::Print()const{
    cout << "First Name: " << First_Name << endl << "Last Name: " << Last_Name << endl << "ID: " << ID << endl;
}

void Person::InPut(){
    bool id_ok = false;
    cout << "Enter your full name" << endl;
    cin >> First_Name >> Last_Name;
    First_Name = Fix_Space(First_Name);
    Last_Name = Fix_Space(Last_Name);
    do{
        cout << "Enter your ID" << endl;
        cin >> ID;
        if (checkID())
            id_ok = true;
        else
            cout << "The ID is incorrect please try again"<< endl;
    }while(!id_ok);
}
string Person::get_Fname() const{
    return First_Name;
}
string Person::get_Lname() const{
    return Last_Name;
}
string Person::get_ID() const{
    return ID;
}


string Person::change_Char_Small_To_Big(string Name){
    if(Name[0] >= 'a' && Name[0] <= 'z')
        Name[0] = Name[0] - 32;
    for (int i = 1; Name[i] != '\0'; i++) {
        if(Name[i] == ' ' && (Name[i+1] >= 'a' && Name[i+1] <= 'z')){
            Name[i+1] -= 32;
            i += 2;
        }
        else if(Name[i] >= 'A' && Name[i] <= 'Z')
            Name[i] += 32;
        }
    return Name;
}

string Person::Fix_Space(string Name){
    string buffer;
    int counter = 0 , index = 0 ;
    for (int i = 0 ; Name[i] != '\0' ;) {
        while(Name[i] != ' ' && Name[i] != '\0'){
            buffer += Name[i];
            i++;
        }
        while(Name[i] == ' '){
            counter++;
            i++;
        }
        if(Name[i] != '\0'){
            index = i - counter;
            buffer += Name[index];
            counter = 0;
        }
    }
    Name = buffer;
    Name = change_Char_Small_To_Big(Name);
    return Name;
}

