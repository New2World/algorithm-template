/*

HDU 5285 - wyh2000 and pupil
bipartite graph detection, graph coloring with BFS

*/

#include <bits/stdc++.h>

#define MAXLEN 100005

using namespace std;

int color[MAXLEN];
map<int,vector<int> > graph;

int bfs(){
    int u, g1, g2, g = 0;
    vector<int> neigh;
    map<int,vector<int> >::iterator it = graph.begin();
    for(;it != graph.end();it++){
        queue<int> q;
        u = it->first;
        if(color[u] != 0)
            continue;
        g1 = g2 = 0;
        q.push(u);
        while(!q.empty()){
            u = q.front();
            q.pop();
            neigh = graph[u];
            if(color[u] == 0){
                color[u] = 1;
                g1++;
            }
            for(int i = 0;i < neigh.size();i++){
                if(color[neigh[i]] == 0){
                    color[neigh[i]] = color[u]==1?2:1;
                    if(color[neigh[i]] == 1)    g1++;
                    else    g2++;
                    q.push(neigh[i]);
                }
                else if(color[neigh[i]] == color[u])
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
    int T, n, m, u, v, g;
    scanf("%d", &T);
    while(T--){
        memset(color, 0, sizeof(color));
        graph.clear();
        scanf("%d %d", &n, &m);
        for(int i = 0;i < m;i++){
            scanf("%d %d", &u, &v);
            if(graph.find(u) == graph.end())
                graph[u] = vector<int>();
            graph[u].push_back(v);
            if(graph.find(v) == graph.end())
                graph[v] = vector<int>();
            graph[v].push_back(u);
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