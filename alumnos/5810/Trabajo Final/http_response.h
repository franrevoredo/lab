/* 
 * File:   http_response.h
 * Author: francisco
 *
 * Created on September 27, 2015, 11:44 AM
 */

#ifndef HTTP_RESPONSE_H
#define	HTTP_RESPONSE_H

#ifdef	__cplusplus
extern "C" {
#endif


    unsigned long long int http_response(int mime, int sd_conn, int fd);


#ifdef	__cplusplus
}
#endif

#endif	/* HTTP_RESPONSE_H */

