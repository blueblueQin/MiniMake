#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include "head.h"

int sysreplace(const char *command){

    pid_t pid = fork(); // 创建子进程
    if (pid < 0) {
        perror("fork failed");
        printf("\n");
        return -1; // 失败返回
    } 

    else if (pid == 0) {// 子进程
        
        char *args[] = {"/bin/sh", "-c", (char *)command, NULL};
        execvp(args[0], args); // 执行命令
        perror("execvp failed"); // 如果 execvp 失败
        printf("\n");
        exit(EXIT_FAILURE); // 子进程退出
    } 

    else {// 父进程
        
        int status=0;
        waitpid(pid, &status, 0); // 等待子进程结束
        if (WIFEXITED(status)) {
            return WEXITSTATUS(status); // 返回子进程的退出状态
        } else {
            return -1; // 子进程异常退出
        }
    }
    return -1;
}