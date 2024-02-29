#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define SIZE 1024
#define NT 8

int **createRandomMatrix(int, int);
void releaseMatrix(int **, int);
void printMat(int **);
void *multiply(void *);

int **M1, **M2, **M3;
int size;

int main() {
    size = SIZE;

    M1 = createRandomMatrix(size, 1);
    M2 = createRandomMatrix(size, 1);
    M3 = createRandomMatrix(size, 0);
    pthread_t T[NT];

    int block_size = size / NT;

    for (int i = 0; i < NT; i++) {
        int *args = (int *)malloc(3 * sizeof(int));
        args[0] = i * block_size;              
        args[1] = (i + 1) * block_size;        
        args[2] = size;                        
        pthread_create(&T[i], NULL, multiply, (void *)args);
    }

    for (int i = 0; i < NT; i++) {
        pthread_join(T[i], NULL);
    }

    printMat(M3);

    releaseMatrix(M1, size);
    releaseMatrix(M2, size);
    releaseMatrix(M3, size);

    return 0;
}

void *multiply(void *arguments) {
    int *args = (int *)arguments;
    int start = args[0];
    int end = args[1];
    int matrix_size = args[2];
    free(args);

    for (int i = start; i < end; i++) {
        for (int j = 0; j < matrix_size; j++) {
            for (int k = 0; k < matrix_size; k++) {
                M3[i][j] += M1[i][k] * M2[k][j];
            }
        }
    }

    pthread_exit(NULL);
}

int **createRandomMatrix(int size, int random) {
    int **Mat = (int **)malloc(size * sizeof(int *));
    for (int i = 0; i < size; i++)
        Mat[i] = (int *)malloc(size * sizeof(int));

    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            Mat[i][j] = (random) ? rand() % 100 + 1 : 0;

    return Mat;
}

void releaseMatrix(int **Mat, int size) {
    for (int i = 0; i < size; i++)
        free(Mat[i]);
    free(Mat);
}

void printMat(int **M) {
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++)
            printf("%5d", M[i][j]);
        printf("\n");
    }
}
