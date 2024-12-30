int arr[maxn], sta[maxn];
signed main() {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> arr[i];
    int len = 1;
    sta[len] = arr[1];
    for (int i = 2; i <= n; i++) {
        if (arr[i] > sta[len]) {
            sta[++len] = arr[i];
        } else {
            int tem = lower_bound(sta + 1, sta + 1 + len, arr[i]) - sta;
            sta[tem] = arr[i];
        }
    }
    cout << len << endl;
}