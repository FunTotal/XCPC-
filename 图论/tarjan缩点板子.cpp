vector<int> G[maxn];
stack<int> stk;
int dfn[maxn], low[maxn], instk[maxn], scc[maxn], cscc, Cnt;
// scc是每个点所属强连通分量编号，cscc是强连通分量的数量
// 注意可能图不联通，要对所有没有dfn[i]的点跑tarjan
// 之后再遍历所有点的所有边，对应的给scc[i] 向scc[j] 连边
void tarjan(int u) {
    low[u] = dfn[u] = ++Cnt;
    instk[u] = 1;
    stk.push(u);
    for (auto v : G[u]) {
        if (!dfn[v]) {
            tarjan(v);
            low[u] = min(low[u], low[v]);
        } else if (instk[v])
            low[u] = min(low[u], dfn[v]);
    }
    if (low[u] == dfn[u]) {
        int top;
        cscc++;
        do {
            top = stk.top();
            stk.pop();
            instk[top] = 0;
            scc[top] = cscc;
        } while (top != u);
    }
}