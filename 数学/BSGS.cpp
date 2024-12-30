#include <bits/stdc++.h>
#define int long long
using namespace std;
const int maxn = 1e5 + 10;
// 解决 a ^ x % mod = b的最小非负x
const int N = 1e5 + 10;
int mod;
class Hash {
   private:
    int keys[N];
    int values[N];

   public:
    Hash() { memset(values, 0, sizeof(values)); }

    int& operator[](int n) {
        int idx = (n % N + N) % N, cnt = 1;
        while (keys[idx] != n && values[idx] != 0) {
            idx = (idx + cnt * cnt) % N;
            cnt += 1;
        }
        keys[idx] = n;
        return values[idx];
    }
};
int qpow(int a, int b) {  // 快速幂
    int ans = 1;
    while (b) {
        if (b & 1)
            ans = (ans * a) % mod;
        a = (a * a) % mod;
        b >>= 1;
    }
    return ans;
}

int bsgs(int a, int b) {
    Hash mp;
    if (a % mod == b % mod)
        return 1;
    if (a % mod == 0 && b)
        return -1;

    int unit = (int)ceil(sqrt(mod)), tmp = qpow(a, unit);
    for (int i = 0; i <= unit; ++i)
        mp[b] = i, b = (b * a) % mod;
    b = 1;
    for (int i = 1; i <= unit; ++i) {
        b = (b * tmp) % mod;
        if (mp[b])
            return i * unit - mp[b];
    }
    return -1;
}
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int a, b;
    cin >> mod >> a >> b;
    int res = bsgs(a, b);
    if (res == -1)
        cout << "no solution" << endl;
    else
        cout << res << endl;
    // system("pause");
    return 0;
}