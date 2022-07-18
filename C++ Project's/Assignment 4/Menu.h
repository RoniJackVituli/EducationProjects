//
//  Menu.h
//  Dictionary
//
//  Created by Roni Jack Vituli on 21/05/2020.
//  Copyright © 2020 Roni Jack Vituli. All rights reserved.
//

#ifndef Menu_h
#define Menu_h
#include "Dictionary.h"
typedef enum {first = 1 , second , thrid , fourth , fifth , sixth} numbers;

class Menu{
    
private:
    Dictionary* THE_BOOK;
    
public:
    Menu();
    ~Menu();
    
    
    void commonExplanation();
    void PrintMenu(bool);
    void MainMenu();
    bool checkDefinition(const String&, int)const;
    bool checkExplanation(const String&, int)const;
    
};



#endif /* Menu_hpp */
