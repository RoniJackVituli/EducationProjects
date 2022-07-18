//
//  type.h
//  Template & Excption
//
//  Created by Roni Jack Vituli on 17/06/2020.
//  Copyright © 2020 Roni Jack Vituli. All rights reserved.
//

#ifndef type_h
#define type_h

#include <string>
#include <typeinfo>

std::string demangle(const char* name);

template <class T>
std::string type(const T& t) {

    return demangle(typeid(t).name());
}

#endif /* type_h */
