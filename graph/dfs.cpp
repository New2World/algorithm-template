/*

HDU 1011 - sticks

*/

#include <bits/stdc++.h>

#define MAXLEN 64

using namespace std;

int arr[MAXLEN];
bool used[MAXLEN];

bool dfs(int n, int s, int t, int l, int k, int c){
    if(s == c)  return true;            // 剪枝4：当前木棍为原木棍最后一条时，必成立，无需再dfs
    int nl, prev = 0;
    for(int i = k;i < n;i++){
        if(used[i] || prev == arr[i]) continue;     // 剪枝2：跳过重复长度
        used[i] = true;
        nl = l + arr[i];
        if(nl == t){
            if(dfs(n, s, t, 0, 0, c+1))
                return true;
            prev = arr[i];
            // 这里并不能直接返回 dfs 结果。
            // 反例：15, 11, 8, 8, 8, 4, 3, 2, 1   结果为 20
            // 如果如果直接返回，会出现 {15, 4, 1}
            // 15 占用 1 因而 {11, 8, 1} 无法成立，导致搜索失败
        }
        else if(nl < t){
            if(dfs(n, s, t, nl, i+1, c))
                return true;
            prev = arr[i];
        }
        used[i] = false;
        if(l == 0)  break;              // 剪枝3 (重要)：如果该木棍是新的第一根，那它一定要被使用。否则后面将永远无法使用
    }
    return false;
}

int main(){
    #ifndef ONLINE_JUDGE
    freopen("test.txt", "r", stdin);
    #endif
    int n, l, s;
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
        sort(arr, arr+n, greater<int>());           // 由大到小
        for(l = arr[0];l <= s;l++){
            memset(used, false, sizeof(used));
            if(s % l != 0)                          // 剪枝1：长度必为总长的因子
                continue;
            if(dfs(n, s/l, l, 0, 0, 0))             // s/l 是原木棍数量，对应剪枝4
                break;
        }
        printf("%d\n", l);
    }
    return 0;
}
