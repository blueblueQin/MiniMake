#include <stdio.h>
#include <string.h>
#include "head.h"


int findhelp(int a,char *words[]){
    for (int i = 0; i < a; i++) {
        if (strcmp(words[i], "--help") == 0) {
            printf("\there is a --help\n");
            return 1;
        }
    }
    printf("\tinvalid input\n");
    return 0;
}


int identifyinput(int a, char **words) {
    printf("Number of words: %d\n", a);
    int k=findhelp(a, words);
    
    for (int i = 0; i < a; i++) {
        printf("word %d: %s\n", i, words[i]);
    }
    if(k==1) return 1;
    return 0;
}