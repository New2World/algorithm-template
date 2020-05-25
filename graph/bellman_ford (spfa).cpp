/*

洛谷 P3385 - 负环

*/

#include <bits/stdc++.h>

#define MAXV 2005
#define MAXE 6005
#define inf 0x3f3f3f3f

using namespace std;

struct _edge {
    int v, w, next;
    _edge(){}
    _edge(int v, int w, int next):v(v), w(w), next(next){}
};
int edges, n;
int head[MAXV];
int dis[MAXV], cnt[MAXV];
bool vis[MAXV];
_edge edge[MAXE];

void addedge(int u, int v, int w){
    edge[edges] = _edge(v, w, head[u]);
    head[u] = edges++;
}

bool spfa(int s, int n){        // TODO: SFL & LLL
    int u, v, w;
    queue<int> q;
    dis[s] = 0;
    q.push(s);
    while(!q.empty()){
        u = q.front();
        q.pop();
        vis[u] = false;
        cnt[u]++;
        for(int i = head[u];i >= 0;i = edge[i].next){
            v = edge[i].v;
            w = edge[i].w;
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
    int T, m, u, v, w;
    scanf("%d", &T);
    while(T--){
        scanf("%d %d", &n, &m);
        for(int i = 1;i <= n;i++){
            vis[i] = false;
            dis[i] = inf;
            head[i] = -1;
            cnt[i] = 0;
        }
        edges = 0;
        for(int i = 0;i < m;i++){
            scanf("%d %d %d", &u, &v, &w);
            addedge(u, v, w);
            if(w >= 0)
                addedge(v, u, w);
        }
        printf(spfa(1, n)?"NO\n":"YES\n");
    }
    return 0;
}