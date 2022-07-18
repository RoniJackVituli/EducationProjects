//
//  Corona management.cpp
//  Hospital
//
//  Created by Roni Jack Vituli on 11/06/2020.
//  Copyright © 2020 Roni Jack Vituli. All rights reserved.
//

#include "Corona management.h"



Corona_Management::Corona_Management():allTheEmployee(0),AllPsize(0),amout_dep(1),all_Pantient(NULL){
    Corona_Dep = new Corona_Department*[amout_dep];
    for (int i = 0; i < this->amout_dep; i++) {
        Corona_Dep[i] = new Corona_Department();
        allTheEmployee += Corona_Dep[i]->Dsize+Corona_Dep[i]->Nsize+Corona_Dep[i]->Psize;
    }
    Employee = new Worker*[allTheEmployee];
    for (int i = 0 , j = 0; i < amout_dep && j < allTheEmployee ; i++) {
        for (int d = 0 ; d < Corona_Dep[i]->Dsize; d++) {
            Employee[j++] = Corona_Dep[i]->D[d];
        }
        for (int n = 0; n < Corona_Dep[i]->Nsize; n++) {
            Employee[j++] = Corona_Dep[i]->N[n];
        }
    }
}


void Corona_Management::printOptions() const{
    cout << "Menu: " << endl;
    cout << "1. ADD NURSE" << endl;
    cout << "2. ADD DOCTOR" << endl;
    cout << "3. ADD DEPARTMENT" << endl;
    cout << "4. PRINT DEPARTMENT DETAILS" << endl;
    cout << "5. PRINT DOCTORS DETAILS" << endl;
    cout << "6. PRINT SALARY BY ID" << endl;
    cout << "7. ADD PATIENT" << endl;
    cout << "8. ADD CORONA TEST TO PATIENT ID" << endl;
    cout << "9. RELEASING PATIENTS" << endl;
    cout << "10. PRINT EXCELLENCE WORKER" << endl;
    cout << "11. PRINT NURSE DETAILS WITH SMALLEST SALARY" << endl;
    cout << "12. EXIT" << endl;
}

void Corona_Management::Menu(){
    int option;
    bool run = true;
    while (run) {
        printOptions();
        cin >> option;
        switch (option) {
        case ADD_NURSE:
            AddNurse();
            break;
        case ADD_DOCTOR:
            AddDoctor();
            break;
        case ADD_DEPARTMENT:
            AddDepartment();
            break;
        case PRINT_DEPARTMENT_DETAILS:
            PrintDepartmentDetails();
            break;
        case PRINT_DOCTORS_DETAILS:
            PrintDoctorsDetails();
            break;
        case PRINT_SALARY_BY_ID:
            PrintSalary();
            break;
        case ADD_PATIENT:
            AddPatient();
            break;
        case ADD_CORONA_TEST_TO_PATIENT_ID:
            AddCoronaTestToPatientById();
            break;
        case RELEASING_PATIENTS:
            Releasing();
            break;
        case PRINT_EXCELLENCE_WORKER:
            PrintExcellenceWorker();
            break;
            case PRINT_NURSE_DETAILS_WITH_SMALLEST_SALARY:
            PrintNurseWithSmallestSalary();
            break;
        case EXIT:
            run = false;
                cout << endl << "-------GOOD BYE-------" << endl;
            break;
            }
        }
    }

void Corona_Management::AddDoctor(){
    getchar();
    bool Exsits = false;
    string Hos_Name;
    cout << "To which department would you like to add the Doctor?" << endl << endl;
    do{
        printList();
        getline(cin,Hos_Name);
        Hos_Name = FixSpace(Hos_Name);
        if(checkHospital(Hos_Name))
           Exsits = true;
        else
            cout << endl << "Sorry but you put worng name of the hospital..." << endl << "please try again" << endl << endl;

    }while(!Exsits);
    Exsits = false;
    for (int i = 0; i < amout_dep ; i++) {
        if(Hos_Name == Corona_Dep[i]->Hospital_Name){
            Doctor newDoctor(Hos_Name);
            cin >> newDoctor;
            if(SameID(&newDoctor,i)){
                Corona_Dep[i]->ADD_Doctor(newDoctor, Hos_Name);
                UpdateWorker();
            }else{
                cout << endl <<  "*********ERROR************" << endl;
                cout << "This Person exsits (SAME ID)" << endl << "      NOT GET IN" << endl;
                cout << "****************************" << endl << endl;
                Pause(3);
            }
            Exsits = true;
        }
    }if(!Exsits){
        cout << endl << Hos_Name << " hospital dont have corona department." << endl;
        cout << "you should open one" << endl << endl;
        Pause(3);
    }
}

void Corona_Management::AddNurse(){
    getchar();
    bool Exsits = false;
    string Hos_Name;
    cout << "To which department would you like to add the Nurse?" << endl << endl;
    do{
        printList();
        getline(cin,Hos_Name);
        Hos_Name = FixSpace(Hos_Name);
        if(checkHospital(Hos_Name))
            Exsits = true;
        else
            cout << endl << "Sorry but you put worng name of the hospital..." << endl << "please try again" << endl << endl;

    }while(!Exsits);
    Exsits = false;
    for (int i = 0; i < amout_dep ; i++) {
        if(Hos_Name == Corona_Dep[i]->Hospital_Name){
            Nurse newNurse(Hos_Name);
            cin >> newNurse;
            if(SameID(&newNurse,i)){
                Corona_Dep[i]->ADD_Nurse(newNurse, Hos_Name);
                UpdateWorker();
            }else{
                cout << endl <<  "********* ERROR ************" << endl;
                cout << "This Person exsits (SAME ID)" << endl << "       NOT GET IN" << endl;
                cout << "****************************" << endl << endl;
                Pause(3);
            }
            Exsits = true;
        }
    }if(!Exsits){
        cout << endl << Hos_Name << " hospital dont have corona department." << endl;
        cout << "you should open one" << endl << endl;
        Pause(3);
    }
}

void Corona_Management::printList()const{
    string HospitalNames[] = { "Sheba", "Wolfson" , "Rambam", "Assaf Harofeh", "Soroka"};
    cout << "The lists of Hospitals:" << endl;
    for(int i = 0 ; i < sizeof(HospitalNames)/sizeof(HospitalNames[0]) ; i++)
        cout << i+1 <<") " << HospitalNames[i] << endl;
    cout << "Enter the name: ";
}


string Corona_Management::changeCharSmallToBig(string Hospital_Name){
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
    return Hospital_Name;
}

string Corona_Management::FixSpace(string Hospital_Name){
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
    Hospital_Name = changeCharSmallToBig(Hospital_Name);
    return Hospital_Name;
}

bool Corona_Management::checkHospital(const string Hospital_Name)const{
    string HospitalNames[] = { "Sheba", "Wolfson" , "Rambam", "Assaf Harofeh", "Soroka"};
    for (int i = 0 ; i < sizeof(HospitalNames)/sizeof(HospitalNames[0]); i++) {
        if (Hospital_Name == HospitalNames[i])
            return true;
    }
    return false;
}

void Corona_Management::UpdateWorker(){
    delete [] this->Employee;
    this->allTheEmployee++;
    Worker** Temp = new Worker*[allTheEmployee];
    for (int i = 0 , j = 0; i < amout_dep && j < allTheEmployee ; i++) {
        for (int d = 0 ; d < Corona_Dep[i]->Dsize; d++) {
            Temp[j++] = Corona_Dep[i]->D[d];
        }
        for (int n = 0; n < Corona_Dep[i]->Nsize; n++) {
            Temp[j++] = Corona_Dep[i]->N[n];
            
        }
    }
    Employee = Temp;
}

void Corona_Management::UpdatePatient(){
    if (all_Pantient){
        delete [] this->all_Pantient;
        this->AllPsize++;
        Patient** Temp = new Patient*[AllPsize];
        for (int i =0 , j = 0; i < amout_dep && j < AllPsize; i++) {
            for (int p = 0 ; p < Corona_Dep[i]->Psize ; p++) {
                Temp[j++] = Corona_Dep[i]->P[p];
            }
        }
        all_Pantient = Temp;
    }else{
        for(int i = 0 ; i < amout_dep ; i++)
            AllPsize += Corona_Dep[i]->Psize;
        all_Pantient = new Patient*[AllPsize];
        for (int i = 0, j = 0; i < amout_dep && j < AllPsize; i++) {
            for (int p = 0 ; p < Corona_Dep[i]->Psize; p++) {
                all_Pantient[j++] = Corona_Dep[i]->P[p];
            }
        }
    }
}

void Corona_Management::PrintDepartmentDetails(){
    getchar();
    int index = 0;
    bool Exsits = false;
    cout << endl << "-----ALL Department-----" << endl;
    do{
        for (int i = 0; i < amout_dep; i++)
            cout << i+1 << ") "<< Corona_Dep[i]->Hospital_Name <<endl;
        cout << "Enter Number: ";
        cin >> index;
           if(index > 0 && index <= amout_dep)
              Exsits = true;
           else
               cout << endl << "The number is not in list." << endl << "please try again" << endl << endl;
       }while(!Exsits);
    cout << *Corona_Dep[index-1] << endl;;
    cout <<"---------End This Department---------" << endl;
    Pause(5);
}

bool Corona_Management::SameID(Person* employe,int index){
    string ID = employe->get_ID();
    
    for(int i = 0 ; i < Corona_Dep[index]->Dsize ; i++){
        if (ID == Corona_Dep[index]->D[i]->get_ID()) {
            return false;
        }
    }
    for(int i = 0 ; i < Corona_Dep[index]->Nsize ; i++){
        if(ID == Corona_Dep[index]->N[i]->get_ID())
            return false;
    }
    for(int i = 0 ; i < Corona_Dep[index]->Psize ; i++){
        if(ID == Corona_Dep[index]->P[i]->get_ID())
            return false;
    }
    return true;
}

void Corona_Management::Pause(int dur)const{
    long temp = time(NULL) + dur;
    while(temp > time(NULL));
}


void Corona_Management::AddDepartment(){
    getchar();
    bool DepExsist = false;
    string hos_name;
    cout << endl << "Where you want to open the department?" << endl;
    do{
        printList();
        getline(cin,hos_name);
        hos_name = FixSpace(hos_name);
        if(checkHospital(hos_name))
            DepExsist = true;
        else
            cout << endl << "Sorry but you put worng name of the hospital..." << endl << "please try again" << endl << endl;
    }while(!DepExsist);
    DepExsist = false;
    for (int i = 0; i < amout_dep; i++) {
        if(hos_name == Corona_Dep[i]->Hospital_Name)
            DepExsist = true;
    }
    if(!DepExsist){
        Corona_Department** Temp = new Corona_Department*[amout_dep+1];
        for (int i = 0 ; i < amout_dep; i++)
            Temp[i] = Corona_Dep[i];
        Temp[amout_dep] = new Corona_Department(hos_name);
        this->amout_dep++;
        delete [] this->Corona_Dep;
        Corona_Dep = Temp;
    }else{
        cout << endl << "********** ERROR **********" << endl;
        cout << "The "<< hos_name <<" Hospital has a Corona Department" << endl;
        cout <<"***************************" << endl << endl;
        Pause(3);
    }
}

void Corona_Management::PrintDoctorsDetails()const{
    for (int i = 0 ; i < amout_dep; i++) {
        cout << endl << "---------" << Corona_Dep[i]->Hospital_Name << "---------"<< endl;
        for (int j = 0; j < Corona_Dep[i]->Dsize; j++) {
            cout << j+1 << ")" << *(Corona_Dep[i]->D[j]) << endl;
        }
        cout << "------------------------" << endl << endl;
        Pause(5);
    }
}

void Corona_Management::PrintSalary()const{
    string ID;
    Person* Help;
    bool flag = false;
    cout << "Enter the ID" << endl;
    cin >> ID;
    for (int i = 0; i < allTheEmployee && !flag; i++) {
        Help = Employee[i];
        if(Help->get_ID() == ID){
            flag = true;
            if(typeid(*Help) == typeid(Doctor)){
                Doctor* help = dynamic_cast<Doctor*>(Help);
                if(help)
                    cout << endl << *help << endl;
            }else if(typeid(*Help) == typeid(Nurse)){
                Nurse* help = dynamic_cast<Nurse*>(Help);
                if(help)
                    cout << endl << *help << endl;
            }
        }else
            flag = false;
    }
    if(!flag){
        cout << endl <<"Sorry but we dont have the ID on our system." << endl;
        Pause(3);
    }
}

void Corona_Management::AddPatient(){
    getchar();
    string Hos_Name;
    bool Exsits = false;
    cout << endl << "Where to transfer the patient?" << endl;
    do{
        printList();
        getline(cin,Hos_Name);
        Hos_Name = FixSpace(Hos_Name);
        if(checkHospital(Hos_Name))
            Exsits = true;
        else
        cout << endl << "Sorry but you put worng name of the hospital..." << endl << "please try again" << endl << endl;
    }while(!Exsits);
    Exsits = false;
        for (int i = 0; i < amout_dep ; i++) {
            if(Hos_Name == Corona_Dep[i]->Hospital_Name){
                if(Corona_Dep[i]->Psize < MAX){
                    Patient newPatient(Hos_Name);
                    cin >> newPatient;
                    if(SameID(&newPatient,i)){
                        Corona_Dep[i]->ADD_Patient(newPatient,Hos_Name);
                        UpdatePatient();
                    }else{
                        cout << endl <<  "********* ERROR ************" << endl;
                        cout << "This Person exsits (SAME ID)" << endl << "       NOT GET IN" << endl;
                        cout << "****************************" << endl << endl;
                        Pause(3);
                    }
                    Exsits = true;
                }else{
                    Exsits = true;
                    cout << "******** ERROR ********" << endl << "There are already "<< MAX <<" people in the department" << endl <<"***********************"<<endl;
                    Pause(3);
                }
            }
        }if(!Exsits){
            cout << endl << Hos_Name << " hospital dont have corona department." << endl;
            cout << "you should open one" << endl << endl;
            Pause(3);
        }
}

void Corona_Management::AddCoronaTestToPatientById(){
    string ID;
    Person* Help;
    bool res;
    bool flag = false;
    cout << "Enter the ID of the patient" << endl;
    cin >> ID;
    for (int i = 0; i < AllPsize && !flag; i++) {
        Help = all_Pantient[i];
        if(Help->get_ID() == ID){
            flag = true;
            if(typeid(*Help) == typeid(Patient)){
                Patient* help = dynamic_cast<Patient*>(Help);
                if(help){
                    cout << "What is the result of the test?(Positive ->1 / Negative -> 0)" << endl;
                    cin >> res;
                    if(res)
                        help->add_NumTestCorona();
                    else
                        help->add_NegativeTests();
                }
            }
        }
    }if(!flag){
        cout << "Sory This Patient not exsits in our system." << endl;
        Pause(3);
    }
}

void Corona_Management::Releasing(){
    int count = 0;
    Patient* temp = NULL;
    for (int i = 0; i < AllPsize; i++) {
        if(all_Pantient[i]->get_NegativeTests() >= 2){
            temp = all_Pantient[i];
            all_Pantient[i] = all_Pantient[AllPsize-1];
            all_Pantient[AllPsize-1] = temp;
            this->AllPsize--;
            i--;
        }
        if(temp != NULL){
            for (int i = 0; i < amout_dep; i++) {
                for (int j = 0; j < Corona_Dep[i]->Psize ; j++) {
                    if(temp == Corona_Dep[i]->P[j]){
                        Corona_Dep[i]->P[j] = Corona_Dep[i]->P[Corona_Dep[i]->Psize-1];
                        Corona_Dep[i]->P[Corona_Dep[i]->Psize-1] = temp;
                        Corona_Dep[i]->Psize--;
                        j--;
                    }
                }
            }
            delete temp;
            count++;
        }
    }
    if(count > 0){
        cout << "Total left " << count << endl;
        Pause(3);
    }else{
        cout << "No one left" << endl;
        Pause(3);
    }
}
void Corona_Management::PrintExcellenceWorker() const{
    for (int i = 0; i < allTheEmployee; i++) {
        if(typeid(*Employee[i])==typeid(Doctor)){
            Doctor* Help = dynamic_cast<Doctor*>(Employee[i]);
            if(Help != NULL){
                if(Help->Excllent()){
                    Help->whoIam();
                    cout << *Help << endl;
                }
            }
        }else if(typeid(*Employee[i])==typeid(Nurse)){
            Nurse* Help = dynamic_cast<Nurse*>(Employee[i]);
            if(Help != NULL){
                if(Help->Excllent()){
                    Help->whoIam();
                    cout << *Help << endl;
                }
            }
        }
    }
}

Corona_Management::~Corona_Management(){
    for(int i = 0; i < amout_dep; i++)
        delete Corona_Dep[i];
    delete Corona_Dep;
    delete [] all_Pantient;
    delete [] Employee;
}

void Corona_Management::PrintNurseWithSmallestSalary(){
    int index = 0;
    double MINI = 10000000;
    for (int i = 0; i < allTheEmployee; i++) {
        if(typeid(*Employee[i])==typeid(Nurse) && Employee[i]->Salery() < MINI){
            MINI = Employee[i]->Salery();
            index = i;
        }
    }if(index != 0){
        Nurse* help = dynamic_cast<Nurse*>(Employee[index]);
        if(help != NULL){
            cout << endl << "------THE MINI SALERY-------"<< endl << *help << endl << "-----------------" << endl;
            Pause(3);
        }
    }
    
}
