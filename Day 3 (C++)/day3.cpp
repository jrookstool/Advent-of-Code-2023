using namespace std;

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <array>

bool isSpecialCharacter(char c) {
    return (!isdigit(c)) && (c != '.');
}

int processFile(string filename) {
    string line;
    ifstream file(filename);

    vector<string> lines;

    int sum = 0;
    if (file.is_open()) {
        while (getline(file, line)) {
            lines.push_back(line);
        }
        file.close();
    }
    else cout << "Unable to open file";
    return 0;
}

int findSum(string beforeLine, string currentLine, string afterLine) {
    // First, locate the numbers, not just the digits, but the full numbers.
    // Then check to see which ones are adjacent, even diagonally, from a special character.
    // Then add them all up.

    // We find the numbers:
    int startIndex = 0;
    int endIndex = currentLine.length();

    vector<array<int, 2>> numbers;
    bool finished = false;

    for (int i = 0; i < currentLine.length(); i++) {
        if (!isSpecialCharacter(currentLine[i])) {
            startIndex = i;
            if (!finished) {
                for (int j = i + 1; j < currentLine.length(); j++) {
                    if (!isSpecialCharacter(currentLine[j])) {
                        endIndex = j;
                        numbers.push_back({ startIndex, endIndex });
                        finished = true;
                    }
                }
            }
            
        }
    }

    for (const auto& number : numbers) {
        cout << "[" << number[0] << ", " << number[1] << "] ";
    }
    cout << endl;

    return 0;
}


int main() {
    string line;
    ifstream myfile("day3_input.txt");

    cout << isSpecialCharacter('4') << endl;

    cout << findSum("", ".....487.599...........411...........................................574..679.136..........................30......255.......432............", "") << endl;
}