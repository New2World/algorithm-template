/*

HDU 1269 - 迷宫城堡

*/

#include <bits/stdc++.h>

#define MAXV 10001
#define MAXE 100001

using namespace std;

struct _edge{
    int v, next;
    _edge(){}
    _edge(int v, int next):v(v), next(next){}
};
stack<int> st;
int edges, n;
int head[MAXV];
int dfn[MAXV], low[MAXV];
bool vis[MAXV];
_edge edge[MAXE];

void init(){
    for(int i = 1;i <= n;i++)
        head[i] = -1;
}

void addedge(int u, int v){
    edge[edges] = _edge(v, head[u]);
    head[u] = edges++;
}

void tarjan(int n, int u, int &cnt, int &ans){
    int v;
    dfn[u] = low[u] = ++cnt;
    st.push(u);
    vis[u] = true;
    for(int i = head[u];i >= 0;i = edge[i].next){
        v = edge[i].v;
        if(!dfn[v]){
            tarjan(n, v, cnt, ans);
            low[u] = min(low[u], low[v]);
        }
        else if(vis[v])
            low[u] = min(low[u], dfn[v]);
    }
    if(low[u] == dfn[u]){
        ans++;
        do{
            v = st.top();
            st.pop();
            vis[v] = false;
        }while(v != u);
    }
}

int main(){
    #ifndef ONLINE_JUDGE
    freopen("test.txt", "r", stdin);
    #endif
    int m, a, b, cnt, ans;
    while(~scanf("%d %d", &n, &m) && (m+n)){
        init();
        edges = 0;
        ans = cnt = 0;
        memset(dfn, 0, sizeof(dfn));
        memset(low, 0, sizeof(low));
        memset(vis, 0, sizeof(vis));
        while(!st.empty())
            st.pop();
        for(int i = 0;i < m;i++){
            scanf("%d %d", &a, &b);
            addedge(a, b);
        }
        tarjan(n, 1, cnt, ans);
        printf((ans==1&&cnt==n)?"Yes\n":"No\n");
    }
    return 0;
}