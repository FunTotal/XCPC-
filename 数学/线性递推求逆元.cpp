const int maxn = 3e6 + 10;
int inv[maxn];
int mod;
signed main() {
    int n;
    cin >> n >> mod;
    inv[1] = 1;
    for (int i = 2; i <= n; i++) {
        inv[i] = (mod - mod / i) * inv[mod % i] % mod;
    }
    for (int i = 1; i <= n; i++)
        cout << inv[i] << "\n";
    // system("pause");
    return 0;
}