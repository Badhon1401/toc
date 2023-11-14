#include <iostream>
#include <string>

using namespace std;

// Function to check if a string is in the language L = {0^n1^n | n >= 0}
bool isInLanguage(const string& str) {
    int countZeros = 0;
    int countOnes = 0;

    // Count the number of zeros and ones
    for (char ch : str) {
        if (ch == '0') {
            countZeros++;
        } else if (ch == '1') {
            countOnes++;
        } else {
            // If there are other characters, the string is not in the language
            return false;
        }
    }

    // Check if the string is of the form 0^n1^n
    return countZeros == countOnes;
}

// Function to demonstrate the Pumping Lemma
bool applyPumpingLemma() {
    // Choose a string from the language (non-regular)
    string str = "0^p1^p"; // p is the pumping length

    // Check if the chosen string is in the language
    if (!isInLanguage(str)) {
        cout << "The chosen string is not in the language.\n";
        return false;
    }

    // Split the string into three parts: xyz
    string x = str.substr(0, 2);  // "0^p"
    string y = str.substr(2, 1);  // "1"
    string z = str.substr(3);     // "1^p"

    // Choose an integer i (pumping length) and generate a new string s = xy^iz
    int i = 2;  // Choose i = 2 for simplicity
    string newStr = x + string(i, y[0]) + z;

    // Check if the new string is still in the language
    if (isInLanguage(newStr)) {
        cout << "The string after pumping is still in the language.\n";
        return true;  // This violates the Pumping Lemma
    } else {
        cout << "The string after pumping is not in the language.\n";
        return false;  // This supports the Pumping Lemma
    }
}

int main() {
    // Apply the Pumping Lemma to the language L = {0^n1^n | n >= 0}
    bool result = applyPumpingLemma();

    // Output the result
    if (result) {
        cout << "The language is not regular (according to the Pumping Lemma).\n";
    } else {
        cout << "The language may be regular.\n";
    }

    return 0;
}
