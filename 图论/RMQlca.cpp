#include <bits/stdc++.h>
using namespace std;
const int maxn = 5e5 + 10;
vector<int> G[maxn];
struct RMQlca {
    // rmqlca.n = n, rmqlca.init(root)
    int n;
    int st[20][maxn], dfn[maxn], tot;
    int mn(int x, int y) { return dfn[x] < dfn[y] ? x : y; }
    void dfs(int u, int f = 0) {
        st[0][tot] = f, dfn[u] = ++tot;
        for (auto v : G[u]) {
            if (v == f) continue;
            dfs(v, u);
        }
    }
    int lca(int x, int y) {
        if (dfn[x] > dfn[y]) swap(x, y);
        int lg = __lg(dfn[y] - dfn[x]);
        return x != y ? mn(st[lg][dfn[x]], st[lg][dfn[y] - (1 << lg)]) : x;
    }
    void init(int root) {
        dfs(root);
        for (int i = 1; i < 20; ++i)
            for (int j = 1; j + (1 << i) - 1 < n; ++j)
                st[i][j] = mn(st[i - 1][j], st[i - 1][j + (1 << i - 1)]);
    }
} rmqlca;