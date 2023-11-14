#include <iostream>
#include <vector>
#include <set>
#include <queue>
#include <map>

using namespace std;

// Function to convert NFA to DFA
map<set<int>, map<char, set<int>>> convertNFAToDFA(const vector<set<int>>& nfaTransitions, const set<int>& nfaFinalStates) {
    map<set<int>, map<char, set<int>>> dfaTransitions;
    map<set<int>, int> stateMapping;

    // Initialize the queue for BFS
    queue<set<int>> bfsQueue;

    // Create the epsilon closure of the initial state
    set<int> initialState = {0};
    for (int state : initialState) {
        initialState.insert(nfaTransitions[state].begin(), nfaTransitions[state].end());
    }

    // Add the initial state to the DFA and the queue
    dfaTransitions[initialState] = {};
    stateMapping[initialState] = 0;
    bfsQueue.push(initialState);

    // Perform BFS to construct the DFA states
    while (!bfsQueue.empty()) {
        set<int> currentDFAState = bfsQueue.front();
        bfsQueue.pop();

        // Process transitions on each symbol
        for (char symbol : {'0', '1'}) {
            set<int> nextState;

            // Collect NFA states reachable on the current symbol
            for (int nfaState : currentDFAState) {
                if (nfaTransitions[nfaState].count(symbol - '0') > 0) {
                    nextState.insert(nfaTransitions[nfaState].begin(), nfaTransitions[nfaState].end());
                }
            }

            // Calculate the epsilon closure of the collected NFA states
            set<int> epsilonClosure;
            for (int state : nextState) {
                epsilonClosure.insert(nfaTransitions[state].begin(), nfaTransitions[state].end());
            }

            // Check if the state is already in the DFA
            if (stateMapping.find(epsilonClosure) == stateMapping.end()) {
                dfaTransitions[epsilonClosure] = {};
                stateMapping[epsilonClosure] = stateMapping.size();
                bfsQueue.push(epsilonClosure);
            }

            // Add transition to the DFA
            dfaTransitions[currentDFAState][symbol] = epsilonClosure;
        }
    }

    return dfaTransitions;
}

int main() {
    int numNFAStates, numSymbols, numNFAFinalStates;

    // Get the number of NFA states, symbols, and final states from the user
    cout << "Enter the number of NFA states: ";
    cin >> numNFAStates;

    cout << "Enter the number of symbols: ";
    cin >> numSymbols;

    cout << "Enter the number of NFA final states: ";
    cin >> numNFAFinalStates;

    set<int> nfaFinalStates;
    cout << "Enter the NFA final states: ";
    for (int i = 0; i < numNFAFinalStates; i++) {
        int state;
        cin >> state;
        nfaFinalStates.insert(state);
    }

    // Create the NFA transition table
    vector<set<int>> nfaTransitions(numNFAStates);
    cout << "Enter the NFA transition table (for epsilon transitions, enter -1):" << endl;
    for (int i = 0; i < numNFAStates; i++) {
        for (int j = 0; j < numSymbols; j++) {
            cout << "Transition from NFA state " << i << " on symbol " << j << " (comma-separated list of states, -1 for epsilon): ";
            string input;
            cin >> input;

            // Parse the input string and update the NFA transition table
            if (input != "-1") {
                size_t pos = 0;
                while ((pos = input.find(',')) != string::npos) {
                    int state = stoi(input.substr(0, pos));
                    nfaTransitions[i].insert(state);
                    input.erase(0, pos + 1);
                }
                int state = stoi(input);
                nfaTransitions[i].insert(state);
            }
        }
    }

    // Convert NFA to DFA
    map<set<int>, map<char, set<int>>> dfaTransitions = convertNFAToDFA(nfaTransitions, nfaFinalStates);

    // Display the DFA transition table
    cout << "\nDFA Transition Table:" << endl;
    for (const auto& [currentState, transitions] : dfaTransitions) {
        cout << "DFA state " << stateMapping[currentState] << ": ";
        for (const auto& [symbol, nextState] : transitions) {
            cout << "On symbol " << symbol << " goes to DFA state " << stateMapping[nextState] << "; ";
        }
        cout << endl;
    }

    return 0;
}
