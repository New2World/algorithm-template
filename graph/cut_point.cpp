/*

洛谷 P3388 - 割点

*/

#include <bits/stdc++.h>

#define MAXV 20005
#define MAXE 200005

using namespace std;

struct _edge {
    int v, next;
    _edge(){}
    _edge(int v, int next):v(v), next(next){}
};
int edges, nodes;
int now;
int head[MAXV];
int dfn[MAXV], low[MAXV];
bool vis[MAXV];
_edge edge[MAXE];
vector<int> cut;

void init(){
    now = 1;
    cut.clear();
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
    int v, child = 0;
    dfn[u] = low[u] = now++;
    vis[u] = true;
    for(int i = head[u];i >= 0;i = edge[i].next){
        v = edge[i].v;
        if(!dfn[v]){
            child++;
            tarjan(v, u);
            low[u] = min(low[u], low[v]);
            if((child > 1 && u == root) || (u != root && low[v] >= dfn[u]))
                cut.push_back(u);
        }
        else
            low[u] = min(low[u], dfn[v]);
        
    }
}

void printcut(){
    int n;
    sort(cut.begin(), cut.end());
    printf("%d\n", n=unique(cut.begin(), cut.end())-cut.begin());
    for(int i = 0;i < n;i++)
        printf(i?" %d":"%d", cut[i]);
    putchar('\n');
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
        printcut();
    }
    return 0;
}