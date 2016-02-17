#ifndef THREAD_H
#define	THREAD_H

#ifdef	__cplusplus
extern "C" {
#endif
#include <stdio.h>
#include <pthread.h>
#include "http_worker.h"

    
    void * thread(void *arg);

#ifdef	__cplusplus
}
#endif

#endif	/* THREAD_H */
