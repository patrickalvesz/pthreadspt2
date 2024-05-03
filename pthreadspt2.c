#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

double sum = 0.0;
int thread_count;
int n;
pthread_mutex_t mutex;

void* Thread_sum(void* rank) {
    long my_rank = (long) rank;
    double factor;
    long long i;
    long long my_n = n/thread_count;
    long long my_first_i = my_n*my_rank;
    long long my_last_i = my_first_i + my_n;
    double my_sum = 0.0;

    if (my_first_i % 2 == 0) /* my_first_i is even */
        factor = 1.0;
    else /* my_first_i is odd */
        factor = -1.0;

    for (i = my_first_i; i < my_last_i; i++, factor = -factor) {
        my_sum += factor/(2*i+1);
    }

    pthread_mutex_lock(&mutex);
    sum += my_sum;
    pthread_mutex_unlock(&mutex);

    return NULL;
} /* Thread_sum */

int main() {
    long thread;
    pthread_t* thread_handles;

    /*colocar thread_count e n com os valores para teste */
    thread_count = 16;
    n = 50000;

    thread_handles = malloc(thread_count*sizeof(pthread_t));
    pthread_mutex_init(&mutex, NULL);
    sum = 0.0;

    for (thread = 0; thread < thread_count; thread++)
        pthread_create(&thread_handles[thread], NULL, Thread_sum, (void*)thread);

    for (thread = 0; thread < thread_count; thread++)
        pthread_join(thread_handles[thread], NULL);

    pthread_mutex_destroy(&mutex);
    free(thread_handles);

    printf("\nQuantidade de threads: %d\n", thread_count);
    printf("\nValor de pi calculado pelo algoritmo: %.15f\n\n", 4.0*sum);

    return 0;
}

