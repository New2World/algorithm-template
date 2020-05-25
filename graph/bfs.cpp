/*

HDU 5285 - wyh2000 and pupil
bipartite graph detection, graph coloring with BFS

*/

#include <bits/stdc++.h>

#define MAXV 100005
#define MAXE 200005

using namespace std;

struct _edge {
    int v, next;
    _edge(){}
    _edge(int v, int next):v(v), next(next){}
};
int edges, n;
int head[MAXV];
int color[MAXV];
_edge edge[MAXE];

void init(){
    for(int i = 1;i <= n;i++)
        head[i] = -1;
}

void addedge(int u, int v){
    edge[edges] = _edge(v, head[u]);
    head[u] = edges++;
}

int bfs(){
    int u, v, g1, g2, g = 0;
    for(int i = 1;i <= n;i++){                  // 二分图不一定连通，可能有几个部分，因此累积计数
        queue<int> q;
        g1 = g2 = 0;
        if(color[i] != 0)
            continue;
        q.push(i);
        while(!q.empty()){
            u = q.front();
            q.pop();
            if(color[u] == 0){
                color[u] = 1;                   // 默认染色为 1
                g1++;                           // 染色 1 计数加 1
            }
            for(int j = head[u];j >= 0;j = edge[j].next){
                v = edge[j].v;
                if(color[v] == 0){              // 未染色的直接染不同色，并对对应计数加 1
                    color[v] = color[u]==1?2:1;
                    if(color[v] == 1)    g1++;
                    else    g2++;
                    q.push(v);
                }
                else if(color[v] == color[u])   // 相连节点染色相同，说明不是二分，返回失败
                    return -1;
            }
        }
        g += g1>g2?g2:g1;
    }
    return g;
}

int main(){
    #ifndef ONLINE_JUDGE
    freopen("test.txt", "r", stdin);
    #endif
    int T, m, u, v, g;
    scanf("%d", &T);
    while(T--){
        edges = 0;
        memset(color, 0, sizeof(color));
        scanf("%d %d", &n, &m);
        init();
        for(int i = 0;i < m;i++){
            scanf("%d %d", &u, &v);
            addedge(u, v);
            addedge(v, u);
        }
        if(n > 1 && m == 0){
            printf("%d 1\n", n-1);
            continue;
        }
        g = bfs();
        printf((g<0||n<=1)?"Poor wyh\n":"%d %d\n", n-g, g);
    }
    return 0;
}
