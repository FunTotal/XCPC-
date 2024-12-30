#include <bits/stdc++.h>
// #define int long long
#define inf 0x3f3f3f3f
#define ll long long
#define pii pair<int, int>
#define db double
#define all(a) a.begin(), a.end()
#define ls 2 * rt
#define rs 2 * rt + 1
using namespace std;
const int maxn = 2e6 + 10;
const int mod = 998244353;
vector<pii> t[maxn];
int L[maxn], R[maxn], tag[maxn], fa[maxn], rk[maxn];
int mxtime = 2e5, top;
struct Stack {
    int x, y, add;
} stk[maxn];
int Find(int x) {
    return fa[x] == x ? fa[x] : Find(fa[x]);
}
void Union(int i, int j) {
    i = Find(i), j = Find(j);
    if (i == j)
        return;
    if (rk[i] > rk[j])
        swap(i, j);
    stk[++top] = Stack{i, j, rk[i] == rk[j]};
    fa[i] = j;
    tag[i] -= tag[j];
    rk[j] += rk[i] == rk[j];
}
void redo(Stack k) {
    rk[fa[k.x]] -= k.add;
    fa[k.x] = k.x;
    tag[k.x] += tag[k.y];
}
void solve(int rt, int l, int r) {
    int lsttop = top;
    for (auto [u, v] : t[rt]) {
        Union(u, v);
    }
    if (l == r) {
        tag[Find(1)]++;
    } else {
        int mid = (l + r) >> 1;
        solve(ls, l, mid), solve(rs, mid + 1, r);
    }
    while (top != lsttop)
        redo(stk[top--]);
}
void change(int rt, int l, int r, int p, int q, pii edge) {
    if (l == p && r == q) {
        t[rt].push_back(edge);
        return;
    }
    int mid = (l + r) >> 1;
    if (q <= mid)
        change(ls, l, mid, p, q, edge);
    else if (p > mid)
        change(rs, mid + 1, r, p, q, edge);
    else
        change(ls, l, mid, p, mid, edge),
            change(rs, mid + 1, r, mid + 1, q, edge);
}
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        cin >> L[i] >> R[i];
    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        int l = max(L[u], L[v]), r = min(R[u], R[v]);
        if (l <= r) {
            change(1, 1, mxtime, l, r, pii(u, v));
        }
    }
    for (int i = 1; i <= n; i++)
        fa[i] = i, rk[i] = 1;
    solve(1, 1, mxtime);
    for (int i = 1; i <= n; i++)
        if (tag[i])
            cout << i << " ";
    cout << endl;
    return 0;
}