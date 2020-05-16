/*

HDU 1863 - 畅通工程

*/

#include <bits/stdc++.h>

#define MAXLEN 105

using namespace std;

typedef struct _edge {
    int v, w;
    _edge(){}
    _edge(int v, int w):v(v), w(w){}
    inline int operator < (const struct _edge &c) const {
        return w > c.w;
    }
} edge;

int graph[MAXLEN][MAXLEN][2];
int neigh[MAXLEN];

int prim(int n, int m, int st){
    set<int> mst;
    priority_queue<edge> pq;
    edge e;
    int ans = 0;
    mst.insert(st);
    for(int i = 0;i < neigh[st];i++)
        pq.push(edge(graph[st][i][0], graph[st][i][1]));
    for(int i = 0;!pq.empty() && mst.size() < m;i++){
        e = pq.top();
        pq.pop();
        if(mst.find(e.v) != mst.end())
            continue;
        mst.insert(e.v);
        ans += e.w;
        for(int j = 0;j < neigh[e.v];j++)
            if(mst.find(graph[e.v][j][0]) == mst.end())
                pq.push(edge(graph[e.v][j][0], graph[e.v][j][1]));
    }
    return mst.size()==m?ans:-1;
}

int main(){
    #ifndef ONLINE_JUDGE
    freopen("test.txt", "r", stdin);
    #endif
    int n, m, u, v, w, ans;
    while(~scanf("%d %d", &n, &m) && n){
        memset(neigh, 0, sizeof(neigh));
        for(int i = 0;i < n;i++){
            scanf("%d %d %d", &u, &v, &w);
            graph[u][neigh[u]][0] = v;
            graph[u][neigh[u]++][1] = w;
            graph[v][neigh[v]][0] = u;
            graph[v][neigh[v]++][1] = w;
        }
        ans = prim(n, m, u);
        printf(ans<0?"?\n":"%d\n", ans);
    }
    return 0;
}