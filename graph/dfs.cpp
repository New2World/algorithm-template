/*

HDU 1011 - sticks

*/

#include <bits/stdc++.h>

#define MAXLEN 64

using namespace std;

int arr[MAXLEN];
bool used[MAXLEN];

bool dfs(int n, int s, int t, int l, int k, int c){
    if(s == c)  return true;
    int nl, prev = 0;
    for(int i = k;i < n;i++){
        if(used[i] || prev == arr[i]) continue;
        used[i] = true;
        nl = l + arr[i];
        if(nl == t){
            if(dfs(n, s, t, 0, 0, c+1))
                return true;
            prev = arr[i];
        }
        else if(nl < t){
            if(dfs(n, s, t, nl, i+1, c))
                return true;
            prev = arr[i];
        }
        used[i] = false;
        if(l == 0)  break;
    }
    return false;
}

int main(){
    #ifndef ONLINE_JUDGE
    freopen("test.txt", "r", stdin);
    #endif
    int n, l, s;
    bool flag;
    while(~scanf("%d", &n) && n){
        s = 0;
        for(int i = 0;i < n;i++){
            scanf("%d", arr+i);
            if(arr[i] > 50){
                --n, --i;
                continue;
            }
            s += arr[i];
        }
        sort(arr, arr+n, greater<int>());
        for(l = arr[0];l <= s;l++){
            memset(used, false, sizeof(used));
            if(s % l != 0)
                continue;
            if(flag = dfs(n, s/l, l, 0, 0, 0))
                break;
        }
        printf("%d\n", flag?l:s);
    }
    return 0;
}