#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <readline/readline.h>
#include "funs.h"

/*void free_matrix(int **matrix, int m) {
    for (int i = 0; i < m; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

int getNumberFromBinary(int binary) {
    int number = binary;
    int finalNumber = 0;
    int currentDigit = 0;
    int i = 0;
    while (number != 0) {
        currentDigit = number % 10;
        for (int j = 0; j < i; j++) {
            currentDigit *= 2;
        }
        finalNumber += currentDigit;
        number /= 10;
        i++;
    }
    return finalNumber;
}

int **makeMatrixWithKnownBinaryStringAndDimension(char *raw, int m, int n) {
    int **emptyMatrix = (int **) calloc(m, sizeof(int *));
    for (int i = 0; i < m; i++) {
        emptyMatrix[i] = (int *) calloc(n, sizeof(int));
    }
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            emptyMatrix[i][j] = 0;
        }
    }
    int rawLength = strlen(raw);
    int currentStepRaw = 0;
    char *currentNumber = NULL;
    int currentColumn = 0;
    int currentRaw = 0;
    for(int i = 0; i < rawLength; i++) {
        char *appendingString = (char *) malloc(2);
        appendingString[0] = raw[i];
        appendingString[1] = '\0';
        if (currentNumber != NULL) {
            currentNumber = strcat(currentNumber, appendingString);
        } else {
            currentNumber = appendingString;
        }
        if (currentStepRaw % 8 == 7) {
            emptyMatrix[currentRaw][currentColumn] = getNumberFromBinary((atoi(currentNumber)));
            currentNumber = NULL;
            if (currentRaw + currentColumn >= m + n - 2) {
                break;
            }
            if (currentColumn == n - 1) {
                currentColumn = 0;
                currentRaw += 1;
            } else {
                currentColumn += 1;
            }
            currentStepRaw = 0;
            currentNumber = 0;
        } else {
            currentStepRaw++;
        }
        //free(appendingString);
    }
    free(currentNumber);
    return emptyMatrix;
}

int **insertRawByIndex(int **matrix, int *raw, int index, int m, int n) {
    int **result = (int **) calloc(m + 1, sizeof(int *));
    for (int i = 0; i < m + 1; i++) {
        result[i] = (int *) calloc(n, sizeof(int));
    }
    for (int i = 0; i < index; i++) {
        for (int j = 0; j < n; j++) {
            result[i][j] = matrix[i][j];
        }
    }
    int **s = result;
    for (int i = 0; i < n; i++) {
        int k = raw[i];
        result[index][i] = raw[i];
    }
    for (int i = index; i < m; i++) {
        for (int j = 0; j < n; j++) {
            result[i+1][j] = matrix[i][j];
        }
    }
    free_matrix(matrix, m);
    return result;
}

int **insertColumnByIndex(int **matrix, int *raw, int index, int m, int n) {
    int **result = (int **) calloc(m, sizeof(int *));
    for (int i = 0; i < m; i++) {
        result[i] = (int *) calloc(n + 1, sizeof(int));
    }
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < index; j++) {
            result[i][j] = matrix[i][j];
        }
    }
    for (int i = 0; i < m; i++) {
        int k = raw[i];
        result[i][index] = raw[i];
    }
    for (int i = 0; i < m; i++) {
        for (int j = index; j < n; j++) {
            result[i][j + 1] = matrix[i][j];
        }
    }
    free_matrix(matrix, m);
    return result;
}

int **deleterRawByIndex(int **matrix, int index, int m, int n) {
    int **result = (int **) calloc(m - 1, sizeof(int *));
    for (int i = 0; i < m - 1; i++) {
        result[i] = (int *) calloc(n, sizeof(int));
    }
    for (int i = 0; i < index; i++) {
        for (int j = 0; j < n; j++) {
            result[i][j] = matrix[i][j];
        }
    }
    for (int i = index; i < m - 1; i++) {
        for (int j = 0; j < n; j++) {
            result[i][j] = matrix[i + 1][j];
        }
    }
    free_matrix(matrix, m);
    return result;
}

int **deleteColumnByIndex(int **matrix, int index, int m, int n) {
    int **result = (int **) calloc(m, sizeof(int *));
    for (int i = 0; i < m; i++) {
        result[i] = (int *) calloc(n - 1, sizeof(int));
    }
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < index; j++) {
            result[i][j] = matrix[i][j];
        }
    }
    for (int i = 0; i < m; i++) {
        for (int j = index; j < n - 1; j++) {
            result[i][j] = matrix[i][j + 1];
        }
    }
    free_matrix(matrix, m);
    return result;
}

void printMatrix(int **matrix, int m, int n) {
    printf("\n--------------------\n");
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            printf("%-5d", matrix[i][j]);
        }
        printf("\n");
    }
    printf("--------------------\n");
}*/

int main() {
    int **matrix = NULL;
    char *string = NULL;
    int m = 0;
    int n = 0;
    int choice = 0;
    do {
        printf("1. Form matrix\n2. Export matrix\n3. Edit matrix\n4. Exit\n");
        while (scanf("%d", &choice) != 1 || ((int) choice > 4) || (int) choice < 1) {
            printf("Error. Enter correct number\n");
            getchar();
        }
        switch (choice) {
            int choice1 = 0;
            case 1:
                printf("");
                //free(matrix);
                printf("1. Read from keyboard\n2. Read from binary file\n3. Random value\n");
                while (scanf("%d", &choice1) != 1 || ((int) choice1 > 3) || (int) choice1 < 1) {
                    printf("Error. Enter correct number\n");
                    getchar();
                }
                switch (choice1) {
                    case 1:
                        printf("Enter number of lines\n");
                        while (scanf("%d", &m) != 1) {
                            printf("Error. Enter correct number of lines\n");
                            getchar();
                        }
                        printf("Enter number of columns\n");
                        while (scanf("%d", &n) != 1) {
                            printf("Error. Enter correct number of columns\n");
                            getchar();
                        }
                        string = readline("Enter binary string\n");
                        break;
                    case 2:
                        printf("");
                        FILE *fl;
                            char* file = readline("Enter name of file\n");
                            fl = fopen(file, "rb");
                            if (fl) {
                                fread(&m, sizeof(int), 1, fl);
                                fread(&n, sizeof(int), 1, fl);
                                printf("m = %d, n = %d\n", m, n);
                                string = malloc(sizeof(char) * 17);
                                fread(string, sizeof(char) * 16, 1, fl);
                                fclose(fl);
                            } else {
                                printf("This file does not exist\n");
                            }
                        break;
                    case 3:
                        srand(time(NULL));
                        n = 1 + rand() % 10;
                        m = 1 + rand() % 10;
                        int stringSize = rand() % 40;
                        string = (char *) malloc(sizeof(char) * stringSize);
                        for (int i = 0; i < stringSize; i++) {
                            string[i] = (char) ('0' + rand() % 2);
                        }
                        break;
                }
                matrix = (int **) calloc(m, sizeof(int *));
                for (int i = 0; i < m; i++) {
                    matrix[i] = (int *) calloc(n, sizeof(int));
                }
                matrix = makeMatrixWithKnownBinaryStringAndDimension(string, m, n);
                //free(string);
                break;
            case 2:
                printf("1. Write matrix to console\n2. Write matrix to binary file\n");
                while (scanf("%d", &choice1) != 1 || ((int) choice1 > 2) || (int) choice1 < 1) {
                    printf("Error. Enter correct number\n");
                    getchar();
                }
                switch (choice1) {
                    case 1:
                        printMatrix(matrix, m, n);
                        break;
                    case 2:
                        printf("");
                        char *file = readline("Enter filename\n");
                        FILE *fl;
                        fl = fopen(file, "wb");
                        if (fl) {
                            for (int i = 0; i < m; i++) {
                                for (int j = 0; j < n; j++) {
                                    fprintf(fl, "%-5d", matrix[i][j]);
                                }
                                fprintf(fl, "\n");
                            }
                        }
                        fclose(fl);
                        break;
                }
                break;
            case 3:
                printf("");
                int index;
                printf("1. Insert a line by index\n2. Insert a column by index\n3. Delete a line by index\n4. Delete a column by index\n");
                while (scanf("%d", &choice1) != 1 || ((int) choice1 > 4) || (int) choice1 < 1) {
                    printf("Error. Enter correct number\n");
                    getchar();
                }
                printf("current matrix is %d x %d\n", m, n);
                printf("Please enter the index\n");
                switch (choice1) {
                    case 1:
                        while (scanf("%d", &index) != 1 || ((int) index >= m) || (int) index < 0) {
                            printf("Error. Enter correct index\n");
                            getchar();
                        }
                        int *line = calloc(n, sizeof(int));
                        printf("Enter %d numbers\n", n);
                        for (int i = 0; i < n; i++) {
                            scanf("%d", &line[i]);
                        }
                        matrix = insertRawByIndex(matrix, line, index, m, n);
                        m++;
                        break;
                    case 2:
                        while (scanf("%d", &index) != 1 || ((int) index >= n) || (int) index < 0) {
                            printf("Error. Enter correct index\n");
                            getchar();
                        }
                        int *column = calloc(m, sizeof(int));
                        printf("Enter %d numbers\n", m);
                        for (int i = 0; i < m; i++) {
                            scanf("%d", &column[i]);
                        }
                        matrix = insertColumnByIndex(matrix, column, index, m, n);
                        n++;
                        break;
                    case 3:
                        while (scanf("%d", &index) != 1 || ((int) index >= m) || (int) index < 0) {
                            printf("Error. Enter correct index\n");
                            getchar();
                        }
                        matrix = deleterRawByIndex(matrix, index, m, n);
                        m--;
                        break;
                    case 4:
                        while (scanf("%d", &index) != 1 || ((int) index >= n) || (int) index < 0) {
                            printf("Error. Enter correct index\n");
                            getchar();
                        }
                        matrix = deleteColumnByIndex(matrix, index, m, n);
                        n--;
                        break;
                }
                break;
            case 4:
                exit(0); //TODO
                break;
            default:
                break;
        }
    } while (choice != 4);
    free_matrix(matrix, m);
    return 0;
}
