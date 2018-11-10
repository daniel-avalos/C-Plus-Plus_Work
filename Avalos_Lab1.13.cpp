// Daniel Avalos, 2018
// Lab Exercise 13, Completed
// Calculates pay cheque amounts for bi-weekly and bi-monthly

#include <iostream>
#include <iomanip>
using namespace std;

// Displays splash block and paycheque amounts
int main() {

    float gross_pay;    // Our Emp's gross annual pay
    gross_pay = 39000;

    // Splash block
    cout << "\n\nExercise 13: Pay Period Gross Pay\n";
    cout << "    Calculating pay cheque amounts for bi-weekly and bi-monthly\n";
    cout << "    cheques for an employee making $39,000 annually";
    cout << "\n\n---------------------------------------\n\n";

    // Display amounts
    cout << "Annual Gross Salary \t\t\t$ " << gross_pay << endl;
    cout << "Gross pay per bi-monthly payckeck\t$ " << (gross_pay / 24) << endl;
    cout << "Gross pay per bi-weekly  payckeck\t$ " << (gross_pay / 26) << endl;
    cout << "\n---------------------------------------\n\n";

    return 0;
}
