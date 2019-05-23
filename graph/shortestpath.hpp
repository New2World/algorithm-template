#pragma once
#include <memory.h>
#include <queue>

#include "graph.hpp"

#define INF 0x3f3f3f3f

class SPFA: public _Graph{
    int dis[MAXLEN];
    int pre[MAXLEN];
    bool inque[MAXLEN];
    int srcNode;

    void cleanMem();
    void _calc();
public:
    SPFA(int);
    int pathLength(int, int);
};

SPFA::SPFA(int n):_Graph(n){
    cleanMem();
}

void SPFA::cleanMem(){
    memset(dis, INF, sizeof(dis));
    memset(pre, -1, sizeof(pre));
    memset(inque, false, sizeof(inque));
    srcNode = -1;
}

void SPFA::_calc(){
    int u, v;
    dis[srcNode] = 0;
    std::queue<int> que;
    que.push(srcNode);
    while(!que.empty()){
        u = que.front();
        que.pop();
        for(int i = head[u];i != -1;i = edge[i].next){
            v = edge[i].v;
            if(dis[v] > dis[u] + edge[i].cost){
                dis[v] = dis[u] + edge[i].cost;
                if(!inque[v])
                    que.push(v);
            }
        }
    }
}

int SPFA::pathLength(int src, int snk){
    if(src != srcNode){
        cleanMem();
        srcNode = src;
        _calc();
    }
    return dis[snk];
}