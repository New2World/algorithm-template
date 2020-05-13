/*

HDU 1711 - Number Sequence

*/

#include <bits/stdc++.h>

#define MAXLEN 1000005

int a[MAXLEN], b[MAXLEN];
int next[MAXLEN];

void getnext(int m){
    int pa = -1, pb = 0;
    next[0] = -1;
    while(pa < m && pb < m){
        if(pa < 0 || b[pa] == b[pb])
            next[++pb] = ++pa;
        else
            pa = next[pa];
    }
}

int kmp(int n, int m){
    int pa = 0, pb = 0;
    while(pa < n && pb < m){
        if(pb < 0 || a[pa] == b[pb])
            ++pa, ++pb;
        else
            pb = next[pb];
    }
    return pb==m?pa-m+1:-1;
}

int main(){
    #ifndef ONLINE_JUDGE
    freopen("test.txt", "r", stdin);
    #endif
    int T, n, m;
    scanf("%d", &T);
    while(T--){
        scanf("%d %d", &n, &m);
        for(int i = 0;i < n;i++)
            scanf("%d", a+i);
        for(int i = 0;i < m;i++)
            scanf("%d", b+i);
        getnext(m);
        printf("%d\n", kmp(n, m));
    }
    return 0;
}