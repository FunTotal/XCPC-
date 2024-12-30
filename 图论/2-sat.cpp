#include <bits/stdc++.h>
// #define int long long
#define inf 0x3f3f3f3f
#define ll long long
#define pii pair<int, int>
#define db double
using namespace std;
const int maxn = 2e6 + 10;
const int mod = 998244353;

// 2-sat问题，建边是 a -> b，如果题目条件是别的，先通过离散数学，转化为 a - >
// b形式 建边时，记得逆否命题对称边也要建

vector<int> G[maxn];
stack<int> stk;
int dfn[maxn], low[maxn], instk[maxn], scc[maxn], cscc, Cnt;
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
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n, m;
    cin >> n >> m;
    while (m--) {
        int i, a, j, b;
        cin >> i >> a >> j >> b;
        G[2 * i - (a ^ 1)].push_back(2 * j - b);
        G[2 * j - (b ^ 1)].push_back(2 * i - a);
    }
    for (int i = 1; i <= 2 * n; i++)
        if (!dfn[i])
            tarjan(i);
    for (int i = 1; i <= n; i++)
        if (scc[2 * i] == scc[2 * i - 1]) {
            cout << "IMPOSSIBLE" << endl;
            return 0;
        }
    cout << "POSSIBLE" << endl;
    for (int i = 1; i <= n; i++) {
        if (scc[2 * i - 1] < scc[2 * i - 0])
            cout << 1 << " ";
        else
            cout << 0 << " ";
    }
    // system("pause");
    return 0;
}