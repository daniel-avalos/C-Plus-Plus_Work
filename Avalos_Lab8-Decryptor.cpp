/*
 * Given an encrypted file, decrypt and write to decrypted.txt
 * */
#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

string decrypt(const string &);
void showState(fstream &);

// Convert string line to character array, decrypt each character
string decrypt(const string &str) {
    long word_len = str.length();
    char charr[word_len];
    strcpy(charr, str.c_str());
    for (int i = 0; i<word_len; i++) {
        charr[i] = charr[i] - 2;
    }
    return charr;
}

// Display fstream's bit statuses
void showState(fstream &file) {
    cout << "\n";
    if (file.eof())
        { cout << " eof bit  : " << file.eof() << "\n"; }
    if (file.fail())
        { cout << " fail bit : " << file.fail() << "\n"; }
    if (file.bad())
        { cout << " bad bit  : " << file.bad() << "\n"; }
    if (file.good())
        { cout << " good bit : " << file.good() << "\n"; }
}

int main() {
    string filename;
    fstream inFile, outFile;

    // Get filename
    cout << "Enter file name : ";
    cin >> filename;

    // Attempt to open infile
    inFile.open(filename);
    cout << "InFile Status: ";
    showState(inFile);
    if (!inFile) {
        cout << " Error : Unable to locate input file" << "\n";
        return 1;
    }
    cout << "\n\n";

    // Attempt to create outfile
    outFile.open("decrypted.txt",ios::app);
    cout << "OutFile Status: ";
    showState(outFile);
    if (!outFile) {
        cout << " Error : Unable to create output file" << "\n";
        return 1;
    }
    cout << "\n";

    // Scan for each line, send to necessary crypto function
    while (!inFile.eof()) {
        string gline;
        if (getline(inFile, gline)) {

            cout << "Read Status : ";
            showState(inFile);

            outFile << decrypt(gline) << endl;

            cout << "write Status: ";
            showState(inFile);

            cout << "\n";
        }
    }


    // Getline sets both eof AND failbit once end is reached
    cout << "InFile Final Status";
    showState(inFile);
    inFile.close();

    cout << "OutFile Final Status";
    showState(outFile);
    outFile.close();
    return 0;
}