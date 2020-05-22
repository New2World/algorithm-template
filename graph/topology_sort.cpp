/*

HDU 4857 - 逃生

*/

#include <bits/stdc++.h>

#define MAXLEN 100005

using namespace std;

vector<int> graph[MAXLEN];
int neigh[MAXLEN];
int ans[MAXLEN];

void topologysort(int n){
    int ptr = 0, u, pre = -1;
    priority_queue<int> q;
    for(int i = 1;i <= n;i++)
        if(!neigh[i])
            q.push(i);
    while(!q.empty()){
        u = q.top();
        q.pop();
        if(u == pre)    continue;
        pre = u;
        ans[ptr++] = u;
        for(int i = 0;i < graph[u].size();i++)
            if(!--neigh[graph[u][i]])
                q.push(graph[u][i]);
    }
}

int main(){
    #ifndef ONLINE_JUDGE
    freopen("test.txt", "r", stdin);
    #endif
    int T, n, m, a, b;
    scanf("%d", &T);
    while(T--){
        memset(neigh, 0, sizeof(neigh));
        scanf("%d %d", &n, &m);
        for(int i = 0;i < m;i++){
            scanf("%d %d", &a, &b);
            graph[b].push_back(a);
            neigh[a]++;
        }
        topologysort(n);
        for(int i = n-1;i >= 0;i--)
            printf(i?"%d ":"%d", ans[i]);
        putchar('\n');
        for(int i = 1;i <= n;i++)
            graph[i].clear();
    }
}