#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_VALUE 20
#define MIN_VALUE 1
#define NUM_ROWS 3
#define NUM_COLS 2
#define NUM_THREADS 3

double A[NUM_ROWS][NUM_COLS];
double x[NUM_COLS];
double y[NUM_ROWS];

void* Multiplicacao_matriz_vetor(void* rank) {
    long my_rank = (long) rank;
    int i, j;
    int local_m = NUM_ROWS/NUM_THREADS;
    int my_first_row = my_rank*local_m;
    int my_last_row = my_first_row + local_m;

    for (i = my_first_row; i < my_last_row; i++) {
        y[i] = 0.0;
        for (j = 0; j < NUM_COLS; j++) {
            y[i] += A[i][j]*x[j];
        }
    }

    return NULL;
}

int main() {
    srand(time(NULL));

    // Preenche a matriz A e o vetor x com valores aleatórios
    printf("Matriz A:\n");
    for (int i = 0; i < NUM_ROWS; i++) {
        for (int j = 0; j < NUM_COLS; j++) {
            A[i][j] = (double)(rand() % (MAX_VALUE - MIN_VALUE + 1)) + MIN_VALUE;
            printf("%.2f ", A[i][j]);
        }
        printf("\n");
    }

    printf("\nVetor x:\n");
    for (int j = 0; j < NUM_COLS; j++) {
        x[j] = (double)(rand() % (MAX_VALUE - MIN_VALUE + 1)) + MIN_VALUE;
        printf("%.2f ", x[j]);
    }
    printf("\n");

    long       thread;
    pthread_t* thread_handles;

    thread_handles = malloc(NUM_THREADS*sizeof(pthread_t));

    for (thread = 0; thread < NUM_THREADS; thread++) {
        pthread_create(&thread_handles[thread], NULL, Multiplicacao_matriz_vetor, (void*) thread);
    }

    for (thread = 0; thread < NUM_THREADS; thread++) {
        pthread_join(thread_handles[thread], NULL);
    }

    printf("\nResultado da multiplicação matriz-vetor:\n");
    for (int i = 0; i < NUM_ROWS; i++) {
        printf("%.2f\n", y[i]);
    }

    free(thread_handles);

    return 0;
}
