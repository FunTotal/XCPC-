struct DOMTree {
    // 赋值n为图的节点数，有向边add(u, v),然后调用work(起点),复杂度O(nlogn)
    // idm[i]表示i的支配点
    // work中已经包括了初始化,多测需要手动清空G
    // 统计支配子树大小，可以反向遍历dfn序
    // 是森林可以建个虚点，向各个树的根连边
    vector<int> G[3][maxn];
    int n, dfc;
    int dfn[maxn], pos[maxn], sdm[maxn], idm[maxn], fa[maxn], mn[maxn],
        fth[maxn];  // pos是dfn逆映射
    void dfs(int u) {
        dfn[u] = ++dfc;
        pos[dfc] = u;
        for (auto v : G[0][u]) {
            if (!dfn[v]) {
                dfs(v);
                fth[v] = u;
            }
        }
    }
    int find(int x) {
        if (fa[x] == x) {
            return x;
        }
        int tmp = fa[x];
        fa[x] = find(fa[x]);
        if (dfn[sdm[mn[tmp]]] < dfn[sdm[mn[x]]]) {
            mn[x] = mn[tmp];
        }
        return fa[x];
    }
    void work(int st) {
        dfc = 0;
        for (int i = 1; i <= n; ++i)
            dfn[i] = 0;
        dfs(st);
        for (int i = 1; i <= n; ++i) {
            mn[i] = fa[i] = sdm[i] = i;
        }
        for (int i = dfc; i >= 2; --i) {
            int u = pos[i], res = inf;
            for (auto v : G[1][u]) {
                if (!dfn[v])
                    continue;
                find(v);
                if (dfn[v] < dfn[u])
                    res = min(res, dfn[v]);
                else
                    res = min(res, dfn[sdm[mn[v]]]);
            }
            sdm[u] = pos[res];
            fa[u] = fth[u];
            G[2][sdm[u]].push_back(u);
            u = fth[u];
            for (auto v : G[2][u]) {
                find(v);
                if (u == sdm[mn[v]])
                    idm[v] = u;
                else
                    idm[v] = mn[v];
            }
            G[2][u].clear();
        }
        for (int i = 2; i <= dfc; ++i) {
            int u = pos[i];
            if (idm[u] != sdm[u]) {
                idm[u] = idm[idm[u]];
            }
        }
    }
} dom;
void add(int u, int v) {  // 题目中的有向边 u -> v
    dom.G[0][u].push_back(v);
    dom.G[1][v].push_back(u);
}