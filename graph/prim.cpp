/*

HDU 1879 - 继续畅通工程

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

int prim(int n){
    set<int> mst;
    priority_queue<edge> pq;
    edge e;
    int ans = 0;
    mst.insert(1);
    for(int i = 0;i < neigh[1];i++)
        pq.push(edge(graph[1][i][0], graph[1][i][1]));
    for(int i = 0;!pq.empty() && mst.size() < n;i++){
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
    return ans;
}

int main(){
    #ifndef ONLINE_JUDGE
    freopen("test.txt", "r", stdin);
    #endif
    int n, m, u, v, w, c;
    while(~scanf("%d", &n) && n){
        m = n*(n-1)/2;
        memset(neigh, 0, sizeof(neigh));
        for(int i = 0;i < m;i++){
            scanf("%d %d %d %d", &u, &v, &w, &c);
            if(c)   w = 0;                  // 将已连接的节点间的 cost 更改为 0 即可
            graph[u][neigh[u]][0] = v;
            graph[u][neigh[u]++][1] = w;
            graph[v][neigh[v]][0] = u;
            graph[v][neigh[v]++][1] = w;
        }
        printf("%d\n", prim(n));
    }
    return 0;
}