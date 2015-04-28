/* 
 * File:   main.c
 * Author: francisco
 *
 * Created on April 17, 2015, 6:43 PM
 */


#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char *argv[]) {

    int fd = 0, dfd = 0, stringsize, leido, opt, sourceflag = 0, cpal = 0, file = 0, help = 0, auxcount = 0;

    char source[100];

    char *pal1;

    char *pal2;

    char *pal3;

    char* path;

    char buff[1];

    char auxbuff[150];
    char* pch;


    extern char *optarg;
    extern int optind, opterr, optopt;


    while ((opt = getopt(argc, argv, "s:1:2:3:f:h")) != -1) {
        switch (opt) {
            case 's':
                strcpy(source, optarg);
                sourceflag = 1;
                break;

            case '1':
                pal1 = malloc(sizeof (int)*strlen(optarg));
                strcpy(pal1, optarg);
                cpal++;
                break;

            case '2':
                pal2 = malloc(sizeof (int)*strlen(optarg));
                strcpy(pal2, optarg);
                cpal++;
                break;

            case '3':
                pal3 = malloc(sizeof (int)*strlen(optarg));
                strcpy(pal3, optarg);
                cpal++;
                break;

            case 'f':
                path = malloc(sizeof (int)*strlen(optarg));
                strcpy(path, optarg);
                file = 1;
                break;

            case 'h':
                help = 1;

                write(1, "Uso: censurar -1 [PALABRA] \n\n Censura las palabras indicadas y las reemplaza por caracteres ? \n\n -s [NOMBRE DE ARCHIVO] Seleccionar el nombre del archivo fuente para censurar \n                        (Source), si se omite se lee el stdin. \n -f [NOMBRE DE ARCHIVO] Seleccionar el nombre del archivo destino para la cens\n                        ura, si se omite la salida sera por stdout. \n -2 [PALABRA]           Seleccionar una segunda palabra adicional para censurar. \n -3 [PALABRA]           Seleccionar una tercera palabra adicional para censurar. \n -h                     Ver este archivo de ayuda. \n\n Nota: Para usar el parametro -2 y -3 se necesita haber usado los parametros anteriores.\n\n", 696);
                break;
        }
    }

    if (cpal == 0 && help == 0) { //Si el contador de palabras está en cero significa que no se insertaron palabras
        write(2, "No se insertaron palabras a buscar! \n", 37);
        return -1;
    } else if (help == 1) {
        return 0;
    }


    if (sourceflag == 1) { //Si se marca el Source, se le asigna el file descriptor al archivo sino se deja en 0


        fd = open(source, O_RDONLY);

        if (fd < 0) {

            perror("Source open()");
            return -1;
        }

    } else {
        fd = 0;
    }


    if (file == 1) { // Si se especificó un destino se crea o se abre el archivo.
        dfd = open(path, O_RDWR | O_CREAT | O_TRUNC, 0777);

        if (dfd < 0) {

            perror("Destination open()");
            return -1;
        }
    }



    memset(auxbuff, 0, sizeof auxbuff);

    while (((leido = read(fd, buff, sizeof buff)) > 0)) { //Leo letra a letra el input.

        if (buff[0] == ' ' || buff[0] == ('.') || buff[0] == ',' || buff[0] == ':' || buff[0] == ';') { //Si la letra es un espacio lo contenido en el buffer de palabra es una palabra

            stringsize = strlen(pal1); //Calculo la longitud de la palabra a buscar.

            pch = strstr(auxbuff, pal1); //La comparo con la palabra que leí.

            if (pch != 0 && stringsize == auxcount) { //Si hay coincidencia se reemplaza por los signos ?.
                strncpy(pch, "?????????????????????", stringsize);
            } else if (cpal > 1) { //Si no hubo coincidencia y hay una segunda palabra a buscar se repite el proceso.

                stringsize = strlen(pal2);

                pch = strstr(auxbuff, pal2);

                if (pch != 0 && stringsize == auxcount) {
                    strncpy(pch, "?????????????????????", stringsize);
                } else if (cpal > 2) { //Si aún no hubo coincidencia y hay una tercera palabra se repite nuevamente.

                    stringsize = strlen(pal3);

                    pch = strstr(auxbuff, pal3);

                    if (pch != 0 && stringsize == auxcount) {
                        strncpy(pch, "?????????????????????", stringsize);
                    }

                }
            }

            switch (buff[0]) { //ya que el ultimo caracter fue ignorado y no se introdujo en el buffer. Se lo agregamos a la salida
                case ' ':
                    strncat(auxbuff, " ", 1);
                    break;
                case 46:
                    strncat(auxbuff, ".", 1);
                    break;
                case ',':
                    strncat(auxbuff, ",", 1);
                    break;
                case ':':
                    strncat(auxbuff, ":", 1);
                    break;
                case ';':
                    strncat(auxbuff, ";", 1);
                    break;
                default:
                    strncat(auxbuff, " ", 1);
                    break;
            }




            if (file == 1) { //Si esta en 1 el flag de destino se escribe en destino sino en stdout
                write(dfd, auxbuff, auxcount + 1);
            } else {
                write(1, auxbuff, auxcount + 1);
            }


            memset(auxbuff, 0, sizeof auxbuff); //Se vacia el buffer que contiene la palabra para leer la proxima

            auxcount = 0; //Se reinicia el contador de caracteres del buffer.
        } else {
            strncat(auxbuff, buff, 1); //Si la letra no era un espacio se inserta en el buffer de palabra.

            auxcount++; //Se aumenta el contador de caracteres del buffer.
        }



    }

    //Si abrí archivos los cierro al finalizar.

    if (sourceflag == 1)
        close(fd);

    if (file == 1)
        close(dfd);

    printf("\n");

    return 0;
}
