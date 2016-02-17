#include "parse.h"


http_req_t parse(int sd_conn) {


    char delim[] = "\n";
    char delim2[] = " ";
    char *token;
    char *token2;
    
    int i = 0, len = 0;

    http_req_t req;

    char buff[4096];

    read(sd_conn, buff, sizeof buff);

    token = strtok(buff, delim);

    for (token2 = strtok(token, delim2); token2;
            token2 = strtok(NULL, delim2)) {

        len = strlen(token2) + 1;

        switch (i) {

            case 0:
                strncpy(req.method, token2, len);
                break;

            case 1:
                strncpy(req.url, token2, len);
                break;

            case 2:
                strncpy(req.ver, token2, len);
                break;
        }

        i++;
    }

    return req;

}