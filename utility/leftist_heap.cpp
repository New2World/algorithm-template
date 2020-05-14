/*

HDU 1512 - Monkey King

*/

#include <bits/stdc++.h>

#define MAXLEN 100005

int arr[MAXLEN], dis[MAXLEN];
int son[MAXLEN][2], fa[MAXLEN];

int getroot(int x){
    return fa[x]<0?x:getroot(fa[x]);
}

int merge(int a, int b){
    if(a < 0)   return b;
    if(b < 0)   return a;
    int t;
    if(arr[a] < arr[b])         // 大根堆
        return merge(b, a);
    son[a][1] = merge(son[a][1], b);
    fa[son[a][1]] = a;
    if(son[a][0] < 0 || dis[son[a][0]] < dis[son[a][1]]){
        t = son[a][0];
        son[a][0] = son[a][1];
        son[a][1] = t;
    }
    dis[a] = son[a][1]<0?1:dis[son[a][1]]+1;
    return a;
}

int erase(int x){
    if(x < 0)
        return x;
    int r = x;
    arr[x] /= 2;                // 题目要求减半
    if(son[x][0] < 0)
        return -1;
    fa[son[x][0]] = fa[son[x][1]] = -1;
    x = merge(son[x][0], son[x][1]);
    son[r][0] = son[r][1] = -1; // 因为还要合并这个节点，所以需要清空左右子树
    return x;
}

int main(){
    #ifndef ONLINE_JUDGE
    freopen("test.txt", "r", stdin);
    #endif
    int n, m, x, y, a, b;
    while(~scanf("%d", &n)){
        for(int i = 0;i < n;i++){
            scanf("%d", arr+i);
            son[i][0] = son[i][1] = fa[i] = -1;
            dis[i] = 1;
        }
        scanf("%d", &m);
        for(int i = 0;i < m;i++){
            scanf("%d %d", &x, &y);
            x = getroot(--x);
            y = getroot(--y);
            if(x == y)
                printf("-1\n");
            else{
                a = erase(x);
                b = erase(y);
                x = merge(merge(a, x), merge(b, y));
                printf("%d\n", arr[x]);
            }
        }
    }
    return 0;
}