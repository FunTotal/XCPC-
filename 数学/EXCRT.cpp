int mul(int a, int b, int m) {
    return (__int128_t)a * b % m;
}
int exgcd(int a, int b, int& x, int& y) {
    if (!b) {
        x = 1, y = 0;
        return a;
    }
    int d = exgcd(b, a % b, y, x);
    y -= a / b * x;
    return d;
}
int excrt(vector<int> ai, vector<int> bi) {  // x % b = a % b;
    int n = ai.size();
    int x, y;
    int M = bi[0], ans = ai[0];
    for (int i = 1; i < n; i++) {
        int a = M, b = bi[i], c = (ai[i] - ans % b + b) % b;
        int g = exgcd(a, b, x, y), bg = b / g;
        if (c % g != 0)
            return -1;
        x = mul(x, c / g, bg);
        ans += x * M;
        M *= bg;
        ans = (ans % M + M) % M;
    }
    return ans = (ans % M + M) % M;
}