// 点差分lca-=2, 边差分lca--,fa[lca]--
int fa[maxn][30], dep[maxn], lg[maxn];
lg[i] = [lg >> 1] + 1;
void dfs(int u, int f, int deep) {
    fa[u][0] = f;
    dep[u] = deep;
    for (int i = 1; i <= lg[dep[u]]; i++)
        fa[u][i] = fa[fa[u][i - 1]][i - 1];
    for (auto v : G[u]) {
        if (v == f)
            continue;
        dfs(v, u, deep + 1);
    }
}
int lca(int u, int v) {
    if (dep[u] < dep[v]) swap(u, v);
    while (dep[u] > dep[v])
        u = fa[u][lg[dep[u] - dep[v]]];
    if (u == v) return u;
    for (int i = lg[dep[u]]; i >= 0; i--)
        if (fa[u][i] != fa[v][i])
            u = fa[u][i], v = fa[v][i];
    return fa[u][0];
}