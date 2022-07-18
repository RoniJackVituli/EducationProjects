
#include "Employee.h"
using namespace std;

int main() {
    char name[51] = "Israel Israeli";
    char id[10] = "123456789";
    Employee emp(name, id, 3, 2, true);

    emp.Show_Employee();
    cout << endl;
    emp.set_years_of_seniority(2);
    emp.Show_Employee();
    cout << endl;
    emp.set_number_of_excellence(3);
    emp.Show_Employee();
    cout << endl;

    return 0;
}
