#pragma once
#include <memory.h>

#define MAXLEN 100005

class _Graph{
protected:
    typedef struct _edge{
        int u, v, cap, cost;
        int next;
    } _edge;

    int n_edge, n_node;
    int head[MAXLEN];
    _edge edge[MAXLEN];
public:
    _Graph(int);
    void addEdge(int, int, int, int, bool=false);
};

_Graph::_Graph(int n){
    n_edge = 0;
    n_node = n;
    memset(head, -1, sizeof(head));
}

void _Graph::addEdge(int u, int v, int cap, int cost, bool dual){
    edge[n_edge] = {u, v, cap, cost, head[u]};
    head[u] = n_edge++;
    if(dual){
        edge[n_edge] = {v, u, 0, cost, head[v]};
        head[v] = n_edge++;
    }
}