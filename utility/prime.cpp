/*

HDU 2138 - How Many Prime Numbers

*/

#include <bits/stdc++.h>

#define MAXLEN 1000005
// #define qmul(a, b, m) mul(a, b, m)
#define qmul(a, b, m) quickmul(a, b, m)

typedef long long ll;

int prime[MAXLEN], base[3] = {2, 7, 61};
bool isprime[MAXLEN];

void initprime(){
    memset(isprime, true, sizeof(isprime));
    int pt = 0, p;
    for(int i = 2;i < MAXLEN;i++){
        if(isprime[i])
            prime[pt++] = i;
        for(int j = 0;j < pt && prime[j]*i < MAXLEN;j++){
            isprime[prime[j]*i] = false;
            if(i % prime[j] == 0)
                break;
        }
    }
}

ll mul(ll a, ll b, int m){              // 将 a b 写成 m 的倍数加余数，就可以推出来
    a %= m;
    b %= m;
    ll c = (long double)a * b / m;
    ll ans = a * b - c * m;
    return (ans % m + m) % m;
}

ll quickmul(ll a, ll b, int m){         // 借鉴快速幂的思想，乘法就是累加的过程
    ll res = 0;
    while(b){
        if(b & 1)
            res = (res + a) % m;
        (a <<= 1) %= m;
        b >>= 1;
    }
    return res;
}

ll quickpow(int x, int y){              // 快速幂
    ll s = x, res = 1;
    int yy = y;
    while(y){
        if(y & 1)
            res = mul(res, s, yy+1);
        s = mul(s, s, yy+1);
        y >>= 1;
    }
    return res;
}

bool miller(int v){                     // Miller-Rabbin 测试
    ll p;
    for(int i = 0;i < 3;i++){
        if(v == base[i])
            return true;
        if(quickpow(base[i], v-1) != 1LL)
            return false;
    }
    if(v % 2 == 0)
        return false;
    return true;
}

int main(){
    #ifndef ONLINE_JUDGE
    freopen("test.txt", "r", stdin);
    #endif
    int n, v;
    ll ans;
    initprime();
    while(~scanf("%d", &n)){
        ans = 0L;
        for(int i = 0;i < n;i++){
            scanf("%d", &v);
            if(v < MAXLEN && isprime[v])
                ans++;
            else if(v >= MAXLEN && miller(v))
                ans++;
        }
        printf("%lld\n", ans);
    }
    return 0;
}
