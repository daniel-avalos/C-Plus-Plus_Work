// Daniel Avalos, 2018
// Lab 5 - Classes, Completed
// Given monthly water consumptions, displays table, min, max, avg, total //

#include <iostream> // std::cout, std::cin, std::string, std::right
#include <limits>   // limits::numeric_limits
using namespace std;

// # Protos
void getData(long long int (&h2oIn)[12]);
void printHeaders();
void printAmounts(const long long int (&h2oIn)[12]);
void lowestAmount(const long long int (&h2oIn)[12]);
void highestAmount(const long long int (&h2oIn)[12]);
void totalConsumption(const long long int (&h2oIn)[12]);

// External Scoped array of months in year, accessed by above protos
extern const string monthsInYear[12] = {"January", "February", "March",
                                        "April", "May", "June",
                                        "July", "August", "September",
                                        "October","November", "December"};

// 1: Get data from user
void getData(long long int (&h2oIn)[12]){
    long long int ccfToUse;  // ccf water usage. Will only assign to month's value if > 0

    for (int x=0; x<12; x++) {
        cout << "Enter water consumption in CCF for " << monthsInYear[x] << " ";

        do {
            cin >> ccfToUse;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                ccfToUse  = -1;
            }
        } while (ccfToUse < 0);

        h2oIn[x] = ccfToUse;
    }
}

// 2: Print headers, with year validation
void printHeaders() {
    int year;

    cout << "Enter the year (2005-2020)";

    do {
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            year = 0;
        }
        cin >> year;
    } while (year < 2005 || 2020 < year);

    cout << "\n                  " << year << " Consumption Report for Paris, Texas"
         << "\n"
         << "\nMonth     Consumption in CCF"
         << "\n----------------------------" << "\n";

}

// 3: Print all amounts
void printAmounts(const long long int (&h2oIn)[12]) {
    for (int ndx=0; ndx<12; ndx++) {
        cout.width(10); cout << left << monthsInYear[ndx];
        cout.width(12); cout << left << h2oIn[ndx] << "\n";
    }
    cout << "\n";
}

// 4: Display lowest consumption amount
void lowestAmount(const long long int (&h2oIn)[12]) {
    long long int lowestVal = 9223372036854775807;  // maximum LLI value
    int lowestNdx = 0;                              // used to pull parallel month

    for (int ndx=0; ndx<12; ndx++) {
        if (h2oIn[ndx] < lowestVal) {
            lowestVal = h2oIn[ndx];
            lowestNdx = ndx;
        }
    }
    cout << "The lowest consumption was in " << monthsInYear[lowestNdx]
         << " with " << lowestVal << " CCF\n";
}

// 5: Display highest consumption
void highestAmount(const long long int (&h2oIn)[12]) {
    long long int highestVal = 0;   // Baseline
    int highestNdx = 0;             // used to pull parallel month

    for (int ndx=0; ndx<12; ndx++) {
        if (h2oIn[ndx] > highestVal) {
            highestVal = h2oIn[ndx];
            highestNdx = ndx;
        }
    }
    cout << "The highest consumption was in " << monthsInYear[highestNdx]
         << " with " << highestVal << " CCF\n";
}

// 6: Total and avg consumption
void totalConsumption(const long long int (&h2oIn)[12]) {
    long long int totalVal = 0;  // maximum lli value,

    for (long long int x: h2oIn) {
        totalVal += x;
    }
    cout << "The total consumption for the year: " << totalVal << " CCF\n";
    cout << "The average consumption for the year: " << totalVal/12 << " CCF\n";
}


int main() {

    // Store monthly water consumption rates
    long long int h2oConsumption[12] = {0, 0, 0,
                                        0, 0, 0,
                                        0, 0, 0,
                                        0, 0, 0};

    getData(h2oConsumption);
    printHeaders();
    printAmounts(h2oConsumption);
    lowestAmount(h2oConsumption);
    highestAmount(h2oConsumption);
    totalConsumption(h2oConsumption);

    cout << endl;
    return 0;
}
