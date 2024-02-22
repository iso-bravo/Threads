#include <pthread.h>
#include <stdio.h>
#include <sys/wait.h>

#define NT 8




void *multiply(void *id, start, end){
    for(i=start, i < end, i++){
        for (j = 0, j < size, j ++) {
            for (k = 0, k < size, k++) {
                M3 [i][j] += M1[i][k] * M2[k][j];
            }
        }
    }
}

int main(){
    pthread_t T[NT]; //Numero de cores disponibles
    int i,e;
    for(i=0; i<NT; i++){
        start = (op_nt * id) 
        e = pthread_create(&T[i],NULL,printT,(void *)i);
        if(e!=0)
            printf("Error\n");
    }
    wait(NULL);
    return 0;
}