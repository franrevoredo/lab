/* 
 * File:   http_worker.h
 * Author: francisco
 *
 * Created on September 27, 2015, 11:44 AM
 */

#ifndef HTTP_WORKER_H
#define	HTTP_WORKER_H

#ifdef	__cplusplus
extern "C" {
#endif
#include <pthread.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <pthread.h>
#include <fcntl.h>
#include <time.h>
#include <float.h>
#include <math.h>

#define RES_LEN 256
#define LINECOUNT 6
#define LINEMAX 384
#define NUM_THREADS 10 


    struct sockaddr *cli_addr;

    typedef struct http_req { //Estructura que contiene el parseo del request HTTP
        char method[6];
        char url[RES_LEN];
        char ver[10];
    } http_req_t;

    extern http_req_t req;

    typedef struct params { //Estructura que contiene el los parametros a enviar a cada thread
        pthread_mutex_t mutex;
        unsigned long long int coef;
        int thr_id;
        long double h;
        char method;
    } params_t;

    extern params_t params;

    typedef struct met_it { //Estructura que contiene el calculo a realizar y las iteraciones
        unsigned long long int it;
        char met;
    } met_it_t;

    met_it_t met_it;


    void http_worker(int sd_conn, struct sockaddr *cli_addr);


#ifdef	__cplusplus
}
#endif

#endif	/* HTTP_WORKER_H */

