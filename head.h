#ifndef head.h
#define head.h

#include <sys/stat.h>
#include <time.h>

int identifyinput(int a, char **words);

int findhelp(int a,char *words[]);

int findminimake(int a,char *word);

int findv(int a,char **words);

void processfile(const char *file1,int vfound, char content[][1024]);

int getrule(char content[][1024] , char targetlines[][128] , char commandlines[][128] );

int getrule2(char targetlines[][128],char commandlines[][128],const char *file);

char* syscharfound(int a,char *word);


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

// 定义图节点结构体
typedef struct Nodee {
    char target[32]; // 目标或依赖文件名
    struct Nodee *next;           // 邻接表指针
} Node;

// 定义图结构体
typedef struct graphh{
    Node *nodes[100];      // 邻接表
    int in_degree[100];    // 入度
    int node_count;              // 顶点数量
} Graph;

time_t getfilemtime(const char *filename);

int needrebuild(const char *target, const char *dependencies[], int dependencynumber);

int find_or_add_node(Graph *graph, const char *target);

void add_edge(Graph *graph, const char *fromchar, const char *tochar);

void topological_sort(Graph *graph, Rule rules[], int rule_count);

void build_targets(Graph *graph, Rule rules[], int rule_count);

#endif 