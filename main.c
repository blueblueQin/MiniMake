#include <stdio.h>
#include <string.h>
#include "head.h"



int main(int argc, char *argv[]){

    int minimakefound = findminimake(argc,argv[1]);//检测输入的命令minimake
    if(minimakefound==0){printf("invalid input\n");return 0;}

    int helpfound = identifyinput(argc, argv);//检测--help
    if(helpfound==1) {return 0;}

    system("pwd\n");//测试输出指令

    static char content[100][1030]={'\0'};
    int vfound = findv(argc,argv);
    processfile("./Makefile",vfound,content);


    char targetlines[10][512];
    char commandlines[10][1024];
    int targetnumber=getrule(content , targetlines , commandlines );


    Rule rules[10];
    for(int i=0;i<targetnumber;i++){
        Rule *rule = & rules[i];
        if(analyserule(targetlines[i], commandlines[i], rule, rules, targetnumber)==1) {
            return 0;
        }
    }

    return 0;
}