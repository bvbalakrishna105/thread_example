#include <stdio.h>
#include <pthread.h>

#define MAX_COUNT 20

pthread_mutex_t mutex;
int counter = 1;

void *print_odd(void *arg) {
    while (counter <= MAX_COUNT) {
        pthread_mutex_lock(&mutex);
        if (counter % 2 != 0) {
            printf("Odd: %d\n", counter);
            counter++;
        }
        pthread_mutex_unlock(&mutex);
    }
    pthread_exit(NULL);
}

void *print_even(void *arg) {
    while (counter <= MAX_COUNT) {
        pthread_mutex_lock(&mutex);
        if (counter % 2 == 0) {
            printf("Even: %d\n", counter);
            counter++;
        }
        pthread_mutex_unlock(&mutex);
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t tid1, tid2;

    pthread_mutex_init(&mutex, NULL);

    pthread_create(&tid1, NULL, print_odd, NULL);
    pthread_create(&tid2, NULL, print_even, NULL);

    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);

    pthread_mutex_destroy(&mutex);

    return 0;
}
