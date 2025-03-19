#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "head.h"
#include <sys/stat.h>
#include <time.h>



int main(int argc, char *argv[]){

    int minimakefound = findminimake(argc,argv[1]);//检测输入的命令minimake
    if(minimakefound==0){printf("invalid input\n");return 0;}

    int helpfound = identifyinput(argc, argv);//检测--help
    if(helpfound==1) {return 0;}

    char* syschar={'\0'};
    if(argc>2) syschar=syscharfound(argc,argv[2]);//检测输入的minimake之后的一个target

    //system("pwd\n");//测试输出指令

    static char content[128][1024]={'\0'};
    int vfound = findv(argc,argv);
    processfile("./Makefile",vfound,content);


    char targetlines[10][128]={'\0'};
    char commandlines[10][128]={'\0'};
    //int targetnumber=getrule(content , targetlines , commandlines );
    //int targetnumber=getrule2(targetlines,commandlines,"Minimake_cleared.mk");


    
    FILE *inputfile = fopen("Makefile", "r");
    if (inputfile == NULL) {
        perror("Failed to open file \n");
        return 0;
    }
    char line[1024];
    int targetnumber=0;
    int commandnumber=-1;
    int linenumber=0;

    printf("\nfollowings are getting rules\n\n");

    while (fgets(line, sizeof(line), inputfile)){
        if(line[0]!='\t'){
            strcpy(targetlines[targetnumber],line);
            printf("%s",line);
            targetnumber++;
            commandnumber++; 
            linenumber++;
            continue;
        }
        else{
            strcat(commandlines[commandnumber],line);
            printf("%s",line);
            linenumber++;
        }
    }
    printf("targetnumber = %d\n",targetnumber);
    
    

    printf("\nfollowings are analysing rules\n\n");

    Rule rules[10];
    for(int i=0;i<targetnumber;i++){
        Rule *rule = & rules[i];
        analyserule(targetlines[i], commandlines[i], rule);
    }
    for(int i=0;i<targetnumber;i++){
        Rule *rule = & rules[i];
        if( checkrule(rule,rules,targetnumber,i)==1)  {
            return 0;
        }
    }

    
    for(int i=0;i<targetnumber;i++){//输出存储的rules
        Rule *rule = & rules[i];
        printrule(rule,i+1);
    }
    
    for(int i=0;i<targetnumber;i++){
        if(!strcmp(syschar,rules[i].target)) system(rules[i].commands[i]);
    }





    
    Graph graph = {0};// 构建依赖图
    for (int i = 0; i < targetnumber; i++) {
        for (int j = 0; j < rules[i].dependencycount; j++) {
            add_edge(&graph, rules[i].dependencies[j], rules[i].target);
        }
    }

    
    topological_sort(&graph, rules, targetnumber);// 拓扑排序

    
    build_targets(&graph, rules, targetnumber);// 构建目标

    
    for (int i=0;i<graph.node_count;i++) {// 释放内存

        Node *current=graph.nodes[i];

        while (current!=NULL) {
            Node *temp=current;
            current=current->next;
            free(temp);
        }
    }


    return 0;
}