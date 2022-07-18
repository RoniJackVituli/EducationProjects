//
//  Corona Department.cpp
//  Hospital
//
//  Created by Roni Jack Vituli on 05/06/2020.
//  Copyright © 2020 Roni Jack Vituli. All rights reserved.
//

#include "Corona Department.h"

Corona_Department::Corona_Department(){
    string HospitalNames[] = { "Sheba", "Wolfson" , "Rambam", "Assaf Harofeh", "Soroka"};
    bool NotExsits = true;
    cout << "Where you want to open the first department?" << endl;
    do{
        cout <<"The list of Hospitals:" << endl;
        for (int i = 0 ; i < sizeof(HospitalNames)/sizeof(HospitalNames[0]) ; i++) {
            cout << i+1 <<") " << HospitalNames[i] << endl;
        }
        cout << "Enter the name: ";
        getline(cin,Hospital_Name);
        FixSpace();
        if(checkHospital())
            NotExsits = false;
        else
            cout << endl << "Sorry but you put worng name of the hospital..." << endl << "please try again" << endl << endl;
    }while(NotExsits);
    this->Dsize = 1;
    D = new Doctor*[Dsize];
    for (int i = 0; i<Dsize; i++) {
        D[i] = new Doctor(Hospital_Name);
        cin >> *D[i];
    }
    NotExsits = true;
    this->Nsize = 2;
    N = new Nurse*[Nsize];
    for (int i = 0 ; i < Nsize; i++){
        N[i] = new Nurse(Hospital_Name);
        do{
            cin >> *N[i];
            if(!checkID(N[i])){
                NotExsits = true;
            }else{
                cout << "******* ERROR *******" << endl << "THE ID EXSITS TRY AGAIN" << endl << "*********************"<< endl;
                i--;
            }
        }while(!NotExsits);
    }
    this->P = NULL;
    this->Psize = 0;
}

Corona_Department::Corona_Department(string Hospital_Name){
    bool NotExsits = false;
    this->Hospital_Name = Hospital_Name;
    this->Dsize = 1;
    D = new Doctor*[Dsize];
    for (int i = 0; i<Dsize; i++) {
        D[i] = new Doctor(Hospital_Name);
        cin >> *D[i];
    }
    NotExsits = false;
    this->Nsize = 2;
    N = new Nurse*[Nsize];
    for (int i = 0 ; i < Nsize; i++){
        N[i] = new Nurse(Hospital_Name);
        do{
            cin >> *N[i];
            if(!checkID(N[i])){
                NotExsits = true;
            }else{
                cout << "******* ERROR *******" << endl << "THE ID EXSITS TRY AGAIN" << endl << "*********************"<< endl;
                i--;
            }
        }while(!NotExsits);
    }
    this->P = NULL;
    this->Psize = 0;
}

bool Corona_Department::checkHospital(){
    string HospitalNames[] = { "Sheba", "Wolfson" , "Rambam", "Assaf Harofeh", "Soroka"};
    for (int i = 0 ; i < sizeof(HospitalNames)/sizeof(HospitalNames[0]); i++) {
        if (Hospital_Name == HospitalNames[i]) 
            return true;
    }
    return false;
}

void Corona_Department::FixSpace(){
    string buffer;
    int counter = 0 , index = 0 ;
    for (int i = 0 ; Hospital_Name[i] != '\0' ;) {
        while(Hospital_Name[i] != ' ' && Hospital_Name[i] != '\0'){
            buffer += Hospital_Name[i];
            i++;
        }
        while(Hospital_Name[i] == ' '){
            counter++;
            i++;
        }
        if(Hospital_Name[i] != '\0'){
            index = i - counter;
            buffer += Hospital_Name[index];
            counter = 0;
        }
    }
    Hospital_Name = buffer;
    changeCharSmallToBig();
}
void Corona_Department::changeCharSmallToBig(){
    if(Hospital_Name[0] >= 'a' && Hospital_Name[0] <= 'z')
        Hospital_Name[0] = Hospital_Name[0] - 32;
    for (int i = 1; Hospital_Name[i] != '\0'; i++) {
        if(Hospital_Name[i] == ' ' && (Hospital_Name[i+1] >= 'a' && Hospital_Name[i+1] <= 'z')){
            Hospital_Name[i+1] -= 32;
            i += 2;
        }
        else if(Hospital_Name[i] >= 'A' && Hospital_Name[i] <= 'Z')
            Hospital_Name[i] += 32;
        }
}


void Corona_Department::ADD_Doctor(Doctor& newDoctor,string nameHos){
    Doctor** temp = new Doctor*[Dsize+1];
    for (int i = 0 ; i < Dsize+1; i++)
        temp[i] = new Doctor(nameHos);
    for (int i = 0 ; i < Dsize; i++)
        *temp[i] = *(this->D[i]);
    for (int i = 0 ; i < Dsize; i++)
        delete this->D[i];
    delete [] this->D;
    *temp[Dsize] = newDoctor;
    this->Dsize++;
    this->D = temp;
}

void Corona_Department::ADD_Patient(Patient& newPatient, string nameHos){
    if(P){
        Patient** temp = new Patient*[Psize+1];
        for (int i = 0 ; i < Psize + 1; i++)
            temp[i] = new Patient(nameHos);
        for (int i = 0 ; i < Psize ; i++)
            *temp[i] = *(this->P[i]);
        for (int i = 0; i < Psize; i++)
            delete this->P[i];
        delete [] this->P;
        *temp[Psize] = newPatient;
        this->Psize++;
        this->P = temp;
    }else{
        this->Psize = 1;
        P = new Patient*[Psize];
        for (int i = 0; i < Psize; i++){
            P[i] = new Patient(nameHos);
            *P[i] = newPatient;
        }
    }
}

void Corona_Department::ADD_Nurse(Nurse& newNurse, string nameHos){
    Nurse** temp = new Nurse*[Nsize+1];
    for (int i = 0; i < Nsize+1; i++)
        temp[i] = new Nurse(nameHos);
    for (int i = 0; i < Nsize; i++)
        *temp[i] = *(this->N[i]);
    for (int i = 0; i < Nsize; i++)
        delete this->N[i];
    delete [] this->N;
    *temp[Nsize] = newNurse;
    this->Nsize++;
    this->N = temp;
}

ostream& operator <<(ostream& output,Corona_Department& dep){
    dep.Print_The_Department();
    return output;
}

void Corona_Department::Print_The_Department()const{
    cout << endl << "-------------"<<Hospital_Name<<"-------------"<< endl << endl;
    if(Dsize > 0){
        cout << "---------ALL DOCTORS-----------" << endl << endl;
        for (int i = 0 ; i < Dsize; i++)
            cout << i+1 << ")" <<*D[i] << endl;
    }
    if(Nsize > 0){
        cout << "---------ALL NURSES-----------" << endl << endl;
            for (int i = 0 ; i < Nsize; i++)
                cout << i+1 << ")" <<*N[i] << endl;
    }
    if(Psize >= 0){
        cout << "---------PATIENT-----------" << endl << endl;
        cout << "We have " << Psize << " Patients" << endl;
    }
}

bool Corona_Department::checkID(Person* person){
    if(D){
        for (int i = 0 ; i < Dsize; i++) {
            if(person != D[i])
                if(person->get_ID() == this->D[i]->get_ID())
                    return true;
        }
    }if(N){
        for (int i = 0; i < Nsize-1 ; i++) {
            if(person != N[i])
                if(person->get_ID() == this->N[i]->get_ID())
                    return true;
        }
        
    }
    return false;
}

Corona_Department::~Corona_Department(){
    for (int i = 0; i < Dsize ; i++)
        delete D[i];
    delete [] D;
    for (int i = 0; i < Nsize; i++)
        delete N[i];
    delete [] N;
    for (int i = 0 ; i < Psize; i++)
        delete P[i];
    delete [] P;
}
    


        
    
