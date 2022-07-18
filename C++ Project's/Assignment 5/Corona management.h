//
//  Hospital
//
//  Created by Roni Jack Vituli on 11/06/2020.
//  Copyright © 2020 Roni Jack Vituli. All rights reserved.
//

#ifndef Corona_management_h
#define Corona_management_h

#include "Worker.h"
#include "Corona Department.h"
#include "Patient.h"
#include <typeinfo>
#define MAX 3

typedef enum {ADD_NURSE = 1,ADD_DOCTOR,ADD_DEPARTMENT,PRINT_DEPARTMENT_DETAILS,PRINT_DOCTORS_DETAILS,PRINT_SALARY_BY_ID,ADD_PATIENT,ADD_CORONA_TEST_TO_PATIENT_ID,RELEASING_PATIENTS,PRINT_EXCELLENCE_WORKER,PRINT_NURSE_DETAILS_WITH_SMALLEST_SALARY,EXIT} numbers;

class Corona_Management{
    Patient** all_Pantient;
    int AllPsize;
    Corona_Department** Corona_Dep;
    int amout_dep;
    Worker** Employee;
    int allTheEmployee;
    void printList()const;
    void AddDoctor();
    void AddNurse();
    void AddDepartment();
    void PrintDoctorsDetails()const;
    void PrintSalary()const;
    void AddPatient();
    void AddCoronaTestToPatientById();
    void Releasing();
    void PrintExcellenceWorker()const;
    void PrintNurseWithSmallestSalary();
    void printOptions()const;
    bool SameID(Person*, int i);
    void UpdateWorker();
    void UpdatePatient();
    void PrintDepartmentDetails();
    bool checkHospital(const string)const;
    string FixSpace(string);
    string changeCharSmallToBig(string);

public:

    Corona_Management();
    ~Corona_Management();
   
    
    //-----------my function------------
    void Menu();
    friend class Corona_Department;
    void Pause(int)const;
    
};




#endif /* Corona_management_hpp */
