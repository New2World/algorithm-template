/*

HDU 4323 - Magic Number

*/

#include <bits/stdc++.h>

#define MAXLEN 15

using namespace std;

int dp[MAXLEN][MAXLEN];

int preprocess(const string &s, const string &t){
    int slen = s.size(), tlen = t.size();
    int flag;
    for(int i = 0;i <= tlen;i++)
        dp[0][i] = i;
    for(int i = 0;i <= slen;i++)
        dp[i][0] = i;
    for(int i = 1;i <= slen;i++){
        for(int j = 1;j <= tlen;j++){
            flag = s[i-1]==t[j-1]?0:1;
            dp[i][j] = min(min(dp[i-1][j]+1, dp[i][j-1]+1), dp[i-1][j-1]+flag);
        }
    }
    return dp[slen][tlen];
}

int main(){
    #ifndef ONLINE_JUDGE
    freopen("test.txt", "r", stdin);
    #endif
    int T, n, q, d;
    int ans;
    string s;
    vector<string> sv;
    scanf("%d", &T);
    for(int ca = 1;ca <= T;ca++){
        printf("Case #%d:\n", ca);
        sv.clear();
        scanf("%d %d", &n, &q);
        for(int i = 0;i < n;i++){
            cin >> s;
            sv.push_back(s);
        }
        for(int i = 0;i < q;i++){
            ans = 0;
            cin >> s >> d;
            for(int j = 0;j < n;j++)
                if(preprocess(sv[j], s) <= d)
                    ans++;
            printf("%d\n", ans);
        }
    }
    return 0;
}