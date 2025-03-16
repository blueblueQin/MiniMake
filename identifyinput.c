#include <stdio.h>
#include <string.h>
#include "head.h"



int findhelp(int a,char *words[]){
    for (int i=0;i<a;i++) {
        if (strcmp(words[i], "--help") == 0) {
            printf("\there is a --help\n");
            printf("Usage: minimake [options]  ... \n");
            printf("Options:\n");
            printf("\t--help\tget more information\n");
            printf("\t-v  --verbose\tOutput the cleaned content to Minimake_claered.mk\n");
            printf("This program built for ...\n");
            printf("Report bugs to ...\n");
            return 1;
        }
    }
    printf("\tno help\n");
    return 0;
}

int findminimake(int a,char *words){
        if (strcmp(words, "minimake") == 0) {
            return 1;
        }
    return 0;
}

int findv(int a,char **words){
    int k=0;
    for(int i=2;i<a;i++) {
        if(strcmp(words[i],"-v")||strcmp(words[i],"--verbose")) {k=1;printf("here is a -v/--verbose\n");}
    }
    return k;
}

int identifyinput(int a, char **words) {
    int k=findhelp(a, words);
    for (int i=0;i<a;i++) {
        printf("word %d: %s\n", i, words[i]);
    }
    if(k==1) return 1;
    return 0;
}