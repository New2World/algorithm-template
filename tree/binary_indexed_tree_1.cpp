/*

HDU 1556 - Color the Ball
区间修改, 单点查询

*/

#include <bits/stdc++.h>

#define MAXL 400005
#define lowbit(x) (x & (-x))

int C[MAXL];

int getsum(int x){
    int s = 0;
    while(x){
        s += C[x];
        x -= lowbit(x);     // 前缀和
    }
    return s;
}

int update(int x, int v, int n){
    while(x <= n){
        C[x] += v;
        x += lowbit(x);     // 更新后缀
    }
}

int main(){
    #ifndef ONLINE_JUDGE
    freopen("test.txt", "r", stdin);
    #endif
    int n, l, r;
    while(~scanf("%d", &n) && n){
        for(int i = 1;i <= n;i++)
            C[i] = 0;
        for(int i = 1;i <= n;i++){
            scanf("%d %d", &l, &r);
            update(l, 1, n);
            update(r+1, -1, n);
        }
        for(int i = 1;i <= n;i++){
            printf("%d", getsum(i));
            printf(i<n?" ":"\n");
        }
    }
    return 0;
}