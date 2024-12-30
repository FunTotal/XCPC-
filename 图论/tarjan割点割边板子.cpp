void tarjan(int u, int fa) { //¸î±ß
    dfn[u] = low[u] = ++t;
    for (auto v : G[u]) {
        if (!dfn[v]) {
            tarjan(v, u);
            low[u] = min(low[u], low[v]);
            if (low[v] > dfn[u])
                cout << u << "->" << v << endl;
        } else if (v != fa)
            low[u] = min(low[u], dfn[v]);
    }
}
void tarjan(int u, int anc) { //¸îµã
    dfn[u] = low[u] = ++t;
    int child = 0;
    for (auto v : G[u]) {
        if (!dfn[v]) {
            tarjan(v, anc);
            low[u] = min(low[u], low[v]);
            if (low[v] >= dfn[u] && u != anc)
                cut[u] = 1;
            if (u == anc)
                child++;
        } else
            low[u] = min(low[u], dfn[v]);
    }
    if (child >= 2 && u == anc)
        cut[u] = 1;
}