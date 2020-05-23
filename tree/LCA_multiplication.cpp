/*

洛谷 P3379 - 最近公共祖先

*/

#include <bits/stdc++.h>

#define MAXLEN 500005
#define inf 0x3f3f3f3f

using namespace std;

vector<int> graph[MAXLEN];
int fa[MAXLEN][20], dp[MAXLEN];
bool vis[MAXLEN];

int getfa(int u, int d){
    if(d == 0)  return u;
    int k = (int)log2((float)d);
    return getfa(fa[u][k], d-(1<<k));
}

int dfs(int u, int d){
    int v, mxd = d;
    dp[u] = d;
    vis[u] = true;
    for(int i = 1;(1<<i) < d;i++)
        fa[u][i] = fa[fa[u][i-1]][i-1];
    for(int i = 0;i < graph[u].size();i++){
        v = graph[u][i];
        if(vis[v])  continue;
        fa[v][0] = u;
        mxd = max(dfs(v, d+1), mxd);
    }
    return mxd;
}

int query(int u, int v, int d){
    if(dp[u] < dp[v])   swap(u, v);
    u = getfa(u, dp[u]-dp[v]);
    if(u == v)  return u;
    for(int i = (int)log2((float)d);i >= 0;i--){
        if(fa[u][i] != fa[v][i]){
            u = fa[u][i];
            v = fa[v][i];
        }
    }
    return fa[u][0];
}

int main(){
    #ifndef ONLINE_JUDGE
    freopen("test.txt", "r", stdin);
    #endif
    int r, n, q, u, v, d;
    while(~scanf("%d %d %d", &n, &q, &r)){
        for(int i = 0;i < n;i++)
            graph[i].clear();
        memset(vis, false, sizeof(vis));
        for(int i = 0;i < n-1;i++){
            scanf("%d %d", &u, &v);
            graph[u].push_back(v);
            graph[v].push_back(u);
        }
        d = dfs(r, 1);
        for(int i = 0;i < q;i++){
            scanf("%d %d", &u, &v);
            printf("%d\n", query(u, v, d));
        }
    }
    return 0;
}