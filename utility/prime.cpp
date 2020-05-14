/*

HDU 2138 - How Many Prime Numbers

*/

#include <bits/stdc++.h>

#define MAXLEN 1000005

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

ll mul(ll a, ll b, int m){
    a %= m;
    b %= m;
    ll c = (long double)a * b / m;
    ll ans = a * b - c * m;
    return (ans % m + m) % m;
}

ll quickpow(int x, int y){
    ll s = x, p = 1;
    int yy = y;
    while(y){
        if(y & 1)
            p = mul(p, s, yy+1);
        s = mul(s, s, yy+1);
        y >>= 1;
    }
    return p;
}

bool miller(int v){
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