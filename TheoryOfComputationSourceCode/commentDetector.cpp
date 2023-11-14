#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

// Function to count lines with single-line comments, multiline comments, and full comments
void countComments(const string& filename) {
    ifstream file(filename);
    string line;
    int lineNumber = 0;
    vector<int> singleLineCommentLines, multiLineCommentLines, fullCommentLines;
    bool inMultiLineComment = false;

    while (getline(file, line)) {
        lineNumber++;
        size_t singleLineCommentPos = line.find("//");
        size_t multiLineCommentStartPos = line.find("/*");
        size_t multiLineCommentEndPos = line.find("*/");

        if (singleLineCommentPos != string::npos) {
            // Single-line comment found
            singleLineCommentLines.push_back(lineNumber);
        }

        if (multiLineCommentStartPos != string::npos) {
            // Start of multiline comment found
            multiLineCommentLines.push_back(lineNumber);
            inMultiLineComment = true;
        }

        if (inMultiLineComment) {
            multiLineCommentLines.push_back(lineNumber);
        }

        if (multiLineCommentEndPos != string::npos) {
            // End of multiline comment found
            inMultiLineComment = false;
        }

        // Check if the line is a full comment
        if (singleLineCommentPos == string::npos && multiLineCommentStartPos == string::npos && multiLineCommentEndPos == string::npos) {
            fullCommentLines.push_back(lineNumber);
        }
    }

    cout << "Single-line comments found on lines: ";
    for (int lineNum : singleLineCommentLines) {
        cout << lineNum << " ";
    }
    cout << endl;

    cout << "Multiline comments found on lines: ";
    for (int lineNum : multiLineCommentLines) {
        cout << lineNum << " ";
    }
    cout << endl;

    cout << "Full comments found on lines: ";
    for (int lineNum : fullCommentLines) {
        cout << lineNum << " ";
    }
    cout << endl;
}

int main() {
    string filename;

    // Get the filename from the user
    cout << "Enter the name of the C program file (including extension): ";
    cin >> filename;

    // Count comments in the C program
    countComments(filename);

    return 0;
}
