using namespace std;

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <array>

#define print(x) cout << x << endl;

struct Number {
    int value;
    array<int, 2> indices;
};

int processFile(string filename);
int findSum(string beforeLine, string currentLine, string afterLine);
bool isSpecialCharacter(char c);
int findSumOfRatios(string beforeLine, string currentLine, string afterLine);
vector<Number> findNumbers(string line);
vector<Number> pruneRedundancy(vector<Number> numbers);


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
            printf("Read line: %s\n", line.c_str());
            lines.push_back(line);
        }
        file.close();
    }
    else cout << "Unable to open file";

    // for (int i = 0; i < lines.size(); i++) {
    //     printf("Processing line %d: ", i + 1);
    //     if (i == 0) {
    //         sum += findSum("", lines[i], lines[i + 1]);
    //     }
    //     else if (i == lines.size() - 1) {
    //         sum += findSum(lines[i - 1], lines[i], "");
    //     }
    //     else {
    //         sum += findSum(lines[i - 1], lines[i], lines[i + 1]);
    //     }
    // }

    for (int i = 0; i < lines.size(); i++) {
        printf("Processing line %d: ", i + 1);
        if (i == 0) {
            sum += findSumOfRatios("", lines[i], lines[i + 1]);
        }
        else if (i == lines.size() - 1) {
            sum += findSumOfRatios(lines[i - 1], lines[i], "");
        }
        else {
            sum += findSumOfRatios(lines[i - 1], lines[i], lines[i + 1]);
        }
    }
    return sum;
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
                    if (j == currentLine.length() - 1) {
                        endIndex = j + 1;
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

    finished = false;

    // Now that we have all numbers, we need to find the ones that are adjacent to special characters.

    for (int i = 0; i < numbers.size(); i++) {
        if (isSpecialCharacter(currentLine[indices[i][0] - 1]) && indices[i][0] > 0) {
            cout << "Found a special character to the left of " << numbers[i] << endl;
            sum += numbers[i];
            continue;
        }
        if (isSpecialCharacter(currentLine[indices[i][1]]) && indices[i][1] < currentLine.length() - 1) {
            cout << "SPECIAL CHARACTER: " << currentLine[indices[i][1]] << endl;
            cout << "Found a special character to the right of " << numbers[i] << endl;
            sum += numbers[i];
            continue;
        }

        if (beforeLine != "") {
            for (int j = indices[i][0]; j < indices[i][1]; j++) {
                if (isSpecialCharacter(beforeLine[j])) {
                    cout << "Found a special character above " << numbers[i] << endl;
                    sum += numbers[i];
                    finished = true;
                    break;
                }
            }
            if (finished) {finished = false; continue;}

            if (isSpecialCharacter(beforeLine[indices[i][0] - 1]) && indices[i][0] > 0) {
                cout << "Found a special character top left of " << numbers[i] << endl;
                sum += numbers[i];
                continue;
            }

            if (isSpecialCharacter(beforeLine[indices[i][1]]) && indices[i][1] < beforeLine.length() - 1) {
                cout << "Found a special character top right of " << numbers[i] << endl;
                sum += numbers[i];
                continue;
            }
        }
        if (afterLine != "") {
            finished = false;
            for (int k = indices[i][0]; k < indices[i][1]; k++) {
                if (isSpecialCharacter(afterLine[k])) {
                    cout << "Found a special character below " << numbers[i] << endl;
                    sum += numbers[i];
                    finished = true;
                    break;
                }
            }
            if (finished) {finished = false; continue;}

            if (isSpecialCharacter(afterLine[indices[i][0] - 1]) && indices[i][0] > 0) {
                cout << "Found a special character bottom left of " << numbers[i] << endl;
                sum += numbers[i];
                continue;
            }

            if (isSpecialCharacter(afterLine[indices[i][1]]) && indices[i][1] < afterLine.length() - 1) {
                cout << "Found a special character bottom right of " << numbers[i] << endl;
                sum += numbers[i];
                continue;
            }
        }
    }

    return sum;
}

int findSumOfRatios(string beforeLine, string currentLine, string afterLine) {
    int sum = 0;
    
    vector<Number> numbersBefore = findNumbers(beforeLine);\
    vector<Number> numbersCurrent = findNumbers(currentLine);
    vector<Number> numbersAfter = findNumbers(afterLine);

    for (int i = 0; i < currentLine.size(); i++) {
        if (currentLine[i] == '*') {
            // We need to see if there are exactly two numbers in the proximity.
            // If there are, we need to find the product of those numbers.

            int numberCount = 0;
            vector<Number> numbersFound;

            // Check numbers before:
            if (beforeLine != "") {
                if (i == 0) {
                    if (isdigit(beforeLine[i])) {
                        numberCount++;
                        // Find the number and add it to the vector.
                        for (const auto& number : numbersBefore) {
                            if (number.indices[0] <= i && number.indices[1] >= i) {
                                numbersFound.push_back(number);
                                break;
                            }
                        }
                    }
                } else if (i == currentLine.length() - 1) {
                    if (isdigit(afterLine[i])) {
                        numberCount++;
                        // Find the number and add it to the vector.
                        for (const auto& number : numbersAfter) {
                            if (number.indices[0] <= i && number.indices[1] >= i) {
                                numbersFound.push_back(number);
                                break;
                            }
                        }
                    }
                } else {
                    if (isdigit(beforeLine[i - 1])) {
                        numberCount++;
                        // Find the number and add it to the vector.
                        for (const auto& number : numbersBefore) {
                            if (number.indices[0] <= i - 1 && number.indices[1] >= i - 1) {
                                numbersFound.push_back(number);
                                break;
                            }
                        }
                    }
                    if (isdigit(beforeLine[i])) {
                        numberCount++;
                        // Find the number and add it to the vector.
                        for (const auto& number : numbersBefore) {
                            if (number.indices[0] <= i && number.indices[1] >= i) {
                                numbersFound.push_back(number);
                                break;
                            }
                        }
                    }
                    if (isdigit(beforeLine[i + 1])) {
                        numberCount++;
                        // Find the number and add it to the vector.
                        for (const auto& number : numbersBefore) {
                            if (number.indices[0] <= i + 1 && number.indices[1] >= i + 1) {
                                numbersFound.push_back(number);
                                break;
                            }
                        }
                    }
                }
            }
            

            // Now check same line

            if (isdigit(currentLine[i - 1])) {
                numberCount++;
                // Find the number and add it to the vector.
                for (const auto& number : numbersCurrent) {
                    if (number.indices[0] <= i - 1 && number.indices[1] >= i - 1) {
                        numbersFound.push_back(number);
                        break;
                    }
                }
            }
            if (isdigit(currentLine[i + 1])) {
                numberCount++;
                // Find the number and add it to the vector.
                for (const auto& number : numbersCurrent) {
                    if (number.indices[0] <= i + 1 && number.indices[1] >= i + 1) {
                        numbersFound.push_back(number);
                        break;
                    }
                }
            }

            // Now check numbers after:

            if (afterLine != "") {
                if (i == 0) {
                    if (isdigit(beforeLine[i])) {
                        numberCount++;
                        // Find the number and add it to the vector.
                        for (const auto& number : numbersBefore) {
                            if (number.indices[0] <= i && number.indices[1] >= i) {
                                numbersFound.push_back(number);
                                break;
                            }
                        }
                    }
                }else if (i == currentLine.length() - 1) {
                    if (isdigit(afterLine[i])) {
                        numberCount++;
                        // Find the number and add it to the vector.
                        for (const auto& number : numbersAfter) {
                            if (number.indices[0] <= i && number.indices[1] >= i) {
                                numbersFound.push_back(number);
                                break;
                            }
                        }
                    }
                } else {
                    if (isdigit(afterLine[i - 1])) {
                        numberCount++;
                        // Find the number and add it to the vector.
                        for (const auto& number : numbersAfter) {
                            if (number.indices[0] <= i - 1 && number.indices[1] >= i - 1) {
                                numbersFound.push_back(number);
                                break;
                            }
                        }
                    }
                    if (isdigit(afterLine[i])) {
                        numberCount++;
                        // Find the number and add it to the vector.
                        for (const auto& number : numbersAfter) {
                            if (number.indices[0] <= i && number.indices[1] >= i) {
                                numbersFound.push_back(number);
                                break;
                            }
                        }
                    }
                    if (isdigit(afterLine[i + 1])) {
                        numberCount++;
                        // Find the number and add it to the vector.
                        for (const auto& number : numbersAfter) {
                            if (number.indices[0] <= i + 1 && number.indices[1] >= i + 1) {
                                numbersFound.push_back(number);
                                break;
                            }
                        }
                    }
                }
            }

            // Now we need to prune redundancies from the set, due to double counting.
            numbersFound = pruneRedundancy(numbersFound);

            if (numbersFound.size() == 2) {
                sum += numbersFound[0].value * numbersFound[1].value;
            }
        }
    }

    return sum;
}

vector<Number> findNumbers(string line) {
    int startIndex = 0;
    int endIndex = line.length();

    vector<Number> numbers;

    bool finished = false;

    for (int i = 0; i < line.length(); i++) {
        if (isdigit(line[i])) {
            startIndex = i;
            if (!finished) {
                for (int j = i + 1; j < line.length(); j++) {
                    if (!isdigit(line[j])) {
                        endIndex = j;
                        numbers.push_back({stoi(line.substr(startIndex, endIndex - startIndex)), { startIndex, endIndex }});
                        finished = true;
                        i = j;
                        break;
                    }
                    if (j == line.length() - 1) {
                        endIndex = j + 1;
                        numbers.push_back({stoi(line.substr(startIndex, endIndex - startIndex)), { startIndex, endIndex }});
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

        cout << "[" << number.value << "] ";
    }
    cout << endl;

    return numbers;
}

vector<Number> pruneRedundancy(vector<Number> numbers) {
    vector<Number> prunedNumbers;

    for (int i = 0; i < numbers.size(); i++) {
        bool found = false;
        for (int j = 0; j < prunedNumbers.size(); j++) {
            if (numbers[i].value == prunedNumbers[j].value && numbers[i].indices[0] == prunedNumbers[j].indices[0] && numbers[i].indices[1] == prunedNumbers[j].indices[1]) {
                found = true;
                break;
            }
        }
        if (!found) {
            prunedNumbers.push_back(numbers[i]);
        }
    }

    return prunedNumbers;
}


int main() {
    // Tried 35868012, too low.
    
    cout << processFile("day3_input.txt") << endl;

    //cout << processFile("sample.txt") << endl;

    //cout << findSum("*.........", "..611..211", ".........*") << endl;
}