// 注意复杂度O(nm)，一般也就500
using namespace std;
const int maxn = 5e2 + 10;
int vis[maxn], match[maxn];  // 都是针对右边的点
vector<int> G[maxn];         // 存左边的点到右边点的边
int n, m, e;  // n是左边点个数，m右边点个数，e是边数
int dfs(int u) {
    for (auto v : G[u]) {
        if (!vis[v]) {
            vis[v] = 1;
            if (!match[v] || dfs(match[v])) {
                match[v] = u;  // 更改v的匹配点为u
                return 1;      // 找到了一个增广路
            }
        }
    }
    return 0;
}
int main() {
    cin >> n >> m >> e;
    int ans = 0;
    for (int i = 1; i <= m; i++) {
        cin >> u >> v;
        G[u].push_back(v);
    }
    for (int i = 1; i <= n; i++) {
        ans += dfs(i);
        memset(vis, 0, sizeof(vis));  // 每次都要memset注意
    }
    cout << ans << endl;
    return 0;
}