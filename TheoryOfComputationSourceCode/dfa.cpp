#include <iostream>
#include <vector>

using namespace std;

// Function to simulate the DFA
int runDFA(const vector<vector<int>>& transitions, const vector<int>& finalStates, int initialState, const string& input) {
    int currentState = initialState;

    // Loop through the input string
    for (char symbol : input) {
        int symbolInt = symbol - '0';

        // Check if the symbol is valid
        if (symbolInt < 0 || symbolInt >= transitions[currentState].size()) {
            // Invalid symbol
            return -1;
        }

        // Update the current state using the transition table
        currentState = transitions[currentState][symbolInt];
    }

    // Check if the final state is one of the accepting states
    for (int finalState : finalStates) {
        if (currentState == finalState) {
            return currentState; // Input string is accepted
        }
    }

    return -1; // Input string is rejected
}

int main() {
    int numStates, numSymbols, initialState, numFinalStates;

    // Get the number of states, symbols, and final states from the user
    cout << "Enter the number of states: ";
    cin >> numStates;

    cout << "Enter the number of symbols: ";
    cin >> numSymbols;

    cout << "Enter the initial state: ";
    cin >> initialState;

    cout << "Enter the number of final states: ";
    cin >> numFinalStates;

    vector<int> finalStates(numFinalStates);
    cout << "Enter the final states: ";
    for (int i = 0; i < numFinalStates; i++) {
        cin >> finalStates[i];
    }

    // Create the transition table
    vector<vector<int>> transitions(numStates, vector<int>(numSymbols));
    cout << "Enter the transition table:" << endl;
    for (int i = 0; i < numStates; i++) {
        for (int j = 0; j < numSymbols; j++) {
            cout << "Transition from state " << i << " on symbol " << j << ": ";
            cin >> transitions[i][j];
        }
    }

    string input;

    // Get input from the user
    cout << "Enter a string (symbols separated by no space): ";
    cin >> input;

    // Run the DFA
    int result = runDFA(transitions, finalStates, initialState, input);

    // Display the result
    if (result != -1) {
        cout << "Accepted. Reached state: " << result << endl;
    } else {
        cout << "Rejected" << endl;
    }

    return 0;
}