/*

洛谷 P2657 - windy 数

*/

#include <bits/stdc++.h>

using namespace std;
using vi = vector<int>;

map<vi,int> dp;

int dfs(const string& tgt, int p, int pre, int lead, bool tight){
    int n = tgt.size(), v = (int)(tgt[p]-'0');
    int ans = 0;
    
    if(p >= n)  return 1;
    
    // if there's no leading digit, we can go even further (w/o leading digits)
    if(lead == 0)
        ans += dfs(tgt, p+1, pre, lead, false);
    
    int lo = lead?0:1;  // if not leading, it can be '0'; otherwise, at least '1'
    int hi = tight?v:9; // if previous digits are tight to the bound, it can at most be 'v'
    for(int i = lo;i <= hi;++i){
        if(abs(i - pre) < 2)    continue;
        vi k = {p,lead,i,tight?1:0};    // memorize
        if(dp.count(k) == 0)
            dp[k] = dfs(tgt, p+1, i, lead+1, tight&(i==v));
        ans += dp[k];
    }
    return ans;
}

void solve(int a, int b){
    string sa = to_string(a-1); // 0 ~ a-1
    string sb = to_string(b);   // 0 ~ b
    int r = dfs(sb, 0, -2, 0, true);
    dp.clear();
    int l = dfs(sa, 0, -2, 0, true);
    printf("%d\n", r-l);        // a ~ b
}

int main(){
    #ifndef ONLINE_JUDGE
    freopen("test.txt", "r", stdin);
    #endif
    
    int a, b;
    while(~scanf("%d %d", &a, &b)){
        solve(a, b);
    }
    return 0;
}
