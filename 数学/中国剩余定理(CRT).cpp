int n, a[maxn], b[maxn];  // a存系数，b存余数
void exgcd(int aa, int bb, int& x, int& y) {
    if (!bb) {
        x = 1;
        y = 0;
        return;
    }
    exgcd(bb, aa % bb, y, x);
    y -= aa / bb * x;
}
int inv(int q, int p) {  // 不用ksm因为p不一定是质数
    int x, y;
    exgcd(q, p, x, y);
    return (x % p + p) % p;
}
int CRT() {
    int p = 1, x = 0;
    for (int i = 1; i <= n; i++)
        p *= a[i];
    for (int i = 1; i <= n; i++) {
        int r = p / a[i];
        x += (b[i] * r * inv(r, a[i])) % p;
    }
    return x % p;
}