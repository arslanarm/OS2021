#include "stdio.h"
#include "stdlib.h"
#include "string.h"


typedef struct IntArray {
    int *arr;
    int size;
} IntArrayT;

typedef struct Matrix {
    IntArrayT *arr;
    int verticalSize;
    int horizontalSize;
} MatrixT;

IntArrayT readLine(FILE *file) {
    int buffer[255];
    int n = 0;
    char *originalLine = malloc(255 * sizeof(char));
    size_t length = 255;
    int chars = getline(&originalLine, &length, file);
    if (chars == -1 || originalLine[0] == '\n') {
        IntArrayT arr = { NULL, 0 };
        return arr;
    }
    int number;
    char *line = malloc(length* sizeof(char));
    memcpy(line, originalLine, length);
    char *newLine = malloc(length * sizeof(char));
    while (1) {
        sscanf(line, "%d%255[^\n]s", &number, newLine);
       
        buffer[n] = number;
        n++;
      
        if (strcmp(line, newLine) == 0) {
            break;
        }
        memcpy(line, newLine, length);
    }
    free(line);
    free(newLine);
    free(originalLine);
    int *arr = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        arr[i] = buffer[i];
    }
    IntArrayT array = { arr, n };
    return array;
}

MatrixT readMatrix(FILE *file) {
    IntArrayT buffer[255];
    int n = 0;
    while (1) {
        IntArrayT current = readLine(file);
        if (current.size == 0) break;
        buffer[n] = current;
        n++;
    }
    IntArrayT *arr = malloc(n * sizeof(IntArrayT));
    for (int i = 0; i < n; i++) {
        arr[i] = buffer[i];
    }
    MatrixT matrix = { arr, n, arr[0].size };
    return matrix;
}

void freeArray(IntArrayT arr) {
    free(arr.arr);
}

void freeMatrix(MatrixT matrix) {
    for (int i = 0; i < matrix.verticalSize; i++) {
        freeArray(matrix.arr[i]);
    }
}


int main() {
    FILE *file = fopen("input.txt", "r");
    IntArrayT existing = readLine(file);
    readLine(file);
    IntArrayT available = readLine(file);
    readLine(file);
    MatrixT allocated = readMatrix(file);
    MatrixT requests = readMatrix(file);
    while (1) {
        int availableExists = 0;
        int number_empty = 0;
        for (int i = 0; i < requests.verticalSize; i++) {
            int isAvailable = 1;
            for (int j = 0; j < requests.horizontalSize; j++) {
                if (requests.arr[i].arr[j] > available.arr[j]) {
                    isAvailable = 0;
                }
            }

            if (isAvailable) {
                int isEmpty = 1;
                for (int j = 0; j < requests.horizontalSize; j++) {
                    if (requests.arr[i].arr[j] != 0) {
                        isEmpty = 0;
                        break;
                    }
                    if (allocated.arr[i].arr[j] != 0) {
                        isEmpty = 0;
                        break;
                    }
                }
                // printf("%d %d\n", isAvailable, isEmpty);
                if (isEmpty) {
                    number_empty++;
                    continue;
                }
                availableExists = 1;
                for (int j = 0; j < allocated.horizontalSize; j++) {
                    available.arr[j] += allocated.arr[i].arr[j] + requests.arr[i].arr[j];
                    requests.arr[i].arr[j] = 0;
                    allocated.arr[i].arr[j] = 0;
                }
            }
        }
        if (number_empty == requests.verticalSize) {
            printf("No deadlock\n");
            break;
        }
        if (!availableExists) {
            printf("Deadlock!\n");

            printf("Numbers of the deadlocked processes: \n");
            for (int i = 0; i < requests.verticalSize; i++) {
                for (int j = 0; j < requests.horizontalSize; j++) {
                    if (requests.arr[i].arr[j] != 0) {
                        printf("%d ", i);
                        break;
                    }    
                }
            }
            printf("\n");
            break;
        }
    }

    freeArray(existing);
    freeArray(available);
    freeMatrix(allocated);
    freeMatrix(requests);
}   
