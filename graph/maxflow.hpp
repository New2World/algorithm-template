#pragma once
#include <memory.h>
#include "graph.hpp"

#define INF 0x3f3f3f3f

class MaxFlow_SAP: public _Graph{
    int cur[MAXLEN];
    int gap[MAXLEN];
    int dis[MAXLEN];
    int pre[MAXLEN];

    void clearMem();
public:
    MaxFlow_SAP(int n):_Graph(n){};
    int maxflow(int, int);
};

void MaxFlow_SAP::clearMem(){
    memset(gap, 0, sizeof(gap));
    memset(dis, 0, sizeof(dis));
    memcpy(cur, head, sizeof(head));
}

int MaxFlow_SAP::maxflow(int src, int snk){
    int u, v;
    int aug = INF, flow = 0;
    bool flag;
    clearMem();
    gap[0] = n_node;                // gap[0] == |V| since all dis are initialized to 0
    u = pre[src] = src;
    while(dis[src] < n_node){
        flag = false;
        for(int &i = cur[u];i != -1;i = edge[i].next){
            v = edge[i].v;
            if(edge[i].cap > 0 && dis[u] == dis[v] + 1){
                flag = true;
                if(edge[i].cap < aug)
                    aug = edge[i].cap;
                pre[v] = u;
                u = v;
                if(u == snk){
                    flow += aug;
                    while(u != src){
                        u = pre[u];
                        edge[cur[u]].cap -= aug;
                        edge[cur[u] ^ 1].cap += aug;
                    }
                    aug = INF;
                }
                break;
            }
        }
        if(flag)
            continue;
        int mindis = n_node;
        for(int i = head[u];i != -1;i = edge[i].next){  // find out the nearest node v from u
            v = edge[i].v;
            if(edge[i].cap > 0 && dis[v] < mindis){
                mindis = dis[v];
                cur[u] = i;             // point to the nearest node
            }
        }
        if((--gap[dis[u]]) == 0)        // why -- ?
            break;
        dis[u] = mindis + 1;            // update distance from u to sink node
        gap[dis[u]]++;                  // after updating dis[u], a new path is added
        u = pre[u];                     // backtracking
    }
    return flow;
};

/*
line 33: Why &
& will change cur[u], but why should we do this? Let's go to line 45 and 46.
Here we'll go back to update capacity of each edge, and here we use cur[u] to locate the edge. So you see, if we do not change cur[u], it will always refer to the last edge we added to the array from vertex u to any other v.
To replace this &, we can define another array to store new cur[u]. If so, do remember to update it at line 60.
*/