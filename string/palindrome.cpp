#include <iostream>
#include <vector>
#include <string>

using namespace std;

int expand(const string &s, int slen, int m, int len) {
    for(;m + len < slen && m - len >= 0;++len)
        if(s[m+len] != s[m-len])
            break;
    return len;
}
pair<int,int> manacher(const string &s, int slen) {
    int m = 0, l = -1, li, r = 1;
    int _max = 1, _m = 0;
    vector<int> mana(slen, 0);
    mana[0] = 1;
    for(int i = 1;i < slen;++i) {
        li = 2 * m - i;
        if(li <= l)
            mana[i] = expand(s, slen, i, 1);
        else {
            if(li - mana[li] <= l)
                mana[i] = expand(s, slen, i, r-i);
            else
                mana[i] = mana[li];
        }
        if(i + mana[i] > r)
            m = i, l = i - mana[i], r = i + mana[i];
        if(mana[i] > _max)
            _max = mana[i], _m = m;
    }
    return make_pair((_m-_max+1)/2, _max-1);
}

int main() {
    string s;
    cin >> s;
    int slen = s.size();
    if(slen < 2) {
        cout << slen << endl;
        return 0;
    }
    string ss = "#";
    for(int i = 0;i < slen;++i) {
        ss += s[i] ;
        ss += "#";
    }
    pair<int,int> ans = manacher(ss, ss.size());
    cout << s.substr(ans.first, ans.second) << endl;
    return 0;
}