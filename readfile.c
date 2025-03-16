#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "head.h"

void processfile(const char *file1,int vfound){

    FILE *inputfile = fopen(file1, "r");
    if (inputfile == NULL) {
        perror("Failed to open file\n");
        return;
    }

    FILE *outputfile = NULL;
    if (vfound==1) {
        outputfile = fopen("Minimake_cleared.mk", "w");
        if (outputfile == NULL) {
            perror("Failed\n");
            fclose(inputfile);
            return ;
        }
    }

    char line[1024];
    int targetmarker=1;
    int linenumber=0;
    while (fgets(line, sizeof(line), inputfile)) {
        linenumber++;
        int length=strlen(line);
        while (length>0&&(line[length-1]=='\n'||isspace(line[length-1]))) {// 去除行尾的换行符和空格
            length--;
            line[length] = '\0';
        }

        if (length==0) continue;//去掉空行

        char *note = strchr(line,'#');//找到注释的位置
        if (note!=NULL){
            *note='\0';//去除注释
            length=strlen(line);
            while(length>0&&isspace(line[length-1])){
                length--;
                line[length]='\0';
            }
            if (length==0){
                continue;
            }
        }

        if (vfound) {
            fprintf(outputfile, "%s\n", line);//输出到文件
        }
        printf("%s\n", line); // 输出

        //检查异常

        char *colon=strchr(line,':');
        if (colon == NULL) {
            if(line[0]=='\t'){
                if(targetmarker==1) {printf("Line %d: Command found before rule\n",linenumber);continue;}
            }
            else printf("Line %d: Missing colon in target definition\n", linenumber);
            continue;//说明不是rule
        }
        else {
            targetmarker=0;//本行是rule 下一行可以是command
        }
    }


    fclose(inputfile);
    fclose(outputfile);
    return ;
}