#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include "checkext.h"

int checkext(char *arch) {

    char *token; //Para guardar la extension del archivo
    char *token2; //Para guardar la peticion get de la extension  despues del ?
    int dif, dif2;
    token = strrchr(arch, '.'); //Localizamos el caracter del punto
    token = token + 1; //Nos paramos en el caracter siguiente al punto
    dif = strcmp(token, "html");
    if (dif == 0) {
        return 1;
    } else {
        dif = strcmp(token, "jpg");
        dif2 = strcmp(token, "jpeg");

        if (dif == 0 || dif2 == 0) {
            return 2;
        } else {
            dif = strcmp(token, "txt");
            if (dif == 0) {
                return 3;
            } else {
                dif = strcmp(token, "pdf");
                if (dif == 0) {
                    return 4;
                } else {
                    dif = strcmp(token, "ico");
                    if (dif == 0) {
                        return 5;
                    } else {
                        token2 = strrchr(token, '?'); //Si encuentra un '?' es por que no es un documento sino una operación

                        if (token2[0] == '?') {
                            token2 = token2 + 1;

                            switch (token2[0]) {

                                case 'a':
                                    token2 = token2 + 1;

                                    switch (token2[0]) {
                                        case '1':
                                            return 11;
                                            break;
                                        case '2':
                                            return 1001;
                                            break;
                                        case '3':
                                            return 100001;
                                            break;
                                        case '4':
                                            return 1000001;
                                            break;
                                        case '5':
                                            return 10000001;
                                            break;
                                        case '6':
                                            return 50000001;
                                            break;
                                        case '7':
                                            return 100000001;
                                            break;
                                        case '8':
                                            return 100000001;
                                            break;
                                    }
                                    break;
                            }
                        } else {
                            return -1;
                        }
                    }
                }
            }
        }
    }
    return -1;
}

