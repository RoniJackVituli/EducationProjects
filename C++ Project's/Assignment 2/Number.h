#ifndef Number_h
#define Number_h


#include <iostream>
#include <string.h>

using namespace std;
class Number{
    
private:
    
    int* present_Num;
    int amount_of_Digits;
    bool symbol;
    
public:
    
    Number();
    Number(int* ,int ,bool);
    Number(const Number&);
    ~Number();
        
    void set_Amount_of_Digits(int);// check
    int get_Amount_of_Digits()const;// check
    void set_Symbol(bool);// check
    bool get_Symbol()const;// check
    void set_present_Num(int*);// check
    int* get_present_Num()const;// check
    
    void UpdateNumber(int* ,int size); // check
    void ChangeSymbol(); // check
    void PrintNumber()const;// check
    int SumOfNumber();// check
    int Change_To_Integer();//check
    bool itsPalidrom();//check
    bool itsPrime();//check
    bool equal_objects(const Number&)const;//check
    bool isDivied(Number&);//check
    Number Add(Number&); //check
    Number Sub(Number&); //check
};



#endif /* Number_h */
