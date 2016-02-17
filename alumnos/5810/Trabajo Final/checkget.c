#include <string.h>

int checkget(char* metodo) {
    
    char* check = "GET";
    int i = 0, diff = 0;
    
    if(strlen(metodo) != 3) {
        return 0;
    } else {
        for(i=0;i<3;i++) {
            if(check[i] != metodo[i]) {
                diff++;
            }
        }
        if(diff == 0) {
            return 1;
        } else {
            return 0;
        }
    }
    
}