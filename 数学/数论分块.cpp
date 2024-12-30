int F(int n) {
    int r, ans = 0;
    for (int i = 1, l = 1; i <= n; i = r + 1) {
        l = i, r = n / (n / i);
        // l 到 r 内， n / i 的值均为 n / i
        ans += (r - l + 1) * (n / i);
        ans %= mod;
    }
    return ans;
}
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int l, r;
    cin >> l >> r;
    cout << (F(r) - F(l - 1) + mod) % mod << endl;
    return 0;
}