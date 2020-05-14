/*

POJ 3264 - Balanced Lineup

*/

#include <cstdio>
#include <cmath>
#include <algorithm>

#define MAXLEN 100005
#define inf (1<<31-1)

using namespace std;

int dp[MAXLEN][20][2];

int getbit(int x){
    return (int)log2((double)x);
}

void update(int i, int j, int n){
    int g = 1 << (j-1);
    if(g >= n)  return;
    dp[i][j][0] = min(dp[i][j-1][0], dp[i+g][j-1][0]);
    dp[i][j][1] = max(dp[i][j-1][1], dp[i+g][j-1][1]);
}

void build(int n){
    int nbit = getbit(n);
    for(int j = 1;j <= nbit;j++)
        for(int i = 0;i < n;i++)
            update(i, j, n);
}

int query(int l, int r){
    int nbit = getbit(r-l+1);
    r -= (1<<nbit)-1;
    int mn = min(dp[l][nbit][0], dp[r][nbit][0]);
    int mx = max(dp[l][nbit][1], dp[r][nbit][1]);
    return mx - mn;
}

int main(){
    #ifndef ONLINE_JUDGE
    freopen("test.txt", "r", stdin);
    #endif
    int n, q, l, r;
    scanf("%d %d", &n, &q);
    for(int i = 0;i < n;i++){
        scanf("%d", &dp[i][0][0]);
        dp[i][0][1] = dp[i][0][0];
    }
    build(n);
    for(int i = 0;i < q;i++){
        scanf("%d %d", &l, &r);
        printf("%d\n", query(l-1, r-1));
    }
    return 0;
}