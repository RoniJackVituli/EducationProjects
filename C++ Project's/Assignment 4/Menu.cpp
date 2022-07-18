//  Menu.c
//  Dictionary
//
//  Created by Roni Jack Vituli on 21/05/2020.
//  Copyright © 2020 Roni Jack Vituli. All rights reserved.
//

#include "Menu.h"

Menu::Menu():THE_BOOK(NULL){}

void Menu::MainMenu(){ // RUN THE PROGRAM.
    int choice = 0 ;
    Definition D1;
    String S1;
    bool flag = false , check = true;
    bool onlyOnce = true;
    do{
        PrintMenu(onlyOnce);
        cin >> choice;
        getchar();
        cout << endl;
        if (THE_BOOK != NULL || choice == sixth || choice == first) {
            switch (choice) {
                case first:
                    cout << "---------CREATE NEW DICTIONARY---------" << endl << endl;
                    if (onlyOnce) {
                        THE_BOOK = new Dictionary();
                        cin >> *THE_BOOK;
                        cout << endl;
                        if(THE_BOOK->get_book_of_def() != NULL)
                            onlyOnce = false;
                    }else{
                        cout << "********* Sory you choice this number you had only one time *********\n"<<endl;
                    }
                    break;
                case second:
                    cout << "---------ADD NEW DEFINITION TO YOUR DICTIONARY---------\n" << endl;
                    cin >> D1;
                    *THE_BOOK += D1;
                    cout << endl;
                    break;
                case thrid:
                    cout << "---------ADD EXPLANANTION---------" << endl;
                    cout << "what the name of definiton that you want to add explanation?" << endl;
                    cin >> S1;
                    for (int i = 0; i < THE_BOOK->get_num_of_Definiton(); i++) {
                        if(checkDefinition(S1,i)){
                            check = false;
                            cout << "Enter the new explanation" << endl;
                            cin >> S1;
                            if(!checkExplanation(S1, i))
                                *THE_BOOK->get_book_of_def()[i] += S1;
                            else
                                cout << endl << "****** sorry you have this explanation on that definition ******"<< endl<<endl;
                        }
                    }
                    if(check)
                        cout<< "****** sorry but we dont find this definition ******" << endl << endl;
                    break;
                case fourth:
                    cout << "---------SEARCH DEFINITION ON DICTIONARY---------" << endl;
                    check = true;
                    cout << "Enter the definition name" << endl;
                    cin >> S1;
                    for (int i = 0; i<THE_BOOK->get_num_of_Definiton(); i++) {
                        if(checkDefinition(S1,i)){
                            check = false;
                            cout << *THE_BOOK->get_book_of_def()[i] << endl;
                        }
                    }
                    cout << "-------------------------------------------------" << endl;
                    if(check)
                        cout << endl <<"Unknow Word!" << endl;
                    break;
                case fifth:
                    cout << "---------ALL COMMON EXPLANATION---------" << endl;
                    commonExplanation();
                    cout << endl << endl;
                    break;
                case sixth:
                    cout << "------Thank You and GoodBye------" << endl<<endl;
                    flag = true;
                    break;

                default:
                    cout << "you choice worng number please try again." << endl;
                break;
            }
        }else{
            cout << "****** you should press 1 to create dictionary ******" << endl << endl;
        }
    }while(!flag);
    
}
    

void Menu::PrintMenu(bool onlyOnce){ // print the menu.
    if(onlyOnce)
        cout << "(1) create dictionary (HAVE ONLY ONCE THIS OPTION)" << endl;
    cout << "(2) enter a new definition" << endl;
    cout << "(3) add a new explanation to the definition￼￼￼ exists in the dictionary" << endl;
    cout << "(4) search definition in dictionary" << endl;
    cout << "(5) view all definitions that have at least one common comment" << endl;
    cout << "(6) EXIT" << endl;
}

bool Menu::checkDefinition(const String& str, int i)const{ // check if definition exsits on dictionary.
    if (THE_BOOK->get_book_of_def()[i]->get_Def_Word() == str)
        return true;
    return false;
}

bool Menu::checkExplanation(const String& str, int i )const{ // check if explanation exsits on definition.
    for (int j = 0 ; j < THE_BOOK->get_book_of_def()[i]->get_num_of_explanation(); j++) {
        if (str == *THE_BOOK->get_book_of_def()[i]->get_explanation()[j]) {
            return true;
        }
    }
    return false;
    
}

void Menu::commonExplanation(){ // call to checkExplanation
    THE_BOOK->checkExplanation();
}

Menu::~Menu(){ //dtor
    delete THE_BOOK;
}
