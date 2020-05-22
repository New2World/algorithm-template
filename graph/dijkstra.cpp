/*

HDU 2544 - 最短路

*/

#include <bits/stdc++.h>

#define MAXLEN 105
#define inf 0x3f3f3f3f

using namespace std;

struct _edge {
    int v, c;
    _edge(){}
    _edge(int v, int c):v(v), c(c){}
    inline int operator < (const _edge &cp) const {
        return c > cp.c;
    }
};

vector<_edge> graph[MAXLEN];
int dis[MAXLEN];
bool vis[MAXLEN];

void dijkstra(int s, int n){
    int v;
    dis[s] = 0;
    priority_queue<_edge> q;
    _edge e;
    q.push(_edge(s, 0));
    while(!q.empty()){
        e = q.top();
        q.pop();
        v = e.v;
        if(vis[v])  continue;
        vis[v] = true;
        for(int i = 0;i < graph[v].size();i++){
            if(!vis[graph[v][i].v] && dis[graph[v][i].v] > dis[v] + graph[v][i].c){
                dis[graph[v][i].v] = dis[v] + graph[v][i].c;
                q.push(_edge(graph[v][i].v, dis[graph[v][i].v]));
            }
        }
    }
}

int main(){
    #ifndef ONLINE_JUDGE
    freopen("test.txt", "r", stdin);
    #endif
    int n, m, u, v, c;
    while(~scanf("%d %d", &n, &m) && n){
        for(int i = 1;i <= n;i++)
            graph[i].clear();
        memset(dis, inf, sizeof(dis));
        memset(vis, false, sizeof(vis));
        for(int i = 0;i < m;i++){
            scanf("%d %d %d", &u, &v, &c);
            graph[u].push_back(_edge(v, c));
            graph[v].push_back(_edge(u, c));
        }
        dijkstra(1, n);
        printf("%d\n", dis[n]);
    }
    return 0;
}