#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define MAX_LENGTH 256

int validateLine(char *line, int counts[]);
int validateClause(char *clause, int counts[]);
int findMinColor(char *line);

int verifyGames(char *filename, int counts[]) {
    FILE *file = fopen(filename, "r");

    if (file == NULL) {
        perror("fopen\n");
        exit(1);
    }

    char line[MAX_LENGTH];
    int sum = 0;

    while (fgets(line, 256, file) != NULL) {
        int gameID = 0;
        sscanf(line, "Game %d:", &gameID);
        printf("Game %d\n", gameID);
        if (validateLine(line, counts)) {
            printf("Game %d is valid\n", gameID);
            sum += gameID;
        }
    }

    fclose(file);

    return sum;
}

int findTotalPower(char *filename, int counts[]) {
    FILE *file = fopen(filename, "r");

    if (file == NULL) {
        perror("fopen\n");
        exit(1);
    }

    char line[MAX_LENGTH];
    int power = 0;

    while (fgets(line, 256, file) != NULL) {
        power += findMinColor(line);
    }

    fclose(file);

    return power;
}

int validateLine(char *line, int counts[]) {
    line = strchr(line, ':');
    line++;

    while (*line == ' ') line++;

    char *saveptr;

    char *tuples = strtok_s(line, ";", &saveptr);
    assert(tuples != NULL);
    while (tuples != NULL) {
        printf("tuple: %s\n", tuples);
        if (!validateClause(tuples, counts)) {
            return 0;
        }
        tuples = strtok_s(NULL, ";", &saveptr);
    }
    
    return 1;
}

int findMinColor(char *line) {
    line = strchr(line, ':');
    line++;

    while (*line == ' ') line++;

    int maxRed = 0;
    int maxGreen = 0;
    int maxBlue = 0;

    char *saveptr;
    char *tuples = strtok_s(line, ";", &saveptr);
    assert(tuples != NULL);
    while (tuples != NULL) {
        char *saveptr2;
        char *values = strtok_s(tuples, ",", &saveptr2);
        assert(values != NULL);
        while (values != NULL) {
            int number = 0;
            char color[6];
            sscanf(values, "%d %s", &number, color);
            if (strcmp(color, "red") == 0) {
                if (maxRed == 0 || number > maxRed) {
                    maxRed = number;
                }
            } else if (strcmp(color, "green") == 0) {
                if (maxGreen == 0 || number > maxGreen) {
                    maxGreen = number;
                }
            } else if (strcmp(color, "blue") == 0){
                if (maxBlue == 0 || number > maxBlue) {
                    maxBlue = number;
                }
            }
            values = strtok_s(NULL, ",", &saveptr2);
        }
        tuples = strtok_s(NULL, ";", &saveptr);
    }

    printf("line is: %s\n", line);
    printf("minRed: %d\nminGreen: %d\nminBlue: %d\n", maxRed, maxGreen, maxBlue);

    return maxRed * maxGreen * maxBlue;
}

int validateClause(char *clause, int counts[]) {
    char *saveptr;
    char *values = strtok_s(clause, ",", &saveptr);
    while (values != NULL) {
        int number = 0;
        char color[6];
        sscanf(values, "%d %s", &number, color);
        printf("%d of %s\n", number, color);
        if (strcmp(color, "red") == 0) {
            if (number > counts[0]) {
                return 0;
            }
        } else if (strcmp(color, "green") == 0) {
            if (number > counts[1]) {
                return 0;
            } 
        } else if (strcmp(color, "blue") == 0){
            if (number > counts[2]) {
                return 0;
            }
        }

        values = strtok_s(NULL, ",", &saveptr);
    }
    
    return 1;
}

int main() {
    int counts[3] = {12, 13, 14};
    printf("%d\n", verifyGames("day2_input.txt", counts));
    printf("Total power: %d\n", findTotalPower("day2_input.txt", counts));
    return 0;
}




