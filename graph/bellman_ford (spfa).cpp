/*

洛谷 P3385 - 负环

*/

#include <bits/stdc++.h>

#define MAXLEN 500005
#define inf 0x3f3f3f3f

using namespace std;

vector<pair<int,int> > graph[MAXLEN];
int dis[MAXLEN], cnt[MAXLEN];
bool vis[MAXLEN];

bool bellmanford(int s, int n){
    int u, v, w;
    queue<int> q;
    dis[s] = 0;
    q.push(s);
    while(!q.empty()){
        u = q.front();
        q.pop();
        vis[u] = false;
        cnt[u]++;
        for(int i = 0;i < graph[u].size();i++){
            v = graph[u][i].first;
            w = graph[u][i].second;
            if(dis[v] > dis[u] + w){
                dis[v] = dis[u] + w;
                if(cnt[v] >= n) return false;
                if(!vis[v]){
                    q.push(v);
                    vis[v] = true;
                }
            }
        }
    }
    return true;
}

int main(){
    #ifndef ONLINE_JUDGE
    freopen("test.txt", "r", stdin);
    #endif
    int T, n, m, u, v, w;
    scanf("%d", &T);
    while(T--){
        scanf("%d %d", &n, &m);
        for(int i = 1;i <= n;i++){
            graph[i].clear();
            vis[i] = false;
            dis[i] = inf;
            cnt[i] = 0;
        }
        for(int i = 0;i < m;i++){
            scanf("%d %d %d", &u, &v, &w);
            graph[u].push_back(make_pair(v, w));
            if(w >= 0)
                graph[v].push_back(make_pair(u, w));
        }
        printf(bellmanford(1, n)?"NO\n":"YES\n");
    }
    return 0;
}