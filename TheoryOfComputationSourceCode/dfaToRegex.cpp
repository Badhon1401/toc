#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Function to generate regular expressions for each pair of states for each input symbol
void generateRegularExpressions(const vector<vector<string>>& transitionTable) {
    int numStates = transitionTable.size();

    // Initialize the regular expressions matrix
    vector<vector<vector<string>>> regex(numStates, vector<vector<string>>(numStates, vector<string>(2, "")));

    // Initialize with direct transitions from the transition table
    for (int i = 0; i < numStates; ++i) {
        for (int j = 0; j < numStates; ++j) {
            regex[i][j][0] = transitionTable[i][0];
            regex[i][j][1] = transitionTable[i][1];
        }
    }

    // Apply the Floyd-Warshall algorithm to generate regular expressions
    for (int k = 0; k < numStates; ++k) {
        for (int i = 0; i < numStates; ++i) {
            for (int j = 0; j < numStates; ++j) {
                for (int s = 0; s < 2; ++s) {
                    string expr = "";

                    // If there's a direct transition from i to k and k to j, or
                    // if there's a transition from i to k and k to j with k being a final state
                    if ((regex[i][k][s] != "") && (regex[k][j][s] != "")) {
                        expr += regex[i][k][s];
                        if (expr != "ε") {
                            expr += "+";
                        }
                        expr += "(" + regex[k][j][s] + ")";
                    }

                    // If there's a direct transition from i to j, or
                    // if there's a transition from i to k and k to j with k being a final state
                    if (regex[i][j][s] != "") {
                        if (expr != "") {
                            expr += "+";
                        }
                        expr += regex[i][j][s];
                    }

                    regex[i][j][s] = expr;
                }
            }
        }
    }

    // Print the regular expressions
    for (int i = 0; i < numStates; ++i) {
        for (int j = 0; j < numStates; ++j) {
            cout << "R" << i + 1 << j + 1 << "(0): " << regex[i][j][0] << endl;
            cout << "R" << i + 1 << j + 1 << "(1): " << regex[i][j][1] << endl;
            cout << "R" << i + 1 << j + 1 << "(2): " << regex[i][j][2] << endl;
            cout << "----------" << endl;
        }
    }
}

int main() {
    // Define the DFA transition table
    vector<vector<string>> transitionTable = {{"q1", "q2"}, {"q2", "q3"}, {"q3", "q3"}};

    // Generate and print regular expressions
    generateRegularExpressions(transitionTable);

    return 0;
}
