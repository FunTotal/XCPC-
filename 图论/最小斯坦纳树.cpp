#include <bits/stdc++.h>
// 复杂度 n* 3 ^ k + mlogm * 2^k
#define pii pair<int, int>
using namespace std;
const int maxn = 1e3 + 10;
int head[maxn], cnt, dp[110][1025], ky[maxn];
int vis[maxn];
struct edge {
    int to, nxt, w;
} e[maxn << 1];
void add(int u, int v, int w) {
    e[++cnt] = edge{v, head[u], w};
    head[u] = cnt;
}
priority_queue<pii, vector<pii>, greater<pii>> q;
void dijkstra(int s) {
    memset(vis, 0, sizeof vis);
    while (!q.empty()) {
        auto [d, u] = q.top();
        q.pop();
        if (vis[u])
            continue;
        vis[u] = 1;
        for (int i = head[u]; i; i = e[i].nxt) {
            int v = e[i].to;
            if (dp[v][s] > dp[u][s] + e[i].w) {
                dp[v][s] = dp[u][s] + e[i].w;
                q.push(pii(dp[v][s], v));
            }
        }
    }
}
signed main() {
    int n, m, k;
    cin >> n >> m >> k;
    for (int i = 1; i <= m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        add(u, v, w), add(v, u, w);
    }
    memset(dp, 0x3f, sizeof dp);
    for (int i = 1; i <= k; i++) {
        int u;
        cin >> u;
        ky[i] = u;
        dp[u][1 << (i - 1)] = 0;
    }
    for (int s = 1; s < (1 << k); s++) {
        for (int i = 1; i <= n; i++) {
            for (int subs = s & (s - 1); subs; subs = (subs - 1) & s)
                dp[i][s] = min(dp[i][s], dp[i][subs] + dp[i][s ^ subs]);
            if (dp[i][s] != inf)
                q.push(pii(dp[i][s], i));
        }
        dijkstra(s);
    }
    cout << dp[ky[1]][(1 << k) - 1] << endl;
    return 0;
}