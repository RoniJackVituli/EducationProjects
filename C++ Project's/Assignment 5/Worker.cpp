//
//  Worker.cpp
//  Hospital
//
//  Created by Roni Jack Vituli on 10/06/2020.
//  Copyright © 2020 Roni Jack Vituli. All rights reserved.
//

#include "Worker.h"


//Worker::Worker():Years_of_seniority(0){
////    bool big = false;
////    do{
////        cout << "How many years do you work?" << endl;
////        cin >> Years_of_seniority ;
////        if(Years_of_seniority >= 0)
////            big = true;
////        else
////            cout << "You cannot enter a negative number, Please try again" << endl;
////    }while(!big);
//}

void Worker::Print()const{
    Person::Print();
    cout << "My Salery is: " << Salery() << endl;
    cout << "Work in this job: " << Years_of_seniority << " years" << endl;
}


void Worker::InPut(){
    Person::InPut();
    bool big = false;
    do{
        cout << "How many years do you work?" << endl;
        cin >> Years_of_seniority ;
        if(Years_of_seniority >= 0)
            big = true;
        else
            cout << "You cannot enter a negative number, Please try again" << endl;
    }while(!big);
}

bool Worker::operator==(const Worker& sec) const{
    if(this->Years_of_seniority != sec.Years_of_seniority)
        return false;
    return true;
    
}


int Worker::get_Years_of_seniority() const{
    return Years_of_seniority;
}

