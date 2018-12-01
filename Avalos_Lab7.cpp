/* Daniel Avalos
 * Lab 7 - Pointers and Dynamic Memory Allocation
 * Create an array of x length, dynamically assigned based on user input
 * Sort, find average, and destroy dynamically allocated memory
 */

#include <iostream>
#include <array>        // C++11 Array type inclusion
#include <sstream>      // C++11 ::stringstream inclusion
using namespace std;

// Survey Class
// Integer storage and sorter
class Survey{
private:
    int *surveyedCount = 0,
        *memAddr = new int,
        *results;
    float currentAvg = 0;

    // Initializes all result entries
    void initResults() {
        for (int i = 0; i<*surveyedCount; i++)
            { results[i] = -1; }
    }
    // input validation
    int *validate(int &toValidate) {
        if (toValidate < 0) {
            toValidate = 0;
        }
        return &toValidate;
    }

public:
    // Default constructor
    explicit Survey(int *surveyCount) {
        surveyedCount = validate(*surveyCount);
        results = new int[*surveyedCount];  // build dyn arr
        initResults();                      // init all to -1
        memAddr = getResultsMemAddr();      // prepare internal array pointer
    }
    // Add value using pointer
    void addEntry(int &ndxPnt, const int *entry) {
        ndxPnt = *entry;
        // setAvg();
    }
    // Update current average
    void setAvg() {
        int ndx;
        float sum = 0.0;
        for (ndx = 0; ndx<*surveyedCount; ndx++) {
            if (*(memAddr+ndx) >= 0) {
                sum += *(memAddr+ndx);
            }
        }
        currentAvg = (sum / *surveyedCount);
    }
    // Return arr ptr
    int *getResultsMemAddr() {
        return results;
    }
    void sortResults() {
        int arrSeek,        // Seek through array
            minNdx,         // ndx of min value. Check if any subsequent entries are lesser
            hold;           // acts as KingCell when swapping values
        for (arrSeek=0; arrSeek<*(surveyedCount)-1; arrSeek++) {
            minNdx = arrSeek;
            // Seek from arrSeek+1 to endOfArr, identify lesser val and store its ndx
            for (int minSeek=arrSeek+1; minSeek<*surveyedCount; minSeek++) {
                if (*(memAddr+minSeek) < *(memAddr+arrSeek)) {
                    minNdx = minSeek;
                }
            }
            // If a lesser value was found, swap with arrSeek'd val
            if (minNdx != arrSeek) {
                hold = *(memAddr+arrSeek);
                *(memAddr+arrSeek) = *(memAddr+minNdx);
                *(memAddr+minNdx) = hold;
            }
        }
    }
    // Return average
    float getAvg() {
        return currentAvg;
    }
};

// Used to build appropriate tables
class Tabler {
private:
    const int *targetArrMem,
              *targetArrLen;

    string title = "Number of Movies Watched";
    string tableHeader() {
        stringstream buffer;
        buffer << "\n" << title;
        return buffer.str();
    }
    string tableBreak() {
        stringstream buffer;
        buffer << "\n" << string(title.length(), '-');
        return buffer.str();
    }
    string tableBody() {
        stringstream buffer;
        for (int ndx=0; ndx<*targetArrLen; ndx++) {
            if (*(targetArrMem+ndx) != -1) {
                buffer << "\n" << *(targetArrMem + ndx);
            }
        }
        return buffer.str();
    }
public:
    Tabler(const int *arrMem, const int *arrLen) {
        targetArrMem = arrMem;
        targetArrLen = arrLen;
    }
    void tPrint() {
        stringstream buffer;
        cout << tableHeader()
             << tableBreak()
             << tableBody()
             << tableBreak()
             << "\n";
    }
};

int main() {
    auto *studentsSurveyed = new int;
    int *surveyPtr = nullptr,
        *movies = new int;

    // Gather number of students surveyed
    cout << "How many students were queried? ";
    cin >> *studentsSurveyed;

    // Build Survey object, assign pointer
    Survey monthlyCinema(studentsSurveyed);
    surveyPtr = monthlyCinema.getResultsMemAddr();

    // Enter values by passing pointer
    cout << "\n" << "Enter movies watched for each student (-1 to stop)"
         << "\n";
    for (int ndx=0; ndx<*studentsSurveyed; ndx++) {
        cout << "Student " << ndx+1 << " : ";
        cin >> *movies;
        if (*movies == -1) {
            break;
        }
        monthlyCinema.addEntry(*(surveyPtr+ndx), movies);
    }
    monthlyCinema.sortResults();
    monthlyCinema.setAvg();

    Tabler monthlyCinemaTable(surveyPtr, studentsSurveyed);
    monthlyCinemaTable.tPrint();
    cout << "Average : " << monthlyCinema.getAvg();

    // Cleanup
    delete studentsSurveyed;
    delete[] surveyPtr;
    delete surveyPtr;
    return 0;
}
