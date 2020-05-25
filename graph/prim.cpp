/*

HDU 1879 - 继续畅通工程

*/

#include <bits/stdc++.h>

#define MAXV 105
#define MAXE 20005

using namespace std;

struct _edge {
    int v, w;
    int next;
    _edge(){}
    _edge(int v, int w, int next):v(v), w(w), next(next){}
    inline int operator < (const struct _edge &c) const {
        return w > c.w;
    }
};
int edges, n;
int neigh[MAXV], head[MAXV];
_edge edge[MAXE];

void init(){
    for(int i = 1;i <= n;i++)
        head[i] = -1;
}

void addedge(int u, int v, int w){
    edge[edges] = _edge(v, w, head[u]);
    head[u] = edges++;
}

int prim(){
    set<int> mst;
    priority_queue<_edge> pq;
    _edge t;
    int ans = 0, v, w;
    mst.insert(1);
    for(int i = head[1];i >= 0;i = edge[i].next)
        pq.push(edge[i]);
    for(int i = 0;!pq.empty() && mst.size() < n;i++){
        t = pq.top();                       // 取目前 fringe 中最短的节点
        pq.pop();
        v = t.v;
        w = t.w;
        if(mst.find(v) != mst.end())
            continue;
        mst.insert(v);
        ans += w;
        for(int j = head[v];j >= 0;j = edge[j].next)
            if(mst.find(edge[j].v) == mst.end())
                pq.push(edge[j]);                 // 每次加入为加入过的最近的节点
    }
    return ans;
}

int main(){
    #ifndef ONLINE_JUDGE
    freopen("test.txt", "r", stdin);
    #endif
    int m, u, v, w, c;
    while(~scanf("%d", &n) && n){
        m = n*(n-1)/2;
        init();
        edges = 0;
        for(int i = 0;i < m;i++){
            scanf("%d %d %d %d", &u, &v, &w, &c);
            if(c)   w = 0;                  // 将已连接的节点间的 cost 更改为 0 即可
            addedge(u, v, w);
            addedge(v, u, w);
        }
        printf("%d\n", prim());
    }
    return 0;
}
