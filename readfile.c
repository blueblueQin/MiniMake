#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "head.h"

void processfile(const char *file1,int vfound, char content[][1024]){

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
    int contentnumber=0;

    int cntt=0;

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

        //printf("contentnumber: %d \n",contentnumber);

        //strcpy(content[contentnumber],line);
        /*int cnt=0;
        while(line[cnt]){
            content[contentnumber][cntt]=line[cnt];
            cnt++;
            cntt++;
        }*/

        //printf("content[%d]:%s \n",contentnumber,content[contentnumber]);

        //contentnumber++;

        //检查异常

        char *colon=strchr(line,':');
        if (colon == NULL) {
            if(line[0]=='\t'){
                if(targetmarker==1) {printf("Line %d: Command found before rule\n",linenumber);continue;}
            }
            else printf("Line %d: Missing colon in target definition\n", linenumber);
            continue;//说明不是target
        }
        else {
            targetmarker=0;//本行是target 下一行可以是command
        }
    }


    fclose(inputfile);
    if (vfound) fclose(outputfile);
    return ;
}



int getrule(char content[][1024] , char targetlines[][128] , char commandlines[][128] ){
    int targetnumber=0;
    int commandnumber=0;
    int linenumber=0;
    while(content[linenumber]){
        if(content[linenumber][0]!='\t'){
            strcpy(targetlines[targetnumber],content[linenumber]);
            targetnumber++;
            linenumber++;
            continue;
        }
        while(content[linenumber][0]=='\t'){
            strcat(commandlines[commandnumber],content[linenumber]);
            linenumber++;
        }
        commandnumber++;
    }
    return targetnumber;
}


int getrule2(char targetlines[][128],char commandlines[][128],const char *file){

    FILE *inputfile = fopen(file, "r");
    if (inputfile == NULL) {
        perror("Failed to open file ");printf("%s \n",file);
        return -1;
    }
    char line[1024];
    int targetnumber=0;
    int commandnumber=-1;
    int linenumber=0;

    printf("out of getrule2 while\n");

    while (fgets(line, sizeof(line), inputfile)){
        printf("in of getrule2 while\n");

        if(line[0]!='\t'){
            strcpy(targetlines[targetnumber],line);
            printf("in of strcpy\n");

            printf("%s\n",line);

            targetnumber++;
            commandnumber++; 
            linenumber++;
            continue;
        }
        if(line[0]=='\t'){
            strcat(commandlines[commandnumber],line);

            printf("%s\n",line);

            linenumber++;
        }
    }
    return targetnumber;

}