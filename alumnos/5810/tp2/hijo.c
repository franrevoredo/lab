#include <unistd.h>
#include <string.h>
#include <stdio.h> 
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

#include "hijo.h"
#include "rot13.h"
#include "nieto.h"

void hijo(int * pah, int * hap, char * pal) {

	extern int rot;
	extern int parse;

	int i;
	int rstatus;
	int leido = 0;
	
	char buff[500];
	char buffaux[500];
	
	memset (buff, 0, sizeof (buff));

	close (hap[0]);


	//Rot 13

      	if((rot == 1) && (parse != 1)) {
      		while ((leido = read (pah[0], buff, sizeof (buff))) > 0) {
			for(i=0;i<leido;i++) {
				buffaux[i] = rot13(buff[i]);	
			}			
			write (hap[1], buffaux, leido);
		}
      	}

	
	//Parseo
	
	if((parse == 1) && (rot != 1)) {
      		int nah[2];
		if(pipe(nah) == -1) {
			perror("Error creando pipe NaH");
		}
		
		int han[2];
		if(pipe(han) == -1) {
			perror("Error creando pipe HaN");
		}
			
		while ((leido = read (pah[0], buff, sizeof (buff))) > 0) {
			write (han[1], buff, leido);
		}

		close(han[1]);

		pid_t nietopid;

		nietopid = fork();

		switch(nietopid) {
			case 0:
				nieto(han, nah, pal);
				break;
			case -1:
				perror("Error creando nieto");
				break;

			default:
				
				waitpid (nietopid, &rstatus, 0);
				
				memset(buffaux,0,sizeof(buffaux));
				leido = 0;

				while ((leido = read (nah[0], buffaux, sizeof (buffaux))) > 0) {
					write (hap[1], buffaux, leido);
				}

				break;
		}

		close(han[0]);
		close(nah[1]);
		close(nah[0]);

      	}	

      	
      close (pah[0]);
      close (hap[1]);

return;
}
