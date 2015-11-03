#include <unistd.h>
#include <string.h>
#include <stdio.h>

#include "nieto.h"
#include "comparar.h"

void nieto(int * han, int * nah, char * pal) {
	
	char * token;
	char * result;
	char delim[] = " \t\r\n\f";	
	
	char buff[500];
	char strptr[500];
	memset(buff, 0, sizeof(buff));
	
	int leido;

	close(han[1]);
	close(nah[0]);


	while((leido = read(han[0], buff, sizeof(buff))) > 0) {
		memset(strptr, 0, sizeof(strptr));
		for (token = strtok(buff, delim); token; token = strtok(NULL, delim)) {
			result = comparar(token, pal);
			strncat(strptr, result, strlen(token));
			strncat(strptr, " ", 1);
		}
		write(nah[1], strptr, leido);
		printf("%s", strptr);

	}

	close(nah[1]);
	close(han[0]);

	return;
}
