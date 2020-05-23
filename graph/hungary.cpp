/*

HDU 2063 - 过山车

*/

#include <bits/stdc++.h>

#define MAXLEN 505

using namespace std;

int match[MAXLEN];
int graph[MAXLEN][MAXLEN];
int neigh[MAXLEN];
bool check[MAXLEN];

bool bipart(int u){
    int v;
    for(int i = 0;i < neigh[u];i++){
        v = graph[u][i];
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
        memset(neigh, 0, sizeof(neigh));
        memset(match, 0, sizeof(match));
        for(int i = 0;i < k;i++){
            scanf("%d %d", &u, &v);
            graph[u][neigh[u]++] = v;
        }
        printf("%d\n", getans(m));
    }
    return 0;
}
