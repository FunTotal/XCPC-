const int maxn = 1e5 + 10;  // 需要的最大组合数n，m的范围
const int mod = 1e9 + 7;
int fac[maxn], ifac[maxn];
int ksm(int a, int b) {
    int res = 1;
    for (; b; b >>= 1, a = a * a % mod) {
        if (b & 1)
            res = res * a % mod;
    }
    return res;
}
int C(int n, int m) {  // m是小的数字，n是大的
    if (n < m || m < 0)
        return 0;
    return fac[n] * ifac[m] % mod * ifac[n - m] % mod;
}

int A(int n, int m) {  // m是小的数字，n是大的
    if (n < m || m < 0)
        return 0;
    return fac[n] * ifac[n - m] % mod;
}
void init() {
    fac[0] = 1;  // 阶乘预处理
    for (int i = 1; i <= maxn - 5; i++)
        fac[i] = fac[i - 1] * i % mod;
    ifac[maxn - 5] = ksm(fac[maxn - 5], mod - 2);
    for (int i = maxn - 5; i; i--)  // 换着写可能导致0的逆元变成0
        ifac[i - 1] = ifac[i] * i % mod;
}