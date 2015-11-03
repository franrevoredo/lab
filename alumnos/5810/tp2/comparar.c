#include "comparar.h"
#include <string.h>

char* comparar(char* pal, char* cen) {

    int len, i = 0, dif;


    dif = 0;

    len = strlen(pal);


    if (strlen(pal) == strlen(cen)) {

        while (i < len) {
            if (pal[i] != cen[i]) {
                dif++;
            }
            i++;
        }

        if (dif == 0) {
            strncpy(pal, "???????????????????", len);
        }

    } else if (strlen(pal) == (strlen(cen) + 1)) {

        if (pal[len - 1] == ',' || pal[len - 1] == ':' || pal[len - 1] == ';' || pal[len - 1] == '.' || pal[len - 1] == '\n' || pal[len - 1] == '\0') { //Si esto es verdad significa que el ultimo caracter del token es un signo, por lo tanto lo ignoramos al comparar

            while (i < (len - 1)) {
                if (pal[i] != cen[i]) {
                    dif++;
                }
                i++;
            }

            if (dif == 0) {
                strncpy(pal, "???????????????????", len - 1);
            }

        } else if (pal[0] == ',' || pal[0] == ':' || pal[0] == ';' || pal[0] == '.' || pal[0] == '\n' || pal[0] == '\0') { //Esto significa si es verdadero que el primer caracter es un signo, por lo empezamos a comparar del segundo en adelante

            while ((i + 1) < len) {
                if (pal[i] != cen[i]) {
                    dif++;
                }
                i++;
            }

            if (dif == 0) {
                strncpy(pal + 1, "???????????????????", len - 1);
            }


        }
    } else if (strlen(pal) == (strlen(cen) + 2)) {
        
    
        if (pal[0] == '"' && pal[len - 1] == '"') { //Si esto es verdad significa que la palabra esta entre comillas

            i++;
            
            while (i < (len - 1)) {
                if (pal[i] != cen[i]) {
                    dif++;
                }
                i++;
            }

            if (dif == 0) {
                strncpy(pal + 1, "???????????????????", len - 2);
            }

        }
    }



    return pal;
}
