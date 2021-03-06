#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include "http_worker.h"

int main(int argc, char * const *argv) {
    int sd, sd_conn;
    int opt = 1, optlen = sizeof (opt);
    socklen_t addrlen;
    struct sockaddr_in srv_addr;
    struct sockaddr_in cli_addr;
        
    sd = socket(AF_INET, SOCK_STREAM, 0);

    if (sd < 0) {
        perror("Error al abrir el SOCKET");
        exit(EXIT_FAILURE);
    }

    srv_addr.sin_family = AF_INET;
    srv_addr.sin_addr.s_addr = INADDR_ANY;
    srv_addr.sin_port = htons(5000);


    if (bind(sd, (struct sockaddr *) &srv_addr, sizeof (srv_addr)) == -1) {
        perror("Error en el BIND");
        exit(EXIT_FAILURE);
    }

    listen(sd, 20);


    while ((sd_conn = accept(sd, (struct sockaddr *) &cli_addr, &addrlen)) > 0) {
        switch (fork()) {
            case 0: // hijo
                http_worker(sd_conn,(struct sockaddr *) &cli_addr);
                return 0;

            case -1: // error
                break;

            default: // padre
		close(sd_conn);
                break;
        }
    }

    return 0;
}
