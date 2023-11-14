#include <iostream>
#include <vector>
#include <set>

using namespace std;

// Function to simulate the NFA
bool runNFA(const vector<set<int>>& transitions, const set<int>& finalStates, int initialState, const string& input) {
    set<int> currentStates = { initialState };

    // Loop through the input string
    for (char symbol : input) {
        set<int> nextStates;

        // Find the next states based on the current states and input symbol
        for (int currentState : currentStates) {
            if (transitions[currentState].count(symbol - '0') > 0) {
                // Add the states reachable from the current state on the input symbol
                nextStates.insert(transitions[currentState].begin(), transitions[currentState].end());
            }
        }

        // Update the set of current states
        currentStates = nextStates;
    }

    // Check if there is any final state in the set of current states
    for (int currentState : currentStates) {
        if (finalStates.count(currentState) > 0) {
            return true; // Input string is accepted
        }
    }

    return false; // Input string is rejected
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

    set<int> finalStates;
    cout << "Enter the final states: ";
    for (int i = 0; i < numFinalStates; i++) {
        int state;
        cin >> state;
        finalStates.insert(state);
    }

    // Create the transition table
    vector<set<int>> transitions(numStates);
    cout << "Enter the transition table:" << endl;
    for (int i = 0; i < numStates; i++) {
        for (int j = 0; j < numSymbols; j++) {
            cout << "Transition from state " << i << " on symbol " << j << " (comma-separated list of states, -1 for empty set): ";
            string input;
            cin >> input;

            // Parse the input string and update the transition table
            if (input != "-1") {
                size_t pos = 0;
                while ((pos = input.find(',')) != string::npos) {
                    int state = stoi(input.substr(0, pos));
                    transitions[i].insert(state);
                    input.erase(0, pos + 1);
                }
                int state = stoi(input);
                transitions[i].insert(state);
            }
        }
    }

    string input;

    // Get input from the user
    cout << "Enter a string (symbols separated by no space): ";
    cin >> input;

    // Run the NFA
    bool result = runNFA(transitions, finalStates, initialState, input);

    // Display the result
    if (result) {
        cout << "Accepted\n";
    } else {
        cout << "Rejected\n";
    }

    return 0;
}