/*

洛谷 T103481 - 割边

*/

#include <bits/stdc++.h>

#define MAXV 50005
#define MAXE 600005

using namespace std;

struct _edge {
    int v, next;
    _edge(){}
    _edge(int v, int next):v(v), next(next){}
};
int edges, nodes;
int now, cut;
int head[MAXV];
int dfn[MAXV], low[MAXV];
bool vis[MAXV];
_edge edge[MAXE];

void init(){
    now = 1;
    cut = 0;
    for(int i = 0;i < MAXV;i++){
        dfn[i] = 0;
        head[i] = -1;
        vis[i] = false;
    }
}

void addedge(int u, int v){
    edge[edges] = _edge(v, head[u]);
    head[u] = edges++;
}

void tarjan(int u, int root){
    int v;
    dfn[u] = low[u] = now++;
    vis[u] = true;
    for(int i = head[u];i >= 0;i = edge[i].next){
        v = edge[i].v;
        if(!dfn[v]){
            tarjan(v, u);
            low[u] = min(low[u], low[v]);
            if(low[v] > dfn[u])
                cut++;
        }
        else if(v != root)
            low[u] = min(low[u], dfn[v]);
        
    }
}

int main(){
    #ifndef ONLINE_JUDGE
    freopen("test.txt", "r", stdin);
    #endif
    int m, u, v;
    while(~scanf("%d %d", &nodes, &m)){
        init();
        for(int i = 0;i < m;i++){
            scanf("%d %d", &u, &v);
            addedge(u, v);
            addedge(v, u);
        }
        for(int i = 1;i <= nodes;i++){
            if(vis[i])  continue;
            tarjan(i, i);
        }
        printf("%d\n", cut);
    }
    return 0;
}