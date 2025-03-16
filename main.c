#include <stdio.h>
#include <string.h>
#include "head.h"

int main(int argc, char *argv[]){

    
    int help = identifyinput(argc, argv);
    if(help==1) {
        return 0;
    }
    printf("123456789\n");

    return 0;
}