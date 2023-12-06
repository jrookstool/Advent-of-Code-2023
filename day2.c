#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define MAX_LENGTH 256

int validateLine(char *line, int counts[]);

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

int validateClause(char *clause, int counts[]) {
    char *saveptr;
    char *values = strtok_r(clause, ",", &saveptr);
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

        values = strtok_r(NULL, ",", &saveptr);
    }
    
    return 1;
}

int main() {
    int counts[3] = {12, 13, 14};
    printf("%d\n", verifyGames("day2_input.txt", counts));
    return 0;
}




