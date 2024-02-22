#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/wait.h>

#define SIZE 1024
#define NT 4

int **createRandomMatrix(int,int);
void releaseMatrix(int **, int);
void printMat(int **);
void *Multiply(void *);

int **M1,**M2,**M3;

int main(){
    M1 = createRandomMatrix(SIZE,1);
    M2 = createRandomMatrix(SIZE,1);
    M3 = createRandomMatrix(SIZE,0);
    pthread_t T[NT];

    
    wait(NULL);
    return 0;
}

int **createRandomMatrix(int size,int random){
    int *Mat = (int *) malloc(sizeof(int *)*10);
    int i,j;
    for(i=0; i<size; i++)
        Mat[i] = (int *) malloc(sizeof(int)*10);
    
    for(i=0; i<size; i++)
        for(j=0;j<size; j++)
            Mat[i][j] = (random)?rand() % 100 +1:0;
    return Mat;
}

void releaseMatrix(int **Mat, int size){
    int i;
    for(i=0; i<size; i++)
        free(Mat[i]);
    free(Mat);
}

void printMat(int **M){
    int i,j;
    for(i=0; i<10; i++){
        for(j=0;j<10; j++)
            printf("%5d",M[i][j]);
        printf("\n");
    }

}

void *Multiply(void *id){
    for (i = start ; i < end ; i++ )
{
    for (k = 0 ; k < 3 ; k++ ) 
    {
        temporal = 0 ;
        for (j = 0 ; j < 2 ; j++ ) 
                {                                   
            temporal += mat[i][j] * mat2[j][k];
            resultado[i][k] = temporal ;
        }
        }
}
}