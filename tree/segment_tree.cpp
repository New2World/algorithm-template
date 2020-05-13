/*

HDU 1698 - Just a Hook

*/

#include <bits/stdc++.h>

#define MAXL 400005
#define lc(rt) ((rt<<1)+1)
#define rc(rt) ((rt<<1)+2)

typedef struct _seg {
    int l, r;
    int z;
    int sum;
} _seg;

_seg seg[MAXL];

inline int mid(int l, int r){
    return (l+r)>>1;
}

inline int mid(int rt){
    return mid(seg[rt].l, seg[rt].r);
}

void pushup(int rt){
    seg[rt].sum = seg[lc(rt)].sum + seg[rc(rt)].sum;
}

void pushdown(int rt){
    if(seg[rt].z){
        seg[lc(rt)].z = seg[rt].z;
        seg[rc(rt)].z = seg[rt].z;
        seg[lc(rt)].sum = seg[rt].z * (seg[lc(rt)].r - seg[lc(rt)].l + 1);
        seg[rc(rt)].sum = seg[rt].z * (seg[rc(rt)].r - seg[rc(rt)].l + 1);
        seg[rt].z = 0;
    }
}

void update(int l, int r, int rt, int v){
    if(l > r)   return;
    if(seg[rt].l == l && seg[rt].r == r){
        seg[rt].z = v;
        // 进入这个条件后不会 pushdown，因此需要手动更新
        seg[rt].sum = v * (seg[rt].r - seg[rt].l + 1);
        return;
    }
    pushdown(rt);       // 先把 lazy 下放
    int m = mid(rt);
    if(l > m)
        update(l, r, rc(rt), v);
    else if(r <= m)
        update(l, r, lc(rt), v);
    else{
        update(l, m, lc(rt), v);
        update(m+1, r, rc(rt), v);
    }
    pushup(rt);         // 更新子树后回来更新当前节点
}

int query(int l, int r, int rt){
    if(seg[rt].l == seg[rt].r && seg[rt].l == l)
        return seg[rt].sum;
    pushdown(rt);       // 查询时也要先下放
    int m = mid(rt);
    if(r <= m)
        return query(l, r, lc(rt));
    else if(l > m)
        return query(l, r, rc(rt));
    return query(l, m, lc(rt)) + query(m+1, r, rc(rt));
}

void build(int l, int r, int rt){
    if(l > r)   return;
    seg[rt].l = l;
    seg[rt].r = r;
    seg[rt].z = 0;
    if(l == r){
        seg[rt].sum = 1;
        return;
    }
    int m = mid(l, r);
    build(l, m, lc(rt));
    build(m+1, r, rc(rt));
    pushup(rt);         // 自底向上更新节点信息
}

int main(){
    #ifndef ONLINE_JUDGE
    freopen("test.txt", "r", stdin);
    #endif
    int T, n, q, l, r, v;
    scanf("%d", &T);
    for(int x = 1;x <= T;x++){
        scanf("%d", &n);
        build(0, n-1, 0);
        scanf("%d", &q);
        for(int i = 0;i < q;i++){
            scanf("%d %d %d", &l, &r, &v);
            update(l-1, r-1, 0, v);
        }
        printf("Case %d: The total value of the hook is %d.\n", x, query(0, n-1, 0));
    }
    return 0;
}