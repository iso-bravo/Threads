#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

#define BUFFER_SIZE 5
//Setup Buffer
int buffer[BUFFER_SIZE]; 
int in = 0; 
int out = 0; 

pthread_mutex_t mutex; 
pthread_cond_t full; 
pthread_cond_t empty; 

void *producer(void *arg) {
    int item;
    while (1) {
        item = rand() % 100; 

        pthread_mutex_lock(&mutex); 

        while (((in + 1) % BUFFER_SIZE) == out) { 
            pthread_cond_wait(&empty, &mutex);
        }

        buffer[in] = item;
        printf("Productor produce el elemento %d\n", item);
        in = (in + 1) % BUFFER_SIZE; 

        pthread_cond_signal(&full); 
        pthread_mutex_unlock(&mutex); 

        sleep(rand() % 3); 
    }
}

void *consumer(void *arg) {
    int item;
    while (1) {
        pthread_mutex_lock(&mutex); 

        while (in == out) { 
            pthread_cond_wait(&full, &mutex);
        }

        item = buffer[out]; 
        printf("Consumidor consume el elemento %d\n", item);
        out = (out + 1) % BUFFER_SIZE; 

        pthread_cond_signal(&empty);
        pthread_mutex_unlock(&mutex); 

        sleep(rand() % 3); // Tiempo de Consumo 
    }
}

int main() {
    pthread_t producer_thread, consumer_thread;

    pthread_mutex_init(&mutex, NULL); 
    pthread_cond_init(&full, NULL); 
    pthread_cond_init(&empty, NULL); 

    pthread_create(&producer_thread, NULL, producer, NULL);
    pthread_create(&consumer_thread, NULL, consumer, NULL);

    pthread_join(producer_thread, NULL); 
    pthread_join(consumer_thread, NULL); 

    pthread_mutex_destroy(&mutex); 
    pthread_cond_destroy(&full); 
    pthread_cond_destroy(&empty); 

    return 0;
}
