#include "Number.h"
#define NO_ERROR 0
Number input();
char ChangeBoolToChar(bool);
bool ChangeCharToBool(char);

int main(){
    Number N1 = input();
    Number N2 = input(), N3(N1);
    int size;
    cout << endl << "-------N1 + N3---------"<<endl;
    cout << "N1 -> ";
    N1.PrintNumber();
    cout << "N3 -> ";
    N3.PrintNumber();
    cout << "(N1) It Prime ? " << ChangeBoolToChar(N1.itsPrime()) << endl;
    cout << "(N3) Sum of the Digits: " << N3.SumOfNumber() << endl;
    cout << "The Objectes (N1 & N3) are Equal?  " << ChangeBoolToChar(N1.equal_objects(N3)) << endl;
    N1.ChangeSymbol();
    cout << "(N1)Change the sign of the number: ";
    N1.PrintNumber();
    cout<< endl << "-----Upadate--- (N1)"<<endl;
    cout << "Enter size\n";
    cin >> size;
    int arr[size];
    cout << "Enter Number\n";
    for (int i = 0 ; i < size; i++)
        cin >> arr[i];
    N1.UpdateNumber(arr, size);
    cout << "The new number is ";
    N1.PrintNumber();
    cout << "its Palidrom ? " << ChangeBoolToChar(N1.itsPalidrom()) <<endl;
    cout << "(N1) Sum of the Digits: " << N1.SumOfNumber() << endl;
    cout << "The Objectes (N1 & N3) are Equal? " << ChangeBoolToChar(N1.equal_objects(N3)) << endl;
    cout << endl << "---------ADD & SUB----------"<< endl;
    cout << "N2 -> ";
    N2.PrintNumber();
    cout << "N3 -> ";
    N3.PrintNumber();
    Number N4 = N2.Add(N3);
    cout << "N2 + N3 = " ;
    N4.PrintNumber();
    Number N5 = N3.Sub(N2);
    cout << "N3 - N2 = ";
    N5.PrintNumber();
    cout << endl;
    return NO_ERROR;
}
Number input(){
        int size;
        char ch;
        bool sign;
        cout << "Enter Digits" << endl;
        cin >> size;
        int arr[size];
        cout << "Enter Number" <<endl;
        for (int i = 0; i < size; i++)
            cin >> arr[i];
        cout << "The number is Positive/Negative? (Y/N)"<<endl;
        cin >> ch;
        sign = ChangeCharToBool(ch);
        Number N(arr,size,sign);
        return N;
}

bool ChangeCharToBool(char ch){
    if (ch == 'Y' || ch == 'y')
        return true;
    else if(ch == 'N' || ch == 'n')
        return false;
    else
        cout << "You put worng char please try again\n";
    exit(0);
}
char ChangeBoolToChar(bool sign){
    if(sign)
        return 'Y';
    else
        return 'N';
}
