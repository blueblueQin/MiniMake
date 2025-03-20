#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>
#include "head.h"



time_t getfilemtime(const char *filename) {// 获取文件的修改时间
    struct stat file_stat;//结构体储存文件相关数据
    if (stat(filename, &file_stat) == 0) return file_stat.st_mtime;//执行成功时返回0
    return -1; // 文件不存在
}



int needrebuild(const char *target, const char *dependencies[], int dependencynumber) {// 检查是否需要重新构建，返回1需要

    time_t target_mtime = getfilemtime(target);//获取时间
    if (target_mtime == -1) return 1; // 目标文件不存在，需要构建

    for (int i = 0; i < dependencynumber; i++) {//分析依赖文件时间

        time_t dep_mtime = getfilemtime(dependencies[i]);

        if (dep_mtime == -1) {
            printf("Error: Dependency file '%s' does not exist\n", dependencies[i]);
            return -1; // 依赖文件不存在
        }
        if (dep_mtime > target_mtime) {
            return 1; // 依赖文件比目标文件新，需要重新构建
        }
    }

    return 0; // 不需要重新构建
}


int find_or_add_node(Graph *graph, const char *target) {// 添加节点到图

    for (int i = 0; i < graph->node_count; i++) {
        if (strcmp(graph->nodes[i]->target, target) == 0) return i; //检测是否已有// 返回已存在节点的索引
    }


    Node *new_node = (Node *)malloc(sizeof(Node));//没有则添加新节点
    strncpy(new_node->target, target, 32);//传递target名
    new_node->next = NULL;//初始化新节点邻接表指针
    graph->nodes[graph->node_count] = new_node;//接入表中
    graph->in_degree[graph->node_count] = 0;

    return graph->node_count++; // 返回新节点的次序
}


void add_edge(Graph *graph, const char *fromchar, const char *tochar) {// 添加边到图

    int fromindex = find_or_add_node(graph, fromchar);//确定起点（dependence）
    int toindex = find_or_add_node(graph, tochar);//确定目标点（target）
    
    Node *new_edge = (Node *)malloc(sizeof(Node));//创建新的边
    strncpy(new_edge->target, tochar, 32);
    new_edge->next = graph->nodes[fromindex]->next;// 添加边到邻接表
    graph->nodes[fromindex]->next = new_edge;

    graph->in_degree[toindex]++;// 更新入度
    return ;
}


void topological_sort(Graph *graph, Rule rules[], int rule_count) {// 拓扑排序
    int queue[100];
    int front = 0, rear = 0;

    
    for (int i = 0; i < graph->node_count; i++) {// 将入度为 0 的节点加入队列
        if (graph->in_degree[i] == 0) {
            queue[rear++] = i;
        }
    }

    
    printf("Topological Order:\n");// 输出拓扑排序结果
    while (front < rear) {
        int u = queue[front++];
        printf("%s\n", graph->nodes[u]->target);

        
        Node *current = graph->nodes[u]->next;// 遍历邻接表，减少依赖节点的入度
        while (current != NULL) {
            int v = -1;
            for (int i = 0; i < graph->node_count; i++) {
                if (strcmp(graph->nodes[i]->target, current->target) == 0) {
                    v = i;
                    break;
                }
            }
            if (v != -1 && --graph->in_degree[v] == 0) {
                queue[rear++] = v;
            }
            current = current->next;
        }
    }
    return ;
}


void build_targets(Graph *graph, Rule rules[], int rule_count) {// 构建目标
    int queue[100];
    int front = 0, rear = 0;

    
    for (int i = 0; i < graph->node_count; i++) {// 将入度为 0 的节点加入队列
        if (graph->in_degree[i] == 0) {
            queue[rear++] = i;
        }
    }

    printf("\nBuild Process:\n");
    while (front < rear) {// 依次检查并构建目标
        int u = queue[front++];
        const char *target = graph->nodes[u]->target;

        const char *dependencies[10];// 获取依赖文件
        int dependency_count = 0;
        for (int i = 0; i < rule_count; i++) {
            if (strcmp(rules[i].target, target) == 0) {
                for (int j = 0; j < rules[i].dependencycount; j++) {
                    dependencies[dependency_count++] = rules[i].dependencies[j];
                }
                break;
            }
        }

        
        int result = needrebuild(target, dependencies, dependency_count);// 检查是否需要重新构建
        if (result == 1) {
            printf("Building target: %s\n", target);
            
            for (int i = 0; i < rule_count; i++) {// 执行构建
                if (strcmp(rules[i].target, target) == 0) {
                    for (int j = 0; j < rules[i].commandcount; j++) {



                        int status = sysreplace(rules[i].commands[j]);
                        //system(rules[i].commands[j]);
                        if(status<0) {
                            printf("build targets failed\n");
                            return ;
                        }


                        
                    }
                    break;
                }
            }
        } else if (result == 0) {
            printf("Target '%s' is up to date\n", target);
        } else if (result == -1) {
            printf("Error: Cannot build target '%s'\n", target);
        }

        
        Node *current = graph->nodes[u]->next;
        while (current != NULL) {// 遍历邻接表，减少依赖节点的入度
            int v = -1;
            for (int i = 0; i < graph->node_count; i++) {
                if (strcmp(graph->nodes[i]->target, current->target) == 0) {
                    v = i;
                    break;
                }
            }
            if (v != -1 && --graph->in_degree[v] == 0) {
                queue[rear++] = v;
            }
            current = current->next;
        }
    }
    return ;
}