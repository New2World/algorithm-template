/*

HDU 1698 - Just a hook

*/

#include <cstdio>
#include <algorithm>

#define MAXL 400005
#define mid(l, r) ((l+r)>>1)
#define lr(rt) ((rt<<1)+1)
#define rr(rt) ((rt<<1)+2)

using namespace std;

typedef struct _seg {
    int l, r;
    int z;
    int sum;
} _seg;

_seg seg[MAXL];
// int arr[MAXL];

int _mid(int rt){
    return mid(seg[rt].l, seg[rt].r);
}

void pushup(int rt){
    seg[rt].sum = seg[lr(rt)].sum + seg[rr(rt)].sum;
}

void pushdown(int rt){
    if(seg[rt].z){
        seg[lr(rt)].z = seg[rt].z;
        seg[rr(rt)].z = seg[rt].z;
        seg[lr(rt)].sum = seg[rt].z * (seg[lr(rt)].r - seg[lr(rt)].l + 1);
        seg[rr(rt)].sum = seg[rt].z * (seg[rr(rt)].r - seg[rr(rt)].l + 1);
        seg[rt].z = 0;
    }
}

void update(int l, int r, int rt, int v){
    if(l > r)   return;
    if(seg[rt].l == l && seg[rt].r == r){
        seg[rt].z = v;
        seg[rt].sum = v * (seg[rt].r - seg[rt].l + 1);
        return;
    }
    pushdown(rt);
    int m = _mid(rt);
    if(l > m)
        update(l, r, rr(rt), v);
    else if(r <= m)
        update(l, r, lr(rt), v);
    else{
        update(l, m, lr(rt), v);
        update(m+1, r, rr(rt), v);
    }
    pushup(rt);
}

int query(int l, int r, int rt){
    if(seg[rt].l == seg[rt].r && seg[rt].l == l)
        return seg[rt].sum;
    pushdown(rt);
    int m = _mid(rt);
    if(r <= m)
        return query(l, r, lr(rt));
    else if(l > m)
        return query(l, r, rr(rt));
    return query(l, m, lr(rt))+query(m+1, r, rr(rt));
}

void build(int l, int r, int rt){
    if(l > r)   return;
    seg[rt].l = l;
    seg[rt].r = r;
    seg[rt].z = 0;
    if(l == r){
        seg[rt].sum = 1;    // arr[l]
        return;
    }
    int m = mid(l, r);
    build(l, m, lr(rt));
    build(m+1, r, rr(rt));
    pushup(rt);
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