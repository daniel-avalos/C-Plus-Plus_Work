// Daniel Avalos, 2018
// Lab 2, WIP
// Traduct Order quantity to pre-tax total, using const software price and discount table


#include <iostream>
#include <cctype>
using namespace std;

int main() {

    // Splash Block
    cout << "\n\n"
            "Lab 2: Order Price Management\n"
            "   Calculating the pre-tax total for software package purchasing\n"
            "   based on discount table\n"
            "---------------------------------------\n\n";

    int orderq;             // Order quantity
    float disc_rate;        // Multiplier, used on order total (20% disc = 0.8)
    float total_pretax;     // Total based on purchase q and discount rate
    const float SOFTW_COST = 199.00;

    cout << "How many units are being purchased?" << endl;
    cin >> orderq;

    // Discount Rate Logic Gate
    if (orderq >= 100) {      // 50%
        disc_rate = 0.5;
    }
    else if (orderq >= 50) {  // 40%
        disc_rate = 0.6;
    }
    else if (orderq >= 20) {  // 30%
        disc_rate = 0.7;
    }
    else if (orderq >= 10) {  // 20%
        disc_rate = 0.8;
    }
    else {                      //  0%
        disc_rate = 1;
    }

    total_pretax = orderq * (SOFTW_COST * disc_rate);
    // cout << orderq << " " << disc_rate << " " << (SOFTW_COST * disc_rate);
    cout << "\nTotal purchase cost: $" << total_pretax << endl;

    return 0;
}


// ($199 each)
// Quantity    Discount
// 10-19       20%
// 20-49       30%
// 50-99       40%
// 100+        50%