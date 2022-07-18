
#include "Employee.h"
using namespace std;

Employee::Employee() {
    strcpy(full_name, "UnKnown");
    strcpy(Id, "0000000000");
    years_of_seniority = 0;
    number_of_excellence = 0;
    degree = false;
}

Employee::Employee(char Full_name[], char Ide[], int Years_of_seniority, int Number_of_excellence, bool Degree) {
    if(strlen(Full_name) > NAME_SIZE){
        cout << "Long Name...."<<endl;
        strcpy(full_name, "UnKnown");
    }else{
        strcpy(full_name, Full_name);
    }
    if(Ide[0] == '0' && Ide[0] != '9')
        strcpy(Id, "0000000000");
    else
        strcpy(Id, Ide);
    if (Years_of_seniority < 0)
        years_of_seniority = 0;
    else
        years_of_seniority = Years_of_seniority;
    degree = Degree;
}

Employee::Employee(const Employee &other) {
    strcpy(full_name, other.full_name);
    strcpy(Id, other.Id);
    years_of_seniority = other.years_of_seniority;
    number_of_excellence = other.number_of_excellence;
    degree = other.degree;
}

int Employee::Bonus() {
    int Bounus = 0 , Max = 3000;
    Bounus = 550*number_of_excellence;
    if (Bounus > Max)
        return Max;
    return Bounus;
}

int Employee::Salary() {
    int salary = 0;
    salary = 6000 + (years_of_seniority * 1000) + Bonus();
    if (degree)
        salary+=2000;
    return salary;
}

void Employee::Show_Employee() {
    cout << "Employee Name: "<< full_name << ",ID: "<< Id  << ",Seniority: " << years_of_seniority << ",Excellence: " << number_of_excellence ;
    if(degree)
        cout << ",Degree: Yes"<< endl;
    else
        cout << ", Degree: No"<< endl;
    cout << "Bouns: " << Bonus() << endl << "Salary: " << Salary() << endl;
}

void Employee::set_full_name(const char Full_name[]) {
    strcpy(full_name, Full_name);
}

void Employee::set_Id(const char Ide[]) {
    strcpy(Id, Ide);
}

void Employee::set_years_of_seniority(const int Years_of_seniority) {
    years_of_seniority = Years_of_seniority;
}

void Employee::set_number_of_excellence(const int Number_of_excellence) {
    number_of_excellence = Number_of_excellence;
}

void Employee::set_degree(const bool Degree) {
    degree = Degree;
}

char* Employee::get_full_name(){
    return full_name;
}

char* Employee::get_Id() {
    return Id;
}

int Employee::get_years_of_seniority() {
    return years_of_seniority;
}

int Employee::get_number_of_excellence() {
    return number_of_excellence;
}

bool Employee::get_degree() {
    return  degree;
}
