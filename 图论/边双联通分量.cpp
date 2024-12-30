int head[maxn], Cnt, cnt = 1, cdcc, dcc[maxn];
int dfn[maxn], low[maxn], instk[maxn];
stack<int> stk;
struct edge {
    int to, nxt;
} e[maxn << 1];
void add(int u, int v) {
    e[++cnt] = edge{v, head[u]};
    head[u] = cnt;
}
void tarjan(int u, int pre) {
    dfn[u] = low[u] = ++Cnt;
    stk.push(u);
    instk[u] = 1;
    for (int i = head[u]; i; i = e[i].nxt) {
        if (i == (pre ^ 1))
            continue;
        int v = e[i].to;
        if (!dfn[v]) {
            tarjan(v, i);
            low[u] = min(low[u], low[v]);
        } else if (instk[v])
            low[u] = min(low[u], dfn[v]);
    }
    if (dfn[u] == low[u]) {
        cdcc++;
        int top;
        do {
            top = stk.top();
            stk.pop();
            dcc[top] = cdcc;
        } while (top != u);
    }
}