/*

HDU 2063 - 过山车

A more interesting explanation of Hungarian algorithm: https://blog.csdn.net/dark_scope/article/details/8880547

*/

#include <bits/stdc++.h>

#define MAXV 505
#define MAXE 1005

using namespace std;

struct _edge {
    int v, next;
    _edge(){}
    _edge(int v, int next):v(v), next(next){}
};
int edges;
int match[MAXV];
int head[MAXV];
bool check[MAXV];
_edge edge[MAXE];

void init(int n){
    for(int i = 1;i <= n;i++)
        head[i] = -1;
}

void addedge(int u, int v){
    edge[edges] = _edge(v, head[u]);
    head[u] = edges++;
}

bool bipart(int u){
    int v;
    for(int i = head[u];i >= 0;i = edge[i].next){
        v = edge[i].v;
        if(!check[v]){
            check[v] = true;                            // 标记为已考察
            if(match[v] == 0 || bipart(match[v])){      // 当前点还没有匹配过 或 匹配过但可以换一个匹配对象
                match[v] = u;
                return true;
            }
        }
    }
    return false;
}

int getans(int m){
    int ans = 0;
    for(int i = 1;i <= m;i++){
        // getans 函数确定待匹配的节点 i，由 bipart 函数判断该节点的匹配是否能被成功加入
        // 因此 check 是被 bipart 使用的而不影响 getans，所以对每个待匹配节点清空
        memset(check, false, sizeof(check));
        if(bipart(i))
            ans++;
    }
    return ans;
}

int main(){
    #ifndef ONLINE_JUDGE
    freopen("test.txt", "r", stdin);
    #endif
    int k, m, n, u, v;
    while(~scanf("%d %d %d", &k, &m, &n) && k){
        init(n);
        edges = 0;
        memset(match, 0, sizeof(match));
        for(int i = 0;i < k;i++){
            scanf("%d %d", &u, &v);
            addedge(u, v);
        }
        printf("%d\n", getans(m));
    }
    return 0;
}
