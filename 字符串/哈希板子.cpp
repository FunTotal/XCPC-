const int mod = 1e18 + 31, base = 131;
int mi[maxn], h[maxn];
void init_mi() {
    mi[0] = 1;
    for (int i = 1; i < maxn; i++)
        mi[i] = (__int128_t)mi[i - 1] * base % mod;
}
void init_Hash(string& str) {
    for (int i = 1; i <= str.length(); i++)
        h[i] = (__int128_t)h[i - 1] * base + str[i - 1];
}
int get_Hash(int l, int r) {
    int res = (h[r] - (__int128_t)h[l - 1] * mi[r - l + 1] % mod + mod) % mod;
    return res;
}