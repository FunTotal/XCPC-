int a[maxn], f[maxn][maxn][2];
// f[len][state],状压的state记录状态
int dfs(int pos, int pre, bool limit, bool lead0, int cnt) {
    if (!pos)
        return 1;  // 看情况return 1还是cnt
    auto& now = f[pos][pre][limit];
    if (!lead0 && ~now)
        return now;
    int up = limit ? a[pos] : 9;
    int res = 0;
    for (int i = 0; i <= up; i++) {
        if (!lead0 && abs(i - pre) < 2)
            continue;  // 保证枚举的要合法
        res += dfs(pos - 1, i, limit && i == up, lead0 && i == 0, cnt);
    }
    if (!lead0)
        now = res;
    return res;
}
int solve(int x) {
    int len = 0;
    while (x > 0) {
        a[++len] = x % 10;
        x /= 10;
    }
    return dfs(len, 0, true, true, 0);
}