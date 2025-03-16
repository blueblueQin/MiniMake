#include <stdio.h>
#include <string.h>
#include "head.h"

int main(int argc, char *argv[]){

    int minimakefound = findminimake(argc,argv[1]);//检测输入的命令minimake
    if(minimakefound==0){printf("invalid input\n");return 0;}

    int helpfound = identifyinput(argc, argv);//检测--help
    if(helpfound==1) {return 0;}

    system("pwd\n");//测试输出指令

    int vfound = findv(argc,argv);
    voidprocessfile("./Makefile",vfound);
    FILE *file1 = fopen("./Makefile","r");


    return 0;
}