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
struct sockaddr *cli_addr;    
    
void http_worker(int sd_conn, struct sockaddr *cli_addr);


#ifdef	__cplusplus
}
#endif

#endif	/* HTTP_WORKER_H */

