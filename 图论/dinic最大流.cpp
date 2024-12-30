// 复杂度O(n²m)
const int maxn = 2e2 + 10;
int S, T, HEAD[maxn], DIS[maxn], NOW[maxn], CNT = 1;
struct Node {
    int to, nxt;
    int val;
} E[maxn];
void ADD(int u, int v, int w) {
    E[++CNT] = Node{v, HEAD[u], w};
    HEAD[u] = CNT;
    E[++CNT] = Node{u, HEAD[v], 0};
    HEAD[v] = CNT;
}
int BFS() {
    // for(int i=1;i<=n;i++) DIS[i]=inf;
    memset(DIS, 0x3f, sizeof(DIS));  // 看范围决定memset或者for清空
    queue<int> q;
    q.push(S);
    DIS[S] = 0;
    NOW[S] = HEAD[S];
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int i = HEAD[u]; i; i = E[i].nxt) {
            int v = E[i].to;
            if (E[i].val > 0 && DIS[v] == inf) {
                q.push(v);
                NOW[v] = HEAD[v];
                DIS[v] = DIS[u] + 1;
                if (v == T)
                    return 1;
            }
        }
    }
    return 0;
}
int DFS(int u, int sum) {
    if (u == T)
        return sum;
    int k, res = 0;
    for (int i = NOW[u]; i && sum; i = E[i].nxt) {
        NOW[u] = i;
        int v = E[i].to;
        if (E[i].val > 0 && (DIS[v] == DIS[u] + 1)) {
            k = DFS(v, min(sum, E[i].val));
            if (k == 0)
                DIS[v] = inf;
            E[i].val -= k;
            E[i ^ 1].val += k;
            res += k;
            sum -= k;
        }
    }
    return res;
}
int dinic() {
    int res = 0;
    while (BFS())
        res += DFS(S, inf);
    return res;
}