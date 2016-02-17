#include "thread.h"


void * thread(void *arg) {

    int id, i;
    long double h;
    unsigned long long int coef;
    extern long double sum;
    extern int tid;

    id = tid;
    tid = tid + 1;
    coef = (*(params_t*) (arg)).coef;

    h = (*(params_t*) (arg)).h;

    long double x = 0.0;
    long double aux = 0.0;
    int ini = (coef * (id - 1)) + 1;
    int j = coef * (id);

    for (i = ini; i <= j; i++) {
        x = h * ((long double) i - 0.5);
        aux = aux + (4.0 / (1.0 + x * x));
    }
    pthread_mutex_lock(&(*(params_t*) (arg)).mutex);

    sum = sum + aux;

    printf("Thread: %d (%d - %d)\nSum: %Lf\n\n", id, ini, j, aux);

    pthread_mutex_unlock(&(*(params_t*) (arg)).mutex);

    pthread_exit(NULL);
}