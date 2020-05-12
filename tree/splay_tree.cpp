/*

HDU 1890 - Robotic sort

*/

#include <cstdio>
#include <algorithm>

#define MAXLEN 10000005

using namespace std;

typedef struct _arr{
    int v, id;
    inline int operator < (const struct _arr &c) const {
        if(c.v == v)
            return id < c.id;
        return v < c.v;
    }
} _arr;

int root;
int fa[MAXLEN];
int son[MAXLEN][2];
int siz[MAXLEN];
bool lazy[MAXLEN];
_arr arr[MAXLEN];

void pushup(int x){
    siz[x] = 1;
    if(son[x][0] >= 0)
        siz[x] += siz[son[x][0]];
    if(son[x][1] >= 0)
        siz[x] += siz[son[x][1]];
}

void pushdown(int x){
    int l = son[x][0], r = son[x][1];
    int t;
    if(lazy[x]){
        lazy[x] = false;
        lazy[l] ^= true;
        lazy[r] ^= true;
        t = son[x][0];
        son[x][0] = son[x][1];
        son[x][1] = t;
    }
}

void rotate(int x){
    int f = fa[x], g = fa[fa[x]];
    int sn = son[f][0]==x?0:1;
    son[f][sn] = son[x][!sn];
    fa[son[x][!sn]] = f;
    son[x][!sn] = f;
    fa[f] = x;
    fa[x] = g;
    if(fa[x] >= 0)
        son[g][son[g][0]==f?0:1] = x;
    pushup(f);
    pushup(x);
}

void splay(int x){
    int f, g;
    while(fa[x] >= 0){
        f = fa[x];
        g = fa[f];
        pushdown(g);
        pushdown(f);
        pushdown(x);
        if(fa[fa[x]] < 0)
            rotate(x);
        else{
            if(son[g][0] == f && son[f][0] == x)
                rotate(f), rotate(x);
            else if(son[g][0] == f && son[f][1] == x)
                rotate(x), rotate(x);
            else if(son[g][1] == f && son[f][1] == x)
                rotate(f), rotate(x);
            else if(son[g][1] == f && son[f][0] == x)
                rotate(x), rotate(x);
        }
    }
}

int findmax(int x){
    if(x < 0)   return x;
    pushdown(x);
    while(son[x][1] >= 0){
        x = son[x][1];
        pushdown(x);
    }
    return x;
}

void erase(int x){
    splay(x);
    int m = findmax(son[x][0]);
    int l = son[x][0], r = son[x][1];
    if(m < 0){
        fa[r] = -1;
        son[x][1] = -1;
        pushup(r);
    }
    else{
        son[m][1] = r;
        fa[r] = m;
        fa[l] = -1;
        pushup(m);
        splay(m);
    }
}

int build(int l, int r, int rt=-1){
    if(l >= r)  return -1;
    int m = (l+r) >> 1;
    fa[m] = rt;
    son[m][0] = build(l, m, m);
    son[m][1] = build(m+1, r, m);
    pushup(m);
    return m;
}

int main(){
    #ifndef ONLINE_JUDGE
    freopen("test.txt", "r", stdin);
    #endif
    int n, x, z;
    do{
        scanf("%d", &n);
        if(!n)  break;
        for(int i = 0;i < n;i++){
            scanf("%d", &arr[i].v);
            arr[i].id = i;
            siz[i] = 1;
        }
        sort(arr, arr+n);
        build(0, n);
        for(int i = 0;i < n;i++){
            x = arr[i].id;
            splay(x);
            z = son[x][0]<0?0:siz[son[x][0]];
            printf("%d", i+z+1);
            if(i < n-1)
                putchar(' ');
            if(son[x][0] >= 0)
                lazy[son[x][0]] ^= true;
            erase(x);
        }
        putchar('\n');
    }while(true);
    return 0;
}