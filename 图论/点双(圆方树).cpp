int head[maxn], Cnt, cnt = 1, cvcc, n;
int dfn[maxn], low[maxn];
vector<int> G[maxn];
stack<int> stk;
struct edge {
    int to, nxt;
} e[maxn << 1];
void add(int u, int v) {
    e[++cnt] = edge{v, head[u]};
    head[u] = cnt;
}
void tarjan(int u, int pre) {  // 不考虑孤立点
    dfn[u] = low[u] = ++Cnt;
    stk.push(u);
    for (int i = head[u]; i; i = e[i].nxt) {
        if (i == (pre ^ 1))
            continue;
        int v = e[i].to;
        if (!dfn[v]) {
            tarjan(v, i);
            low[u] = min(low[u], low[v]);
            if (low[v] >= dfn[u]) {
                cvcc++;
                int top;
                do {
                    top = stk.top();
                    stk.pop();
                    G[top].push_back(n + cvcc);
                    G[n + cvcc].push_back(top);
                } while (top != v);
                G[n + cvcc].push_back(u);
                G[u].push_back(n + cvcc);
            }
        } else
            low[u] = min(low[u], dfn[v]);
    }
}