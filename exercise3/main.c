#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/wait.h>

#define NumberOfThreads 10
#define size 100

pthread_mutex_t the_mutex;
pthread_mutex_init(&the_mutex, 0);

int array[size];




