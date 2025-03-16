#ifndef head.h
#define head.h

int identifyinput(int a, char **words);

int findhelp(int a,char *words[]);

int findminimake(int a,char *words);

int findv(int a,char **words);

void processfile(const char *file1,int vfound);

typedef struct {
    char *target;
    char **dependencies;
    char *command;
} Rule;

Rule *parse_makefile(const char *filename, int *rule_count);

#endif 