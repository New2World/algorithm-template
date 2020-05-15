/*

HDU 21863 - 畅通工程

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

int main(){
    #ifndef ONLINE_JUDGE
    freopen("test.txt", "r", stdin);
    #endif
    int n, m, u, v, w, ans;
    int e;
    while(~scanf("%d %d", &n, &m) && n){
        ans = 0;
        e = 0;
        for(int i = 0;i <= m;i++)
            uni[i] = i;
        for(int i = 0;i < n;i++){
            scanf("%d %d %d", &u, &v, &w);
            arr[i].u = u>v?v:u;
            arr[i].v = u>v?u:v;
            arr[i].w = w;
        }
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
        printf(e!=m-1?"?\n":"%d\n", ans);
    }
    return 0;
}