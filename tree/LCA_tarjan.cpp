/*

HDU 2586 - How Far Away?

*/

#include <bits/stdc++.h>

#define MAXV 40005
#define MAXE 80005
#define inf 0x3f3f3f3f

using namespace std;

struct _edge {
    int v, w, next;
    _edge(){}
    _edge(int v, int w, int next):v(v), w(w), next(next){}
};
vector<pair<int,int> > query[MAXV];
int edges, n;
int fa[MAXV], dis[MAXV];
int head[MAXV];
int ans[200];
bool vis[MAXV];
_edge edge[MAXE];

void init(){
    for(int i = 1;i <= n;i++)
        head[i] = -1;
}

void addedge(int u, int v, int w){
    edge[edges] = _edge(v, w, head[u]);
    head[u] = edges++;
}

int getfa(int x){
    int y = x, t;
    while(y != fa[y])
        y = fa[y];
    while(x != y){
        t = fa[x];
        fa[x] = y;
        x = t;
    }
    return x;
}

void dfs(int u){
    if(vis[u])
        return;
    vis[u] = true;
    int v, w, f;
    for(int i = 0;i < query[u].size();i++){
        v = query[u][i].first;
        w = query[u][i].second;
        if(!vis[v]) continue;
        f = getfa(v);
        ans[w] = dis[u] + dis[v] - 2 * dis[f];
    }
    for(int i = head[u];i >= 0;i = edge[i].next){
        v = edge[i].v;
        w = edge[i].w;
        if(vis[v])  continue;
        dis[v] = dis[u] + w;
        dfs(v);
        fa[v] = u;
    }
}

int main(){
    #ifndef ONLINE_JUDGE
    freopen("test.txt", "r", stdin);
    #endif
    int T, n, q, u, v, w;
    scanf("%d", &T);
    while(T--){
        scanf("%d %d", &n, &q);
        edges = 0;
        for(int i = 1;i <= n;i++){
            query[i].clear();
            head[i] = -1;
            dis[i] = 0;
            fa[i] = i;
        }
        for(int i = 0;i < n-1;i++){
            scanf("%d %d %d", &u, &v, &w);
            addedge(u, v, w);
            addedge(v, u, w);
        }
        for(int i = 0;i < q;i++){
            scanf("%d %d", &u, &v);
            query[u].push_back(make_pair(v, i));
            query[v].push_back(make_pair(u, i));
        }
        memset(vis, false, sizeof(vis));
        dfs(1);
        for(int i = 0;i < q;i++)
            printf("%d\n", ans[i]);
    }
    return 0;
}