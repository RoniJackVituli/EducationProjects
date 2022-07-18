#include "Doctor.h"


Doctor::Doctor(string hos):Hospital_Name(hos),the_doc_is_Pro(false),feedback(0){}

void Doctor::InPut(){
    cout << endl << "-------- Doctor ---------" << endl << endl;
    Worker::InPut();
    bool big = false;
        cout << "Are you a professor? (Yes -> 1 / NO -> 0)" << endl;
        cin >> the_doc_is_Pro;
        do{
            cout << "How many feedback do you have?" << endl;
            cin >> feedback;
            if(feedback >= 0)
                big = true;
            else
                cout << "You cannot enter a negative number, Please try again" << endl;
        }while(!big);
}

istream& operator >>(istream&input ,Doctor& doctor){
    doctor.InPut();
    return input;
}
ostream& operator <<(ostream& output,const Doctor& doctor){
    doctor.Print();
    return output;
}

Doctor::Doctor(const Doctor& sec){
    this->Hospital_Name = sec.Hospital_Name;
    this->the_doc_is_Pro = sec.the_doc_is_Pro;
    this->feedback = sec.feedback;
}

double Doctor::Salery() const{
    if(the_doc_is_Pro)
        return Basis_Salery+200*Years_of_seniority+50*feedback+2000;
    return Basis_Salery+200*Years_of_seniority+50*feedback;
}

bool Doctor::Excllent(){
    if(feedback>10)
        return true;
    return false;
}

void Doctor::Print()const{
    Worker::Print();
    cout << "I work at " << Hospital_Name << " Hospital." << endl;
    if(the_doc_is_Pro)
        cout << "I am also professor" << endl;
    
}
void Doctor::whoIam() const{
    cout << "I am a Docotor" << endl;
}

bool Doctor::operator==(const Doctor& sec)const{
    if(this->Person::get_ID() != sec.Person::get_ID())
        return false;
    return true;
}


