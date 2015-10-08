#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "http_worker.h"
#include "checkget.h"
#include "checkext.h"

void http_worker(int sd_conn, struct sockaddr *cli_addr) {

    char delim[] = "\n";
    char delim2[] = " ";
    char * token;
    char * token2;
    char * headaux; 
    char ** head = (char**) calloc(3, sizeof (char*));
    int i = 0;
    int leido = 0;
    int len;
    int fd, mime;
    int http_ok = 0;

    char buff[4096];
    
    read(sd_conn, buff, sizeof buff);

    token = strtok(buff, delim);

    for (token2 = strtok(token, delim2); token2; token2 = strtok(NULL, delim2)) {

        len = strlen(token2) + 1;

        head[i] = (char*) malloc(sizeof (char)*len);
        head[i] = token2;
//        printf("Token: %s (%d) %d\n", head[i], len, i);
        i++;

    }


        if (checkget(head[0])) {

            write(1, "Ok (Method)\n", 12);
            http_ok++;

		if(head[1][0] == '/' && (strlen(head[1]) == 1)) {
	    		mime = 1;
			fd = open("index.html", O_RDONLY, 0777);
    		} else { 
			len = 0;
			len = strlen(head[1]);
			headaux = (char*) malloc(sizeof (char)*len);

			for(i=1;i<len;i++) {
				headaux[i-1] = head[1][i]; 				
			}
			
			mime = checkext(headaux);
			
			if(mime == -1) {
				write(sd_conn, "501 Not Implemented\n", 20);
            			printf("MIME no valido (%s)\n", headaux);
            			exit(EXIT_FAILURE);

			}						



			fd = open(headaux, O_RDONLY, 0777);
		}

       	    if (fd < 0) {
            	write(sd_conn, "404 File Not Found\n", 19);
            	perror("Destination open()");
            	exit(EXIT_FAILURE);
            } else {
            	write(1, "Ok (File)\n", 10);
            	http_ok++;
            }

        } else {

            write(sd_conn, "400 Bad request\n", 16);
            exit(EXIT_FAILURE);

        }
	

	if(http_ok == 2) {
		switch(mime) {
			case 1:
				write(sd_conn, "HTTP/1.1 200 OK\nContent-Type: text/html; charset=utf-8\nConnection:close\n\n", 73);
				memset(buff, 0, sizeof buff);
				while((leido = read(fd, buff, sizeof buff)) > 0) {
					write(sd_conn, buff, sizeof buff);
				}
				write(sd_conn, "\n\n", 2);
				break;
			case 2:
				write(sd_conn, "HTTP/1.1 200 OK\nContent-Type: image/jpeg; charset=utf-8\nConnection:close\n\n", 74);
				memset(buff, 0, sizeof buff);
				while((leido = read(fd, buff, sizeof buff)) > 0) {
					write(sd_conn, buff, sizeof buff);
				}
				write(sd_conn, "\n\n", 2);
				break;
			case 3:
				write(sd_conn, "HTTP/1.1 200 OK\nContent-Type: text/plain; charset=utf-8\nConnection:close\n\n", 74);
				memset(buff, 0, sizeof buff);
				while((leido = read(fd, buff, sizeof buff)) > 0) {
					write(sd_conn, buff, sizeof buff);
				}
				write(sd_conn, "\n\n", 2);
				break;
			case 4:
				write(sd_conn, "HTTP/1.1 200 OK\nContent-Type: application/pdf; charset=utf-8\nConnection:close\n\n", 76);
				memset(buff, 0, sizeof buff);
				while((leido = read(fd, buff, sizeof buff)) > 0) {
					write(sd_conn, buff, sizeof buff);
				}
				write(sd_conn, "\n\n", 2);
				break;		

}
    	}
    free(head);
    free(headaux);
    close(sd_conn);
}
