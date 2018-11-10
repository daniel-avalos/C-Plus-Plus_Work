// Daniel Avalos, Oct 2018
// Lab 3 complete
// Gather sales figures for 4 districts (w/ input validation)
// Determine highest grossing division

#include <iostream>     // i/o declarations
#include <string>       // String usage

using namespace std;

// Protos
int getSales(const string &);
void findHighest(float, float, float, float);

int main() {

    // Constant numeric literals
    const float neSales = getSales("Northeast");
    const float seSales = getSales("Southeast");
    const float nwSales = getSales("Northwest");
    const float swSales = getSales("Southwest");

    // Run bracket tourney to determine highest selling division
    findHighest(neSales, seSales, nwSales, swSales);

    return 0;
}


// Stdin sales gathering, with input validation
// (No negative sales values accepted)
int getSales(const string &division){
    int val;

    cout << "Enter the quarterly sales for the " <<
            division << " division: ";
    cin >> val;

    if (val < 0) {
        cout << "Sales figures cannot be negative. Please re-enter.\n";
    }
    while (val < 0) {
        cin >> val;
    }

    return val;
}


//            Tourney Bracket
//  East           Final           West
// ─{ne}─┐                       ┌─{nw}─
//       ├─{WinnerE}─┬─{WinnerW}─┤
// ─{se}─┘           │           └─{sW}─
//                   │
//      "The {x} division had the.."
void findHighest(float ne, float se, float nw, float sw) {

    // String and float vars for bracket winners
    string sWinnerE, sWinnerW;  // Division's name
    float fWinnerE, fWinnerW;   // Division's sales

    // East Bracket
    if (ne > se) {
        sWinnerE = "Northeast";
        fWinnerE = ne;
    }
    else {
        sWinnerE = "Southeast";
        fWinnerE = se;
    }

    // West Bracket
    if (ne > se) {
        sWinnerW = "Northwest";
        fWinnerW = nw;
    }
    else {
        sWinnerW = "Southwest";
        fWinnerW = sw;
    }

    // Final Bracket
    cout.precision(2);
    if (fWinnerE > fWinnerW) {
        cout << "\nThe " << sWinnerE <<
                " division had the highest sales this quarter.\n" <<
                "Their sales were $" << fixed << fWinnerE << endl;
    }
    else {
        cout << "The " << sWinnerW <<
             " division had the highest sales this quarter.\n" <<
             "Their sales were $" << fixed << fWinnerW << endl;
    }
}
