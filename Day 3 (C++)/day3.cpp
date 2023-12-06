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

    int sum = 0;

    vector<array<int, 2>> indices;
    vector<int> numbers;
    bool finished = false;

    for (int i = 0; i < currentLine.length(); i++) {
        if (isdigit(currentLine[i])) {
            startIndex = i;
            if (!finished) {
                for (int j = i + 1; j < currentLine.length(); j++) {
                    if (!isdigit(currentLine[j])) {
                        endIndex = j;
                        indices.push_back({ startIndex, endIndex });
                        numbers.push_back(stoi(currentLine.substr(startIndex, endIndex - startIndex)));
                        finished = true;
                        i = j;
                        break;
                    }
                }
            }
            finished = false;
        }
    }

    for (const auto& number : numbers) {
        cout << "[" << number << "] ";
    }
    cout << endl;

    // Now that we have all numbers, we need to find the ones that are adjacent to special characters.

    for (int i = 0; i < numbers.size(); i++) {
        if (isSpecialCharacter(currentLine[indices[i][0] - 1])) {
            cout << "Found a special character to the left of " << numbers[i] << endl;
            sum += numbers[i];
            continue;
        }
        if (isSpecialCharacter(currentLine[indices[i][1]])) {
            cout << "Found a special character to the right of " << numbers[i] << endl;
            sum += numbers[i];
            continue;
        }

        if (beforeLine != "") {
            for (int j = indices[i][0]; j < indices[i][1]; j++) {
                if (isSpecialCharacter(beforeLine[j])) {
                    cout << "Found a special character above " << numbers[i] << endl;
                    sum += numbers[i];
                    break;
                }
            }
            continue;

            if (isSpecialCharacter(beforeLine[indices[i][0] - 1])) {
                cout << "Found a special character top left of " << numbers[i] << endl;
                sum += numbers[i];
                continue;
            }

            if (isSpecialCharacter(beforeLine[indices[i][1]])) {
                cout << "Found a special character top right of " << numbers[i] << endl;
                sum += numbers[i];
                continue;
            }
        }
        if (afterLine != "") {
            for (int j = indices[i][0]; j < indices[i][1]; j++) {
                if (isSpecialCharacter(afterLine[j])) {
                    cout << "Found a special character below " << numbers[i] << endl;
                    sum += numbers[i];
                }
                break;
            }
            continue;

            if (isSpecialCharacter(afterLine[indices[i][0] - 1])) {
                cout << "Found a special character bottom left of " << numbers[i] << endl;
                sum += numbers[i];
                continue;
            }

            if (isSpecialCharacter(afterLine[indices[i][1]])) {
                cout << "Found a special character bottom right of " << numbers[i] << endl;
                sum += numbers[i];
                continue;
            }
            if (isSpecialCharacter(beforeLine[indices[i][0]])) {
                cout << "Found a special character above " << numbers[i] << endl;
                sum += numbers[i];
                continue;
            }
            if (isSpecialCharacter(beforeLine[indices[i][1]])) {
                cout << "Found a special character above " << numbers[i] << endl;
                sum += numbers[i];
            }
        }
    }

    return sum;
}


int main() {
    string line;
    ifstream myfile("day3_input.txt");

    //cout << findSum("", ".....487.599...........411...........................................574..679.136..........................30......255.......432............", "") << endl;
    cout << findSum("....*......*............*..........&586..........................375...@..*....../.....835.............610*........./...............582.....",
                    "...833........304...&.862...............203..........922.125...............819.............@....563.....................722..775............",
                    "..............+...994..........#.........*..244.457.....*...........867.........829.....469.....#...........................*...............") << endl;
}