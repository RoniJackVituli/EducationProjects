//
//  Set.h
//  Template & Excption
//
//  Created by Roni Jack Vituli on 16/06/2020.
//  Copyright © 2020 Roni Jack Vituli. All rights reserved.
//

#ifndef Set_h
#define Set_h
#include "type.h"
#include <iostream>
using namespace::std;

template <class T>
class Set {
    T* group;
    int size_group;
public:
    Set():group(NULL),size_group(0){};
    Set(T*,int);
    Set(const Set<T>&);
    ~Set();
    
    bool isThere(const T&)const;
    void getType()const;
    
    Set<T>& operator =(const Set<T>&);
    bool operator ==(const Set<T>&) const;
    void operator +=(const T);
    void operator -=(const T&);
    Set<T> operator +(const Set<T>&);
    Set<T>& operator -(const Set<T>&);
    bool operator >(const Set<T>&)const;
    template <class U>
    friend ostream& operator << (ostream&,const Set<U>&);
    
};

//Realizations

template <class T>
Set<T>::Set(T* gro,int size):group(NULL),size_group(0){
    this->size_group = size;
    this->group = new T[this->size_group];
    for (int i = 0; i < size_group ; i++) {
        this->group[i] = gro[i];
    }
}

template <class T>
Set<T>::Set(const Set<T>& obj){ // c'Ctor (copy)
    this->size_group = obj.size_group;
    this->group = new T[this->size_group];
    for (int i = 0; i < size_group; i++) {
        group[i] = obj.group[i];
    }
}

template <class T>
void Set<T>::getType() const{
    cout << "The Type is: " << type(this) << endl;
}

template <class T>
Set<T>& Set<T>::operator = (const Set<T>& obj){
    this->size_group = obj.size_group;
    this->group = new T[size_group];
    for (int i = 0; i < size_group; i++) {
        this->group[i] = obj.group[i];
    }
    return *this;
}

template <class T>
bool Set<T>::operator==(const Set<T>& obj) const{
    int count = 0;
    T temp;
    if(this->size_group != obj.size_group)
        return false;
    for (int i = 0; this->size_group; i++) {
        temp = this->group[i];
        count = 0;
        for (int j = 0; j < obj.size_group; j++) {
            if(temp == obj.group[j])
                count++;
        }
        if(count != 1)
            return false;
    }
    return true;
}

template <class T>
void Set<T>::operator+=(const T var){
    if(!isThere(var)){
        T* Temp = new T[this->size_group+1];
        for (int i = 0; i < this->size_group; i++)
            Temp[i] = this->group[i];
        Temp[size_group] = var;
        delete [] this->group;
        this->size_group++;
        this->group = Temp;
    }
    
}

template <class T>
Set<T> Set<T>::operator+(const Set<T>& obj){ //
    Set<T> objNew;
    if(obj.size_group > this->size_group){
        for (int i = 0; i < obj.size_group; i++){
                if(!this->isThere(obj.group[i]))
                    objNew += obj.group[i];
        }
        for (int j = 0; j < this->size_group; j++)
            objNew += this->group[j];
        return objNew;
    }else{
        for (int i = 0; i < this->size_group; i++){
                if(!obj.isThere(this->group[i]))
                    objNew += this->group[i];
        }
        for (int j = 0; j < obj.size_group; j++) 
            objNew += obj.group[j];
        return objNew;
    }
}


template <class T>
bool Set<T>::isThere(const T& var) const{
    for (int i = 0; i < this->size_group; i++) {
        if(this->group[i] == var)
            return true;
    }
    return false;
}

template <class T>
void Set<T>::operator -=(const T& var){
    if(isThere(var)){
        int count = 0;
        for (int i = 0; i < size_group; i++)
            if(!(group[i] == var))
                count++;
        T* Temp = new T[count];
        for (int i = 0, j = 0; i < size_group && j < count; i++) {
            if(!(group[i] == var)){
                Temp[j] = group[i];
                j++;
            }
        }
        delete [] group;
        this->size_group = count;
        this->group = Temp;
    }else{
        throw "The Varibale not in the array.";
    }
}

template <class T>
Set<T>& Set<T>::operator -(const Set<T>& obj){
    for (int i = 0; i < this->size_group; i++) {
        if(obj.isThere(this->group[i])){
            *this -= this->group[i];
            i--; 
        }
    }
    return *this;
}

template <class T>
bool Set<T>::operator >(const Set<T>& obj)const{
    for (int i = 0; i < obj.size_group; i++) {
        if(!this->isThere(obj.group[i]))
            return false;
    }
    return true;
}

template <class U>
ostream& operator << (ostream& output ,const Set<U>& obj){
    obj.getType();
    output << "The size of the group is: " << obj.size_group << endl;
    output << "{";
    for(int i=0; i < obj.size_group ; i++){
        output << obj.group[i];
        if(i+1 < obj.size_group){
            output << ", " ;
        }
    }
    output<< "}" << endl;
    return output;
}

template <class T>
Set<T>::~Set() {
    delete [] group;
}

#endif /* Set_h */
