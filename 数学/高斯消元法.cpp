db arr[maxn][maxn];
db ans[maxn];
db eps = 1e-9;
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n + 1; j++)
            cin >> arr[i][j];
    for (int i = 1; i <= n; i++) {
        int tem = i;
        for (int j = i + 1; j <= n; j++)
            if (abs(arr[tem][i] < abs(arr[j][i])))
                tem = j;
        if (abs(arr[tem][i]) < eps) {
            cout << "No Solution" << endl;
            return 0;
        }
        if (i != tem)
            swap(arr[i], arr[tem]);
        db div = arr[i][i];
        for (int j = i; j <= n + 1; j++)
            arr[i][j] /= div;
        for (int j = i + 1; j <= n; j++) {
            div = arr[j][i];
            for (int k = i; k <= n + 1; k++)
                arr[j][k] -= arr[i][k] * div;
        }
    }
    ans[n] = arr[n][n + 1];
    for (int i = n - 1; i >= 1; i--) {
        ans[i] = arr[i][n + 1];
        for (int j = i + 1; j <= n; j++)
            ans[i] -= arr[i][j] * ans[j];
    }
    for (int i = 1; i <= n; i++)
        cout << fixed << setprecision(2) << ans[i] << endl;
    return 0;
}