#include <bits/stdc++.h>
#define int long long
#define inf 0x3f3f3f3f
#define ll long long
using namespace std;
const int maxn = 1e5 + 10;
const int maxlen = 1e7 + 100;
int n, m, query[110], ans[110];  // 离线查询答案
int total, head[maxn], siz[maxn], ctr, dis[maxn], cnt, maxson[maxn];
int del[maxn], tmp[maxlen], lens[maxlen], q[maxlen];
// del表示结点是否删除，tmp存储当前dfs到的分支中存在的路径距离
// lens是其他子树中存在的距离，q存储都用过哪些距离，该分治结束后撤销操作
struct edge {
    int to, nxt, w;
} e[maxn << 1];
void add(int u, int v, int w) {
    e[++cnt].to = v;
    e[cnt].nxt = head[u];
    e[cnt].w = w;
    head[u] = cnt;
}
void get_root(int u, int f) {  // total为当前分治的总大小
    siz[u] = 1;
    maxson[u] = 0;
    int mss = 0;
    for (int i = head[u]; i; i = e[i].nxt) {
        int v = e[i].to;
        if (v == f || del[v])
            continue;
        get_root(v, u);
        maxson[u] = max(maxson[u], siz[v]);
        siz[u] += siz[v];
    }
    maxson[u] = max(maxson[u], total - siz[u]);
    if (maxson[u] < maxson[ctr])
        ctr = u;
}
void get_dis(int u, int f) {
    tmp[++tmp[0]] = dis[u];
    for (int i = head[u]; i; i = e[i].nxt) {
        int v = e[i].to, w = e[i].w;
        if (del[v] || v == f)
            continue;
        dis[v] = dis[u] + w;
        get_dis(v, u);
    }
}
void calc(int u) {  // 第二次dfs，一般题目主要改这个地方
    int p = 0;
    for (int i = head[u]; i; i = e[i].nxt) {
        int v = e[i].to, w = e[i].w;
        if (del[v])
            continue;
        tmp[0] = 0;
        dis[v] = w;
        get_dis(v, u);
        for (int j = tmp[0]; j; j--) {
            for (int k = 1; k <= m; k++)
                if (query[k] >= tmp[j])
                    ans[k] |= lens[query[k] - tmp[j]];
        }
        for (int j = tmp[0]; j; j--)
            q[++p] = tmp[j], lens[tmp[j]] = 1;
    }
    for (int i = p; i; i--)
        lens[q[i]] = 0;
}
void solve(int u) {
    del[u] = lens[0] = 1;
    calc(u);
    for (int i = head[u]; i; i = e[i].nxt) {
        int v = e[i].to;
        if (del[v])
            continue;
        total = siz[v];
        maxson[ctr = 0] = inf;
        get_root(v, 0);
        solve(ctr);
    }
}
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin >> n >> m;
    for (int i = 1; i < n; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        add(u, v, w);
        add(v, u, w);
    }
    for (int i = 1; i <= m; i++)
        cin >> query[i];
    maxson[ctr = 0] = inf;
    total = n;
    get_root(1, 0);
    solve(ctr);
    for (int i = 1; i <= m; i++)
        if (ans[i])
            cout << "AYE" << endl;
        else
            cout << "NAY" << endl;
    // system("pause");
    return 0;
}