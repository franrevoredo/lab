#include "http_worker.h"
#include "http_response.h"
#include "checkget.h"
#include "checkext.h"
#include "thread.h"
#include "parse.h"


/* Variables Compartidas */

long double sum = 0.0;
int tid = 1;

void http_worker(int sd_conn, struct sockaddr *cli_addr) {

    //Inicio definicion para los threads
    params_t params;
    pthread_t threads[NUM_THREADS];
    pthread_mutex_init(&params.mutex, NULL);
 
    //Fin definicion para los threads

    long double pi = 0.0;

    char urlaux[256] = "";
    http_req_t req;
    int i = 0;
    int len;
    int fd, mime;
    int http_ok = 0;
    unsigned long long int ifpi = 0;
    char buff[4096];

    char rhtml[] = "HTTP/1.1 200 OK\nContent-Type: text/html; charset=utf-8\nConnection:close\n\n";
    char by[] = "<br><br><div style='font-size: x-small; font-style: italic;'>Hecho por Francisco Revoredo.</div></body>";

    req = parse(sd_conn); //Parseamos el request y lo metemos dentro de la estructura

    if (checkget(req.method)) {

        write(1, "Ok (Method)\n", 12);
        http_ok++;

        if (req.url[0] == '/' && (strlen(req.url) == 1)) {
            mime = 1;
            fd = open("index.html", O_RDONLY, 0777);
        } else {
            len = 0;
            len = strlen(req.url);


            for (i = 1; i < len; i++) {
                urlaux[i - 1] = req.url[i];
            }

            mime = checkext(urlaux);

            if (mime == -1) {
                write(sd_conn, "501 Not Implemented\n", 20);
                printf("MIME no valido (%s)\n", urlaux);


            } else {
                if (mime < 10) {
                    fd = open(urlaux, O_RDONLY, 0777);
                }
            }
        }

        if ((fd < 0) && (mime < 9)) {
            write(sd_conn, "404 File Not Found\n", 19);
            perror("Destination open()");

        } else {
            write(1, "Ok (File)\n", 10);
            http_ok++;
        }

    } else {

        write(sd_conn, "400 Bad request\n", 16);

    }


    if (http_ok == 2) {
        ifpi = http_response(mime, sd_conn, fd);
    }

    if (ifpi > 0) {
        memset(buff, 0, sizeof buff);

        clock_t begin, end;
        double ms;

        begin = clock(); //Comienzo a Calcular Pi

        int i;
        unsigned long long int coef = ifpi / NUM_THREADS; //Calculo cuantas iteraciones le corresponde a cada thread del pool.
        long double h = 1.0 / (long double) ifpi;

        for (i = 0; i < NUM_THREADS; i++) {

            params.coef = coef;
            params.h = h;
            pthread_create(&threads[i], NULL, thread, &params);
            tid++;
        }

        for (i = 0; i < NUM_THREADS; i++) {
            pthread_join(threads[i], NULL);
        }


        /* Destroy all synchronization primitives.  */
        pthread_mutex_destroy(&params.mutex);


        pi = sum * h; //Termino de Calcular Pi


        end = clock();
        ms = (double) (end - begin) / CLOCKS_PER_SEC;



        write(sd_conn, rhtml, strlen(rhtml)); //cabecera de respuesta HTML

        char httplines[LINECOUNT][LINEMAX];

        snprintf(httplines[0], LINEMAX, "<head><title>Cálculo de Pi</title><body><h2><div style='text-decoration: underline;'>Calculo de Pi</div></h2>");
        snprintf(httplines[1], LINEMAX, "<b>Cantidad de iteraciones:</b> %llu <br>", ifpi);
        snprintf(httplines[2], LINEMAX, "<b>El Valor de Pi es:</b> 3.1415926535897932384626433832795028841971693993751058209749445923078164 <br>");
        snprintf(httplines[3], LINEMAX, "<b>El Valor de Pi es:</b> %.21Lf <br>", pi);
        snprintf(httplines[4], LINEMAX, "<b>El tiempo de cálculo fue de:</b> %f segundos. <br><br>", ms);
        snprintf(httplines[5], LINEMAX, "<div style='padding-left: 5px;'><a href='index.html'>Volver</a></div>");


        tid = 0;

        for (i = 0; i < LINECOUNT; i++) {
            write(sd_conn, httplines[i], strlen(httplines[i]));
        }

        sum = 0.0;

        write(sd_conn, by, strlen(by));
        write(sd_conn, "\n\n", 2);


    }


    close(fd);
    close(sd_conn);

    exit(0);
}
