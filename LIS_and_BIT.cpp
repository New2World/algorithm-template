/*

Given a permutation of integers [1...n], there are several longest increasing subsequences (LIS). 
Output an array in which each element represent the number of LIS the corresponding integer appears. Results should module 10^9+7.

Example:
Inputs:
5
3 1 4 2 5

Outputs:
1 2 2 1 3

Explanation:
LIS: [3,4,5], [1,4,5], [1,2,5]
- 3, 2 appears in only 1 LIS;
- 1, 4 appears in 2 LIS;
- 5 appears in 3 LIS.

*/

#include <bits/stdc++.h>

#define lowbit(x) ((x) & (-x))

using namespace std;
using LL = long long;
using vi = vector<int>;
using pii = pair<int,int>;

const int mxN = 1e5 + 1;
const int MOD = 1e9 + 7;

void update(vector<pii>& dp, int x, pii val){
    int n = dp.size();
    while(x < n){
        if(val.first >= dp[x].first){
            if(val.first == dp[x].first){
                dp[x].second += val.second;
                dp[x].second %= MOD;
            }else{
                dp[x].second = val.second;
                dp[x].first = val.first;
            }
        }
        x += lowbit(x);
    }
}

pii query(const vector<pii>& dp, int x){
    pii ans = {0, 0};
    while(x){
        if(dp[x].first >= ans.first){
            if(dp[x].first == ans.first){
                ans.second += dp[x].second;
                ans.second %= MOD;
            }else{
                ans.second = dp[x].second;
                ans.first = dp[x].first;
            }
        }
        x -= lowbit(x);
    }
    return ans;
}

/*
思路：
1. 解决 LIS 有三种方法
  - lower_bound: O(n log n), 无法计数;
  - DP: O(n ^ 2), 可以计数;
  - DP + BIT (Fenwick): O(n log n), 可以计数，Fenwick也是树状数组的叫法;
因为这里不仅需要找到 LIS 的值，还得计数；而 lower_bound 方法会破坏子序列，因此不考虑。这里具体讲讲 DP + BIT (Fenwick)。

对于每一位，以它为结尾的 LIS 具有如下性质：LIS[i] = max{LIS[j] + 1}, \forall j < i and a[j] < a[i].
这里就可以用到树状数组来维护 {LIS长度, 数量}，而树状数组下标表示值域，即 [1...x] 的 LIS 和其对应数量。

比如例子里: 考虑以 3 结尾的 LIS，那么就 query(3-1) 的 LIS，然后以 3 结尾的结果就是 query + 1 了。
因为树状数组维护前缀，所以即使 query 没有 3-1=2 只有 1，也能查到（1 是 2 的前缀）。这么一来，通过树状数组的 query(x-1) 就满足了 a[j] < a[i]。
又因为我们遍历数组时，i=0...n 是从小到大的顺序，因此 j < i 也就满足了。还是拿 3 举例，虽然 [1 3] 是个 LIS，但我们考虑 3 的时候 1 还没加进树状数组，因此 query 不会考虑 1。
这么一来，两个条件都满足了。

那么关于 LIS 的数量，在树状数组 query 和 update 时都得考虑三种情况，以 query 举例：
 - ans < bit[x]: 出现更大的 LIS，更新 ans，并重置数量为 bit 对应的数量
 - ans == bit[x]: 最大 LIS 又出现了，数量叠加；
 - ans > bit[x]: 已经 query 更大的，跳过；
update 也差不多，不过如果更新的值更大要修改 bit[x]。

2. 怎么算每一位出现的数量呢？对任意一位，出现的数量是它前面的 LIS 数量乘以后面的 LIS 数量，因此需要双向 DP，简单来说就是反向遍历。
正向的递增就是反向的递减，但不像再写一套反向的逻辑，那就直接 (n - x)。
在算完双向DP后，对每一位来说，如果它在 LIS 里，那么一定有 LIS_forward[i] + LIS_backward[i] - 1 == LIS，这里 -1 是因为 arr[i] 正反计算了两次。
然后把前后的数量乘起来就行。
*/

void solve(){
    int n;
    cin >> n;
    vi arr(n, 0);
    vi lis1(n, 0), cnt1(n, 0);
    vi lis2(n, 0), cnt2(n, 0);
    int mxl = 1;
    vector<pii> dp1(n+1, {0,0}), dp2(n+1, {0,0});
    for(int i = 0;i < n;++i){
        cin >> arr[i];
        auto ret = query(dp1, arr[i] - 1);
        lis1[i] = ret.first + 1;
        cnt1[i] = ret.first > 0 ? ret.second : 1;
        update(dp1, arr[i], {lis1[i], cnt1[i]});
        mxl = max(mxl, lis1[i]);
    }

    for(int i = n-1;i >= 0;--i){
        auto ret = query(dp2, n - arr[i]);
        lis2[i] = ret.first + 1;
        cnt2[i] = ret.first > 0 ? ret.second : 1;
        update(dp2, n - arr[i] + 1, {lis2[i], cnt2[i]});
    }
    
    for(int i = 0;i < n;++i){
        if(lis1[i] + lis2[i] - 1 == mxl)
            cout << (1LL * cnt1[i] * cnt2[i]) % MOD << endl;
        else
            cout << 0 << endl;
    }
}

int main(){
    // freopen("data.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);

    int T = 1;
    // cin >> T;
    for(int t = 1;t <= T;++t){
        solve();
    }
    return 0;
}

