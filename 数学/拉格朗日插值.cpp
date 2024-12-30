/*
f(k) =
    for i = 1 to n:
        for j = 1 to n:
            if (i != j)
                ans += y[i] * (k - x[j])/(x[i]-x[j])
*/
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int maxn = 1e5 + 10;
const int mod = 998244353;
int x[maxn], y[maxn];
int ksm(int a, int b) {
    int res = 1;
    for (; b; b >>= 1, a = a * a % mod)
        if (b & 1)
            res = res * a % mod;
    return res;
}
signed main() {
    int n, k;
    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        cin >> x[i] >> y[i];
    }
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        int zi = 1, mu = 1;
        for (int j = 1; j <= n; j++) {
            if (i == j)
                continue;
            zi = zi * (k - x[j] + mod) % mod;
            mu = mu * (x[i] - x[j] + mod) % mod;
        }
        ans = (ans + y[i] * zi % mod * ksm(mu, mod - 2) % mod) % mod;
    }
    cout << ans << endl;
    return 0;
}