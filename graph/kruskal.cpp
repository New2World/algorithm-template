/*

HDU 1863 - 畅通工程

在 HDU 1879 中，部分节点已经连接。
此时再做 MST 的话只需将已连接的节点间的 cost 更改为 0 即可。

*/

#include <bits/stdc++.h>

#define MAXLEN 105

using namespace std;

typedef struct _edge {
    int u, v;
    int w;
    inline int operator < (const struct _edge &c) const {
        return w < c.w;
    }
} edge;

int uni[MAXLEN];
edge arr[MAXLEN];

int getuni(int a){
    int root = a, t;
    while(uni[a] != a)
        a = uni[a];
    while(uni[root] != root){
        t = uni[root];
        uni[root] = a;
        root = t;
    }
    return a;
}

bool duplicate(const int &a, const int &b){
    if(arr[a].u == arr[b].u && arr[a].v == arr[b].v)
        return true;
    return false;
}

int kruskal(int n, int m){
    int ans = 0, e = 0;
    int u, v;
    sort(arr, arr+n);
    for(int i = 0;i < n;i++){
        if(i > 0 && duplicate(i-1, i))
            continue;
        u = getuni(arr[i].u);
        v = getuni(arr[i].v);
        if(u != v){
            uni[v] = u;
            ans += arr[i].w;
            e++;
        }
    }
    return e==m-1?ans:-1;
}

int main(){
    #ifndef ONLINE_JUDGE
    freopen("test.txt", "r", stdin);
    #endif
    int n, m, u, v, w, ans;
    while(~scanf("%d %d", &n, &m) && n){
        for(int i = 0;i <= m;i++)
            uni[i] = i;
        for(int i = 0;i < n;i++){
            scanf("%d %d %d", &u, &v, &w);
            arr[i].u = u>v?v:u;
            arr[i].v = u>v?u:v;
            arr[i].w = w;
        }
        ans = kruskal(n, m);
        printf(ans<0?"?\n":"%d\n", ans);
    }
    return 0;
}
