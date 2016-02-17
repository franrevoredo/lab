#include <unistd.h>
#include <string.h>
#include "http_response.h"

met_it_t http_response(int mime, int sd_conn, int fd) {

    int leido = 0;
    char buff[4096];

    char rpdf[] = "HTTP/1.1 200 OK\nContent-Type: application/pdf;\nConnection:close\n\n";
    char rtxt[] = "HTTP/1.1 200 OK\nContent-Type: text/plain;\nConnection:close\n\n";
    char rjpg[] = "HTTP/1.1 200 OK\nContent-Type: image/jpeg; charset=utf-8\nConnection:close\n\n";
    char rhtml[] = "HTTP/1.1 200 OK\nContent-Type: text/html; charset=utf-8\nConnection:close\n\n";
    char rico[] = "HTTP/1.1 200 OK\nContent-Type: image/x-icon; charset=utf-8\nConnection:close\n\n";


    switch (mime) {
        case 1:
            write(sd_conn, rhtml, strlen(rhtml));
            memset(buff, 0, sizeof buff);
            while ((leido = read(fd, buff, sizeof buff)) > 0) {
                write(sd_conn, buff, sizeof buff);
            }
            write(sd_conn, "\n\n", 2);
            break;

        case 2:
            write(sd_conn, rjpg, strlen(rjpg));
            memset(buff, 0, sizeof buff);
            while ((leido = read(fd, buff, sizeof buff)) > 0) {
                write(sd_conn, buff, sizeof buff);
            }
            write(sd_conn, "\n\n", 2);
            break;

        case 3:
            write(sd_conn, rtxt, strlen(rtxt));
            memset(buff, 0, sizeof buff);
            while ((leido = read(fd, buff, sizeof buff)) > 0) {
                write(sd_conn, buff, leido);
            }
            write(sd_conn, "\n\n", 2);
            break;

        case 4:
            write(sd_conn, rpdf, strlen(rpdf));
            memset(buff, 0, sizeof buff);
            while ((leido = read(fd, buff, sizeof buff)) > 0) {
                write(sd_conn, buff, sizeof buff);
            }
            write(sd_conn, "\n\n", 2);
            break;

        case 5:
            write(sd_conn, rico, strlen(rico));
            memset(buff, 0, sizeof buff);
            while ((leido = read(fd, buff, sizeof buff)) > 0) {
                write(sd_conn, buff, sizeof buff);
            }
            write(sd_conn, "\n\n", 2);
            break;

        case 11:
            met_it.it = 10;
            met_it.met = 'a';
            return met_it;
            break;

        case 1001:
            met_it.it = 1000;
            met_it.met = 'a';
            return met_it;
            break;

        case 100001:
            met_it.it = 100000;
            met_it.met = 'a';
            return met_it;

        case 1000001:
            met_it.it = 1000000;
            met_it.met = 'a';
            return met_it;

        case 10000001:
            met_it.it = 10000000;
            met_it.met = 'a';
            return met_it;

        case 50000001:
            met_it.it = 50000000;
            met_it.met = 'a';
            return met_it;

        case 100000001:
            met_it.it = 100000000;
            met_it.met = 'a';
            return met_it;
    }

    met_it.it = 0;
    met_it.met = 0;
    return met_it;
}