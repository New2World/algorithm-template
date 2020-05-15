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
            check[v] = true;
            if(match[v] == 0 || bipart(match[v])){
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