#include <bits/stdc++.h>
// #define int long long
#define inf 0x3f3f3f3f
#define ll long long
#define pii pair<int, int>
#define db double
using namespace std;
const int maxn = 2e5 + 10;
const int mod = 998244353;
vector<int> G[maxn];
int val[maxn], b[maxn], tong[maxn];
int bel[maxn], sq, ans[maxn];
int fa[maxn][24], lg[maxn], dep[maxn], in[maxn], out[maxn], cnt, cur;
int vis[maxn], oula[maxn];
struct query {
    int l, r, id, lca;
    bool operator<(const query& o) {
        if (bel[l] != bel[o.l])
            return bel[l] < bel[o.l];
        if (bel[l] & 1)
            return bel[r] < bel[o.r];
        return bel[r] > bel[o.r];
    }
} q[maxn];
void dfs(int u, int f, int deep) {
    in[u] = ++cnt;
    oula[cnt] = u;
    fa[u][0] = f;
    dep[u] = deep;
    for (int i = 1; i <= lg[dep[u]]; i++)
        fa[u][i] = fa[fa[u][i - 1]][i - 1];
    for (auto v : G[u])
        if (v != f)
            dfs(v, u, deep + 1);
    out[u] = ++cnt;
    oula[cnt] = u;
}
int LCA(int u, int v) {
    if (dep[u] < dep[v])
        swap(u, v);
    while (dep[u] > dep[v])
        u = fa[u][lg[dep[u] - dep[v]]];
    if (u == v)
        return u;
    for (int i = lg[dep[u]]; i >= 0; i--)
        if (fa[u][i] != fa[v][i])
            u = fa[u][i], v = fa[v][i];
    return fa[u][0];
}
void add(int x) {
    tong[x]++;
    if (tong[x] == 1)
        cur++;
}
void del(int x) {
    tong[x]--;
    if (tong[x] == 0)
        cur--;
}
void cal(int x) {
    vis[x] ^= 1;
    if (vis[x])
        add(val[x]);
    else
        del(val[x]);
}
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    for (int i = 2; i < maxn; i++)
        lg[i] = lg[i >> 1] + 1;
    int n, m;
    cin >> n >> m;
    sq = sqrt(2 * n);
    for (int i = 1; i <= 2 * n; i++)
        bel[i] = i / sq + 1;
    for (int i = 1; i <= n; i++)
        cin >> val[i], b[i] = val[i];
    sort(b + 1, b + 1 + n);
    int len = unique(b + 1, b + 1 + n) - b - 1;
    for (int i = 1; i <= n; i++)
        val[i] = lower_bound(b + 1, b + 1 + len, val[i]) - b;
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        G[u].push_back(v);
        G[v].push_back(u);
    }
    dfs(1, 0, 0);
    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        if (in[u] > in[v])
            swap(u, v);
        q[i].id = i;
        q[i].lca = LCA(u, v);
        if (q[i].lca == u) {
            q[i].l = in[u];
            q[i].r = in[v];
            q[i].lca = 0;
        } else {
            q[i].l = out[u];
            q[i].r = in[v];
        }
    }
    sort(q + 1, q + 1 + m);
    int l = 1, r = 0;
    for (int i = 1; i <= m; i++) {
        while (r < q[i].r)
            cal(oula[++r]);
        while (l < q[i].l)
            cal(oula[l++]);
        while (l > q[i].l)
            cal(oula[--l]);
        while (r > q[i].r)
            cal(oula[r--]);
        if (q[i].lca)
            cal(q[i].lca);
        ans[q[i].id] = cur;
        if (q[i].lca)
            cal(q[i].lca);
    }
    for (int i = 1; i <= m; i++)
        cout << ans[i] << "\n";
    return 0;
}