/*

HDU 1856 - More is Better

*/

#include <bits/stdc++.h>

#define MAXLEN 10000005

int parent[MAXLEN], num[MAXLEN];

int init(){
    for(int i = 0;i < MAXLEN;i++){
        parent[i] = i;
        num[i] = 1;
    }
}

int getParent(const int &a){
    int p = a;
    while(p != parent[p])
        p = parent[p];
    parent[a] = p;
    return p;
}

int combine(int a, int b){
    int pa = getParent(a);
    int pb = getParent(b);
    if(pa != pb)
        num[pa] += num[pb];
    parent[pb] = pa;
    return pa;
}

int main(){
    #ifndef ONLINE_JUDGE
    freopen("test.txt", "r", stdin);
    #endif
    int n, u, v, ans, p;
    while(~scanf("%d", &n)){
        init();
        ans = 1;
        for(int i = 0;i < n;i++){
            scanf("%d %d", &u, &v);
            p = combine(u, v);
            if(num[p] > ans)
                ans = num[p];
        }
        printf("%d\n", ans);
    }
    return 0;
}