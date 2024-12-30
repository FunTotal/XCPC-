#include <bits/stdc++.h>
#define int long long
#define inf 0x3f3f3f3f
#define ll long long
#define pii pair<int, int>
#define db double
using namespace std;
const int maxn = 2e5 + 10;
const int mod = 998244353;
int root[maxn], ncnt = 0;
struct tree {
    int ls, rs, sum;
} t[maxn << 5];
#define lson t[rt].ls
#define rson t[rt].rs
void push_up(int rt) {
    t[rt].sum = t[lson].sum + t[rson].sum;
}
void change(int& rt, int old, int l, int r, int val) {
    rt = ++ncnt;
    t[rt] = t[old];
    if (l == r) {
        t[rt].sum++;
        return;
    }
    int mid = (l + r) >> 1;
    if (val <= mid)
        change(t[rt].ls, t[old].ls, l, mid, val);
    else
        change(t[rt].rs, t[old].rs, mid + 1, r, val);
    push_up(rt);
}
int ask(int pre, int now, int l, int r, int k) {
    if (l == r)
        return l;
    int num = t[t[now].ls].sum - t[t[pre].ls].sum;
    int mid = (l + r) >> 1;
    if (num >= k)
        return ask(t[pre].ls, t[now].ls, l, mid, k);
    else
        return ask(t[pre].rs, t[now].rs, mid + 1, r, k - num);
}
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        change(root[i], root[i - 1], 0, inf, x);
    }
    while (m--) {
        int l, r, k;
        cin >> l >> r >> k;
        cout << ask(root[l - 1], root[r], 0, inf, k) << "\n";
    }
    // system("pause");
    return 0;
}