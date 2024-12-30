#include <bits/stdc++.h>
// #define int long long
#define ll long long
using namespace std;
const int maxn = 1e5 + 10;
const int mod = 998244353;
const int P = 998244353;
struct FWT {
    int n;
    vector<int> Or(vector<int> b, int type = 1) {  // 逆运算type = -1
        vector<int> a = b;
        a.resize(n);
        for (ll x = 2; x <= n; x <<= 1) {
            ll k = x >> 1;
            for (ll i = 0; i < n; i += x) {
                for (ll j = 0; j < k; j++) {
                    a[i + j + k] = (a[i + j + k] + a[i + j] * type) % P;
                }
            }
        }
        return a;
    }
} fwt;
void solve() {
    int n; cin >> n;
    fwt.n = (1 << n);
    vector<vector<int>> a((n + 1), vector<int>(1 << n));
    vector<vector<int>> b((n + 1), vector<int>(1 << n));
    vector<vector<int>> h((n + 1), vector<int>(1 << n));
    for (int i = 0; i < (1 << n); i++)
        cin >> a[__builtin_popcount(i)][i];
    for (int i = 0; i < (1 << n); i++)
        cin >> b[__builtin_popcount(i)][i];
    for (int i = 0; i <= n; i++)
        a[i] = fwt.Or(a[i], 1);
    for (int i = 0; i <= n; i++)
        b[i] = fwt.Or(b[i], 1);
    for (int i = 0; i <= n; i++)
        for (int j = 0; j <= i; j++)
            for (int k = 0; k < (1 << n); k++)
                h[i][k] = (h[i][k] + 1ll * a[j][k] * b[i - j][k] % mod) % mod;
    for (int i = 0; i <= n; i++)
        h[i] = fwt.Or(h[i], -1);
    for (int i = 0; i < (1 << n); i++)
        cout << h[__builtin_popcount(i)][i] << " ";
}
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int t = 1;
    while (t--) solve();
    return 0;
}