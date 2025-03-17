#ifndef head.h
#define head.h

int identifyinput(int a, char **words);

int findhelp(int a,char *words[]);

int findminimake(int a,char *words);

int findv(int a,char **words);

void processfile(const char *file1,int vfound, char *content[]);

int getrule(char *content[] , char *targetlines[] , char *commandlines[] );

int getrule2(char *targetlines[],char *commandlines[],const char *file);


#pragma once
typedef struct rulestruct{
    char target[32];               // 目标
    char dependencies[32][32]; // 依赖
    int dependencycount;                     // 依赖数量
    char commands[10][128]; // 命令
    int commandcount;                        // 命令数量
} Rule;

int analyserule(const char *target_line, const char *command_line, Rule *rule);

int checkrule(Rule *rule, const Rule rules[],int rule_count,int sense);

Rule *parse_makefile(const char *filename, int *rule_count);

void printrule(Rule *rule,int count);

#endif 