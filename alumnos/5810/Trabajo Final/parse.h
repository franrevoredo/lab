#ifndef PARSE_H
#define	PARSE_H

#ifdef	__cplusplus
extern "C" {
#endif
#include "http_worker.h"
#include <string.h>
#include <stdio.h>
#include <unistd.h>

    extern http_req_t req;
    http_req_t parse(int sd_conn);

#ifdef	__cplusplus
}
#endif

#endif	/* PARSE_H */
