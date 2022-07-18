#include "Number.h"

//Constrctur & Copy Constrctur & Distractur.
Number::Number(){
    present_Num = new int[1];
    present_Num[0] = 0;
    amount_of_Digits = 1;
    symbol = true;
}
Number::Number(int* Number, int Size , bool Symbol):amount_of_Digits(Size),symbol(Symbol){
    if(Size <= 0){
        present_Num = new int[1];
        present_Num[0] = 0;
        amount_of_Digits = 1;
    }else{
    present_Num = new int[sizeof(Number)];
    for (int i=0; i<Size; i++)
        present_Num[i] = Number[i];
    }
}
Number::Number(const Number& sec){
    this->present_Num = new int[sec.amount_of_Digits];
    for (int i = 0 ; i < sec.amount_of_Digits ; i++)
        this->present_Num[i] = sec.present_Num[i];
    this->amount_of_Digits = sec.amount_of_Digits;
    this->symbol = sec.symbol;
}
Number::~Number(){
    cout << "dtor Number\n";
    delete [] present_Num;
}

//function get & set.
int* Number::get_present_Num()const{
    return present_Num;
}
void Number::set_present_Num(int* Present){
    present_Num = Present;
}
void Number::set_Amount_of_Digits(int Digits){
    amount_of_Digits = Digits;
}
int Number::get_Amount_of_Digits()const{
    return amount_of_Digits;
}
void Number::set_Symbol(bool sign){
    symbol = sign;
}
bool Number::get_Symbol()const{
    return symbol;
}


//Function on Class Number
void Number::PrintNumber()const{
    if (symbol){
        for (int i = 0; i<amount_of_Digits; i++)
            cout << present_Num[i];
    }else{
        cout << "-";
        for (int i = 0 ; i<amount_of_Digits; i++)
            cout << present_Num[i];
    }
    cout << endl;
}
void Number::UpdateNumber(int* num,int size){
    delete [] get_present_Num();
    int* newNum = NULL;
    newNum = new int[size];
    for (int i = 0 ; i<size; i++)
        newNum[i] = num[i];
    set_present_Num(newNum);
    set_Amount_of_Digits(size);
}
void Number::ChangeSymbol(){
    if(symbol)
        set_Symbol(false);
    else
        set_Symbol(true);
}
int Number::SumOfNumber(){
    int sum = 0;
    for (int i = 0 ; i < amount_of_Digits; i++)
        sum += present_Num[i];
    return sum;
}
int Number::Change_To_Integer(){
    int Num = 0;
    for(int i = 0 ; i<amount_of_Digits; i++)
        Num = (Num + present_Num[i])*10;
    if (symbol) {
        Num = Num/10;
        return Num;
    }else{
        Num = (Num/10)*(-1);
        return Num;
    }
}
bool Number::itsPalidrom(){
    bool flag = true;
    for (int i = 0 , j = amount_of_Digits-1; i<amount_of_Digits && flag; i++ , j--) {
        if(present_Num[i] == present_Num[j])
            flag = true;
        else
            flag = false;
    }
    return flag;
}
bool Number::itsPrime(){
    int number = Change_To_Integer();
    int counter = 0;
    if(!symbol)
        number *=(-1);
    for (int i = 1; i<=number; i++) {
        if(number%i == 0)
            counter++;
    }
    if (counter ==  2)
        return true;
    else
        return false;
}
bool Number::equal_objects(const Number& sec)const{
    bool flag = false;
    if(this->amount_of_Digits == sec.amount_of_Digits)
        flag = true;
    else
        return false;
    if(this->symbol == sec.symbol)
        flag = true;
    else
        return false;
    for (int i = 0; i < this->amount_of_Digits && flag; i++) {
        if (this->present_Num[i] == sec.present_Num[i])
            flag = true;
        else
            flag = false;
    }
        return flag;
}
bool Number::isDivied(Number& sec){
    int num1 = this->Change_To_Integer(), num2 = sec.Change_To_Integer();
    return num1%num2  == 0;
}

Number Number::Add(Number& sec){
    int num1 = this->Change_To_Integer();
    int num2 = sec.Change_To_Integer();
    int num3 = num1 + num2,temp = 0;
    int size = 0;
    bool sign  = true;
    if(num3 >= 0){
        sign = true;
    }else{
        num3 *= (-1);
        sign = false;
    }
    temp = num3;
    while(temp != 0){
        temp /= 10;
        size++;
    }
    int NUM[size];
    for (int i = size-1; i >= 0 && num3 != 0; i--) {
        NUM[i] = num3%10;
        num3 /= 10;
    }
    Number N(NUM,size,sign);
    return N;
}
Number Number::Sub(Number& sec){
    int num1 = this->Change_To_Integer();
    int num2 = sec.Change_To_Integer();
    int num3 = num1 - num2,temp = 0;
    int size = 0;
    bool sign;
    if(num3 >= 0){
        sign = true;
    }else{
        num3 *= (-1);
        sign = false;
    }
    temp = num3;
    while(temp != 0){
        temp /= 10;
        size++;
    }
    int NUM[size];
    for (int i = size-1; i >= 0 && num3 != 0; i--) {
        NUM[i] = num3%10;
        num3 /= 10;
    }
    Number N(NUM,size,sign);
    return N;
}
