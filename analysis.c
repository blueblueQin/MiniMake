#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "head.h"



int file_exists(const char *path) {
    FILE *file1 = fopen(path, "r");
    if (file1) {
        fclose(file1);
        return 1;  // 文件存在
    }
    return 0;  // 文件不存在
}

int analyserule(const char *target_line, const char *command_line, Rule *rule){

    char media[256];

    strcpy(media, target_line);
    char *targetpart = strtok(media, ":");//从冒号往前拆
    char *dependenciespart = strtok(NULL, "\n");

    strncpy(rule->target, targetpart, 32);// 提取目标
    rule->target[31] = '\0';

    char *dependency = strtok(dependenciespart, " ");// 提取依赖

    rule->dependencycount = 0;
    while (dependency!=NULL&&rule->dependencycount<32) {
        strncpy(rule->dependencies[rule->dependencycount], dependency,32);
        rule->dependencycount++;
        dependency = strtok(NULL, " ");
    }

    // 解析命令
    strcpy(media,command_line);
    if(media[0]=='\t') media[0]=' ';
    char *command=strtok(media,"\t");
    rule->commandcount=0;
    while (command!=NULL&&rule->commandcount<10) {
        strncpy(rule->commands[rule->commandcount],command,128);
        rule->commandcount++;
        command=strtok(NULL,"\t");
    }
    return 0;
}





int checkrule(Rule *rule, const Rule rules[],int rule_count,int sense){

    for (int i=sense+1;i<rule_count;i++) {//检查是否相同
        if (strcmp(rule->target,rules[i].target)==0) {
            printf("Duplicate target definition '%s'\n", rule->target);
            return 1;
        }
    }

    // 检查依赖文件是否存在或是否为已定义的目标
    for (int i = 0; i < rule->dependencycount; i++) {
        if (file_exists(rule->dependencies[i])==0 ) {// 检查依赖文件是否存在,不存在的话继续检查
            // 检查是否是已定义的目标
            int istarget=0;
            for (int j=0;j<rule_count;j++) {
                if (strcmp(rule->dependencies[i], rules[j].target) == 0) {
                    istarget=1;
                    break;
                }
            }
            if (!istarget && sense!=0) {
                printf("Invalid dependency '%s'\n", rule->dependencies[i]);
                return 1;
            }
        }
    }
    return 0;
}


void printrule(Rule *rule,int count){
    printf("\nThis is no.%d rule\n",count);
    printf("%s : ",rule->target);
    for(int i=0;i<rule->dependencycount;i++){
        printf("%s ",rule->dependencies[i]);
    }
    printf("\n");
    for(int i=0;i<rule->commandcount;i++){
        printf("\t%s\n",rule->commands[i]);
    }
    return ;
}