#include <bits/stdc++.h>
// #define int long long
#define inf 0x3f3f3f3f
#define ll long long
#define pii pair<int, int>
#define db double
using namespace std;
const int maxn = 1e5 + 10;
const int mod = 998244353;
int head[maxn], cnt, in[maxn], num[maxn], dis[maxn];
int n, m;
struct edge {
    int to, nxt, w;
} e[maxn << 1];
void add(int u, int v, int w) {
    e[++cnt] = edge{v, head[u], w};
    head[u] = cnt;
}
bool spfa(int s) {
    queue<int> q;
    q.push(s);
    dis[s] = 0;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        if (num[u] > n)
            return 0;
        in[u] = 0;
        for (int i = head[u]; i; i = e[i].nxt) {
            int v = e[i].to;
            if (dis[u] + e[i].w < dis[v]) {
                dis[v] = dis[u] + e[i].w;
                if (!in[v]) {
                    q.push(v);
                    in[v] = 1;
                    num[v]++;
                }
            }
        }
    }
    return 1;
}
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    // 现在是解决x1 - x2 <= c, 如果是>=, 则距离负无穷，松弛操作取反
    memset(dis, 0x3f, sizeof(dis));
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        add(v, u, w);
    }
    for (int i = 1; i <= n; i++)
        add(n + 1, i, 0);
    if (spfa(n + 1) == 0) {
        cout << "NO" << endl;
        return 0;
    }
    for (int i = 1; i <= n; i++)
        cout << dis[i] << " ";
    // system("pause");
    return 0;
}