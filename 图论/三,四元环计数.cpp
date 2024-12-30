int cal3() {
    int res = 0;
    for (int u = 1; u <= n; u++) {
        for (auto v : G[u]) vis[v] = u;
        for (auto v1 : G[u])
            for (auto v2 : G[v1]) {
                if (vis[v2] == u)
                    res++;
            }
        for (auto v : G[u]) vis[v] = 0;
    }
    return res;
}
bool cmp(int u, int v) { //in是原无向图的度数
    return in[u] == in[v] ? u < v : in[u] < in[v];
}
int cal4() {
    int res = 0;
    for (int u = 1; u <= n; u++) {
        for (auto v : G0[u]) //G0是原无向图
            for (auto w : G[v])
                if (cmp(u, w))
                    (res += vis[w]++) %= mod;
        for (auto v : G0[u])
            for (auto w : G[v])
                if (cmp(u, w))
                    vis[w] = 0;
    }
    return res;
}