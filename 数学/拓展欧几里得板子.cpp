int exgcd(int a, int b, int& x, int& y) {  // 返回值是gcd
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    int d = exgcd(b, a % b, y, x);
    y -= (a / b) * x;
    return d;
}