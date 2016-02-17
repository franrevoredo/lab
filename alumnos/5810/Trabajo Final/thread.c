#include "thread.h"

void * thread(void *arg) {

    char method = (*(params_t*) (arg)).method;

    unsigned long long int coef = (*(params_t*) (arg)).coef;

    long double h = (*(params_t*) (arg)).h;

    int id, i, ini, j;

    extern long double sum;

    long double x = 0.0;
    long double aux = 0.0;

    switch (method) {
        case 'a':
            id = (*(params_t*) (arg)).thr_id;

            ini = (coef * (id - 1)) + 1;
            j = coef * (id);

            for (i = ini; i <= j; i++) {
                x = h * ((long double) i - 0.5);
                aux = aux + (4.0 / (1.0 + x * x));
            }
            
            pthread_mutex_lock(&(*(params_t*) (arg)).mutex);
            sum = sum + aux;
            pthread_mutex_unlock(&(*(params_t*) (arg)).mutex);
            
            printf("Thread: %d (%d - %d)\nSum: %Lf\n\n", id, ini, j, aux);


            break;
    }


    pthread_exit(NULL);
}