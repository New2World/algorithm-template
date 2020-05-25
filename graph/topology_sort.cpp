/*

HDU 4857 - 逃生

*/

#include <bits/stdc++.h>

#define MAXV 30005
#define MAXE 100005

using namespace std;

struct _edge {
    int v, next;
    _edge(){}
    _edge(int v, int next):v(v), next(next){}
};
int edges, n;
int head[MAXV], neigh[MAXV];
int ans[MAXV];
_edge edge[MAXE];

void init(){
    for(int i = 1;i <= n;i++)
        head[i] = -1;
}

void addedge(int u, int v){
    edge[edges] = _edge(v, head[u]);
    head[u] = edges++;
}

void topologysort(){
    int ptr = 0, u, v, pre = -1;
    priority_queue<int> q;              // 因为题目要求要默认升序，在反向拓扑时就变成了降序
    for(int i = 1;i <= n;i++)
        if(!neigh[i])                   // 初始化，压入所有入度为 0 的点
            q.push(i);
    while(!q.empty()){
        u = q.top();
        q.pop();
        if(u == pre)    continue;
        pre = u;
        ans[ptr++] = u;
        for(int i = head[u];i >= 0;i = edge[i].next){
            v = edge[i].v;
            if(!--neigh[v])             // 将邻接的点的入度减 1，如果减为 0 则压入队列
                q.push(v);
        }
    }
}

int main(){
    #ifndef ONLINE_JUDGE
    freopen("test.txt", "r", stdin);
    #endif
    int T, m, a, b;
    scanf("%d", &T);
    while(T--){
        memset(neigh, 0, sizeof(neigh));
        scanf("%d %d", &n, &m);
        init();
        edges = 0;
        for(int i = 0;i < m;i++){
            scanf("%d %d", &a, &b);
            addedge(b, a);                  // 题目要求潜台词是没在输入的都得在后面，且默认升序
            neigh[a]++;                     // 因此使用逆向拓扑，即没在输入的入度都为 0，先处理
        }
        topologysort();
        for(int i = n-1;i >= 0;i--)
            printf(i?"%d ":"%d", ans[i]);
        putchar('\n');
    }
}
