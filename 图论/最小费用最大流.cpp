const int maxn = 5e3 + 10;
const int maxm = 5e4 + 10;
int S, T, DIS[maxn], PRE[maxn], LST[maxn], FLOW[maxn], VIS[maxn];
int maxFLOW, minCOST;  // 需要的最大流、最小费用
struct Node {
    int to, nxt;
    int FLOW, DIS;  // FLOW流量,DIS花费
} E[maxm << 1];
int CNT = 1, HEAD[maxn];
void add(int u, int v, int FLOW, int DIS) {  // 建反向边，花费也是相反数
    E[++CNT].to = v;
    E[CNT].FLOW = FLOW;
    E[CNT].nxt = HEAD[u];
    E[CNT].DIS = DIS;
    HEAD[u] = CNT;
    E[++CNT].to = u;
    E[CNT].FLOW = 0;
    E[CNT].nxt = HEAD[v];
    E[CNT].DIS = -DIS;
    HEAD[v] = CNT;
}
int spfa() {
    // 注意这里的清空是所有点，包括s和t
    for (int i = 1; i <= n; i++)
        DIS[i] = inf, FLOW[i] = inf, VIS[i] = 0;
    queue<int> q;
    q.push(S);
    VIS[S] = 1;
    DIS[S] = 0;
    PRE[T] = -1;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        VIS[u] = 0;
        for (int i = HEAD[u]; i; i = E[i].nxt) {
            int v = E[i].to;
            if (E[i].FLOW > 0 && DIS[v] > DIS[u] + E[i].DIS) {
                DIS[v] = DIS[u] + E[i].DIS;
                PRE[v] = u;
                LST[v] = i;
                FLOW[v] = min(FLOW[u], E[i].FLOW);
                if (!VIS[v]) {
                    VIS[v] = 1;
                    q.push(v);
                }
            }
        }
    }
    return PRE[T] != -1;
}
void MCMF() {  // min cost max FLOW
    while (spfa()) {
        int now = T;
        maxFLOW += FLOW[T];
        minCOST += FLOW[T] * DIS[T];
        while (now != S) {
            E[LST[now]].FLOW -= FLOW[T];
            E[LST[now] ^ 1].FLOW += FLOW[T];
            now = PRE[now];
        }
    }
}