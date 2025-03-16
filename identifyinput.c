#include <stdio.h>
#include <string.h>


void findhelp(int a,char *words[]){
    for (int i = 0; i < a; i++) {
        if (strcmp(words[i], "--help") == 0) {
            printf("\there is a --help\n");
            return ;
        }
    }
    printf("invalid input\n");
    return;
}


int main(int argc, char *argv[]) {
    printf("Number of words: %d\n", argc);
    findhelp(argc, argv);
    
    for (int i = 0; i < argc; i++) {
        printf("word %d: %s\n", i, argv[i]);
    }

    return 0;
}