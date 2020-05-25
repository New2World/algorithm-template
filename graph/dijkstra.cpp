/*

HDU 2544 - 最短路

*/

#include <bits/stdc++.h>

#define MAXV 105
#define MAXE 20005
#define inf 0x3f3f3f3f

using namespace std;

struct _edge {
    int v, w;
    int next;
    _edge(){}
    _edge(int v, int w, int next):v(v), w(w), next(next){}
    inline int operator < (const _edge &cp) const {
        return w > cp.w;
    }
};

int edges, n;
int dis[MAXV], head[MAXV];
_edge edge[MAXE];
bool vis[MAXV];

void init(){
    for(int i = 1;i <= n;i++)
        head[i] = -1;
}

void addedge(int u, int v, int w){
    edge[edges] = _edge(v, w, head[u]);
    head[u] = edges++;
}

void dijkstra(int s, int n){
    int u, v, w;
    dis[s] = 0;
    priority_queue<_edge> q;
    _edge e;
    q.push(_edge(s, 0, 0));
    while(!q.empty()){
        e = q.top();            // 所有 dis 中距离最短的节点
        q.pop();
        u = e.v;
        if(vis[u])  continue;
        vis[u] = true;
        for(int i = head[u];i >= 0;i = edge[i].next){
            v = edge[i].v;
            w = edge[i].w;
            if(!vis[v] && dis[v] > dis[u] + w){
                dis[v] = dis[u] + w;
                q.push(_edge(v, dis[v], 0));
            }
        }
    }
}

int main(){
    #ifndef ONLINE_JUDGE
    freopen("test.txt", "r", stdin);
    #endif
    int m, u, v, w;
    while(~scanf("%d %d", &n, &m) && n){
        init();
        edges = 0;
        memset(dis, inf, sizeof(dis));
        memset(vis, false, sizeof(vis));
        for(int i = 0;i < m;i++){
            scanf("%d %d %d", &u, &v, &w);
            addedge(u, v, w);
            addedge(v, u, w);
        }
        dijkstra(1, n);
        printf("%d\n", dis[n]);
    }
    return 0;
}