#include <string.h>
#include <unistd.h>
#include "checkext.h"

int checkext(char * arch) {

	char * token;
	int dif, dif2;
	token = strrchr(arch, '.');
	token = token + 1;
	dif = strcmp(token, "html");
	if(dif == 0) {
		return 1;
	} else {
		
		dif = strcmp(token, "jpg");
		dif2 = strcmp(token, "jpeg");
		if(dif == 0 || dif2 == 0) {
			return 2;
		} else {
			dif = strcmp(token, "txt"); 
			if(dif == 0) {
				return 3;
			} else {
				dif = strcmp(token, "pdf");
				if(dif == 0) {
					return 4;
				} else {
					return -1;
				}
			}
		}
	}
}

	

