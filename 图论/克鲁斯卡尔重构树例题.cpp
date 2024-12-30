#include <bits/stdc++.h>
#define int long long
#define inf 0x3f3f3f3f
using namespace std;
const int maxn = 4e5 + 10;
const int maxm = 4e5 + 10;
struct edge {
    int u, v, w;
} e[maxm];
int f[maxn][30], dep[maxn], lg[maxn], val[maxn];
vector<int> G[maxm];
int fa[maxn];
int Find(int x) {
    return fa[x] == x ? fa[x] : fa[x] = Find(fa[x]);
}
bool cmp(edge a, edge b) {
    return a.w < b.w;
}
void dfs(int u, int fu, int deep) {
    f[u][0] = fu;
    dep[u] = deep;
    for (int i = 1; i <= lg[dep[u]]; i++)
        f[u][i] = f[f[u][i - 1]][i - 1];
    for (auto v : G[u])
        if (v != fu)
            dfs(v, u, deep + 1);
}
int lca(int u, int v) {
    if (dep[u] < dep[v])
        swap(u, v);
    while (dep[u] > dep[v])
        u = f[u][lg[dep[u] - dep[v]]];
    if (u == v)
        return u;
    for (int i = lg[dep[u]]; i >= 0; i--)
        if (f[u][i] != f[v][i])
            u = f[u][i], v = f[v][i];
    return f[u][0];
}
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n, m;
    cin >> n >> m;
    int cnt = n;
    for (int i = 0; i <= n * 2; i++)
        fa[i] = i;
    for (int i = 2; i < maxn; i++)
        lg[i] = lg[i >> 1] + 1;
    for (int i = 1; i <= m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        e[i] = edge{u, v, w};
    }
    sort(e + 1, e + 1 + m, cmp);
    for (int i = 1; i <= m; i++) {
        int u = e[i].u, v = e[i].v, w = e[i].w;
        int fu = Find(u), fv = Find(v);
        if (fu == fv)
            continue;
        cnt++;  // 创造新的结点
        fa[fu] = fa[fv] = cnt;
        f[fu][0] = f[fv][0] = cnt;
        val[cnt] = w;
        G[cnt].push_back(fu);
        G[cnt].push_back(fv);
    }
    dfs(cnt, cnt, 1);
    int q;
    cin >> q;
    while (q--) {
        int u, v;
        cin >> u >> v;
        int fu = Find(u), fv = Find(v);
        if (fu != fv)
            cout << "impossible" << endl;
        else
            cout << val[lca(u, v)] << endl;
    }
    return 0;
}