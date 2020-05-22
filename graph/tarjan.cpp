#include <bits/stdc++.h>

#define MAXLEN 10001

using namespace std;

vector<int> graph[MAXLEN];
stack<int> st;
int dfn[MAXLEN], low[MAXLEN];
bool vis[MAXLEN];

void tarjan(int n, int u, int &cnt, int &ans){
    int v;
    dfn[u] = low[u] = ++cnt;
    st.push(u);
    vis[u] = true;
    for(int i = 0;i < graph[u].size();i++){
        v = graph[u][i];
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
    int n, m, a, b, cnt, ans;
    while(~scanf("%d %d", &n, &m) && (m+n)){
        ans = cnt = 0;
        memset(dfn, 0, sizeof(dfn));
        memset(low, 0, sizeof(low));
        memset(vis, 0, sizeof(vis));
        while(!st.empty())
            st.pop();
        for(int i = 1;i <= n;i++)
            graph[i].clear();
        for(int i = 0;i < m;i++){
            scanf("%d %d", &a, &b);
            graph[a].push_back(b);
        }
        tarjan(n, 1, cnt, ans);
        printf((ans==1&&cnt==n)?"Yes\n":"No\n");
    }
    return 0;
}