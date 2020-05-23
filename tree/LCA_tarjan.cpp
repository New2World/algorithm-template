/*

HDU 2586 - How Far Away?

*/

#include <bits/stdc++.h>

#define MAXLEN 40005
#define inf 0x3f3f3f3f

using namespace std;

vector<pair<int,int> > graph[MAXLEN], query[MAXLEN];
int fa[MAXLEN], dis[MAXLEN];
int ans[200];
bool vis[MAXLEN];

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
    for(int i = 0;i < graph[u].size();i++){
        v = graph[u][i].first;
        w = graph[u][i].second;
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
        for(int i = 0;i < n;i++){
            graph[i].clear();
            query[i].clear();
            dis[i] = 0;
            fa[i] = i;
        }
        for(int i = 0;i < n-1;i++){
            scanf("%d %d %d", &u, &v, &w);
            graph[u].push_back(make_pair(v, w));
            graph[v].push_back(make_pair(u, w));
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