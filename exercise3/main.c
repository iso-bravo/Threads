#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/wait.h>

#define NumberOfThreads 10
#define size 100
#define b size/NumberOfThreads

int stotal;
pthread_t T[NumberOfThreads];
pthread_mutex_t the_mutex;

int array[size];

void *suma(void *i){
    int tid = (int)i;
    int inicio = tid * b;
    int fin = (tid + 1) * b;
    int subsuma = 0;

    for(int j=inicio; j<fin; j++){
        subsuma += array[j];
    }

    pthread_mutex_lock(&the_mutex);
    stotal += subsuma;
    pthread_mutex_unlock(&the_mutex);

    return NULL;
}

int main (void){
    pthread_mutex_init(&the_mutex, NULL);

    for(int i = 0; i < size; i++){
        array[i] = i + 1;
    }

    for(int i = 0; i < NumberOfThreads; i++){
        pthread_create(&T[i], NULL, suma, (void *)i);
    }

    for(int i = 0; i < NumberOfThreads; i++){
        pthread_join(T[i], NULL);
    }

    printf("Total sum: %d\n", stotal);

    pthread_mutex_destroy(&the_mutex);

    return 0;
}
