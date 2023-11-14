#include <iostream>
#include <string>

using namespace std;

// Function to derive the string using the palindrome CFG
void derivePalindrome(const string& str, int& index) {
    // Check if the string is empty or if the index exceeds the string length
    if (index >= str.length()) {
        return;
    }

    // Display the current production rule
    cout << "P → ";

    // Check the character at the current index
    if (str[index] == '0') {
        cout << "0";
        index++;
    } else if (str[index] == '1') {
        cout << "1";
        index++;
    } else {
        cout << "ε";  // epsilon (empty string)
    }

    // Recursively derive the remaining string
    derivePalindrome(str, index);

    // Display the reverse of the current production rule
    cout << " ← ";
    index--;

    // Check the character at the current index for the reverse production
    if (str[index] == '0') {
        cout << "0";
    } else if (str[index] == '1') {
        cout << "1";
    }
}

int main() {
    string inputString;

    // Get the input string from the user
    cout << "Enter a string: ";
    cin >> inputString;

    // Start the derivation from the beginning of the string
    int index = 0;

    // Display the initial production rule
    cout << "Derivation Steps:\n";
    cout << "P -> ε\n";

    // Derive the string using the palindrome CFG
    derivePalindrome(inputString, index);

    cout << endl;

    return 0;
}
