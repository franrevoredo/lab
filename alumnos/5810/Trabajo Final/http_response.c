#include <unistd.h>
#include <string.h>

unsigned long long int http_response(int mime, int sd_conn, int fd) {

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
            return 0;
            break;

        case 2:
            write(sd_conn, rjpg, strlen(rjpg));
            memset(buff, 0, sizeof buff);
            while ((leido = read(fd, buff, sizeof buff)) > 0) {
                write(sd_conn, buff, sizeof buff);
            }
            write(sd_conn, "\n\n", 2);
            return 0;
            break;

        case 3:
            write(sd_conn, rtxt, strlen(rtxt));
            memset(buff, 0, sizeof buff);
            while ((leido = read(fd, buff, sizeof buff)) > 0) {
                write(sd_conn, buff, leido);
            }
            write(sd_conn, "\n\n", 2);
            return 0;
            break;

        case 4:
            write(sd_conn, rpdf, strlen(rpdf));
            memset(buff, 0, sizeof buff);
            while ((leido = read(fd, buff, sizeof buff)) > 0) {
                write(sd_conn, buff, sizeof buff);
            }
            write(sd_conn, "\n\n", 2);
            return 0;
            break;

        case 5:
            write(sd_conn, rico, strlen(rico));
            memset(buff, 0, sizeof buff);
            while ((leido = read(fd, buff, sizeof buff)) > 0) {
                write(sd_conn, buff, sizeof buff);
            }
            write(sd_conn, "\n\n", 2);
            return 0;
            break;

        case 10:
            return 10;
            break;

        case 1000:
            return 1000;
            break;

        case 100000:
            return 100000;
            break;

        case 1000000:
            return 1000000;
            break;

        case 10000000:
            return 10000000;
            break;

        case 50000000:
            return 50000000;
            break;

        case 100000000:
            return 100000000;
            break;
        case 100000001:
            return 1000000000;
            break;
    }
    
    return 0;
}