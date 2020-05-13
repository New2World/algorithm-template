/*

HDU 1166 - 敌兵布阵
单点修改, 区间查询

*/

#include <bits/stdc++.h>

#define MAXLEN 50005
#define lowbit(x) (x&(-x))

using namespace std;

int C[MAXLEN];

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
    int t, n, l, r, v;
    string op;
    scanf("%d", &t);
    for(int ca = 1;ca <= t;ca++){
        for(int i = 0;i < MAXLEN;i++)
            C[i] = 0;
        scanf("%d", &n);
        for(int i = 1;i <= n;i++){
            scanf("%d", &v);
            update(i, v, n);
        }
        printf("Case %d:\n", ca);
        while(cin >> op && op[0] != 'E'){
            scanf("%d %d", &l, &r);
            if(op[0] == 'Q')
                printf("%d\n", getsum(r)-getsum(l-1));
            else if(op[0] == 'A')
                update(l, r, n);
            else if(op[0] == 'S')
                update(l, -r, n);
        }
    }
    return 0;
}