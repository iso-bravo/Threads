#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/wait.h>

#define NumberOfThreads 10
#define NumberOfRequest 100

char FILENAME[] = "Contador.txt";
FILE *file = NULL;

pthread_mutex_t the_mutex;

int read_file();
int write_file(int);
void *contador(void *);

int main(void) {
    if ((file = fopen(FILENAME, "w")) == NULL) {
        printf("The file couldn't be created :(\n");
        return 0;
    }
    fprintf(file, "%d", 0);
    fclose(file);

    pthread_mutex_init(&the_mutex, NULL);
    pthread_t T[NumberOfThreads];

    int i;
    for (i = 0; i < NumberOfThreads; i++) {
        int *thread_id = malloc(sizeof(int));
        *thread_id = i;
        pthread_create(&T[i], NULL, contador, thread_id);
    }

    for (i = 0; i < NumberOfThreads; i++) {
        pthread_join(T[i], NULL);
    }

    pthread_mutex_destroy(&the_mutex);

    wait(NULL);

    return 0;
}

void *contador(void *id) {
    int thread_id = *((int *)id);
    free(id);

    for (int i = 0; i < NumberOfRequest; i++) {
        pthread_mutex_lock(&the_mutex);
        int a = read_file();
        a++;
        write_file(a);
        pthread_mutex_unlock(&the_mutex);
    }
    pthread_exit(NULL);
}

int read_file() {
    int contador;
    if ((file = fopen(FILENAME, "r")) == NULL) {
        printf("The file couldn't be read :(\n");
        return -1;
    }
    fscanf(file, "%d", &contador);
    fclose(file);
    return contador;
}

int write_file(int c) {
    if ((file = fopen(FILENAME, "w")) == NULL) {
        printf("The file couldn't be created :(\n");
        return -1;
    }
    fprintf(file, "%d", c);
    fclose(file);
    return 1;
}
