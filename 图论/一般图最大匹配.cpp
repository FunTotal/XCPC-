struct FLOWER {
    // n点,m边，将图存进G[]后调用work(),ans记录最大匹配数，match记录每个点的匹配点
    int tot, tag[maxn], vis[maxn], match[maxn];
    int pre[maxn], fa[maxn], n = 0, ans = 0;
    vector<int> G[maxn];
    queue<int> q;
    int Find(int x) { return fa[x] == x ? fa[x] : fa[x] = Find(fa[x]); }
    int lca(int x, int y) {
        ++tot;
        while (1) {
            if (x) {
                x = Find(x);
                if (tag[x] == tot)
                    return x;
                tag[x] = tot;
                x = pre[match[x]];
            }
            swap(x, y);
        }
    }
    void flower(int x, int y, int p) {
        while (Find(x) != p) {
            pre[x] = y;
            y = match[x];
            vis[y] = 1;
            q.push(y);
            if (Find(x) == x)
                fa[x] = p;
            if (Find(y) == y)
                fa[y] = p;
            x = pre[y];
        }
    }
    void bfs(int st) {
        for (int i = 1; i <= n; ++i)
            pre[i] = vis[i] = 0, fa[i] = i;
        while (!q.empty())
            q.pop();
        vis[st] = 1;
        q.push(st);
        while (!q.empty()) {
            int x = q.front();
            q.pop();
            for (int y : G[x])
                if (Find(y) != Find(x) && vis[y] != 2) {
                    if (vis[y] == 1) {
                        int l = lca(x, y);
                        flower(x, y, l);
                        flower(y, x, l);
                        continue;
                    }
                    vis[y] = 2;
                    pre[y] = x;
                    if (!match[y]) {
                        int px = y;
                        while (px) {
                            int py = pre[px], pz = match[py];
                            match[px] = py;
                            match[py] = px;
                            px = pz;
                        }
                        ++ans;
                        return;
                    }
                    vis[match[y]] = 1;
                    q.push(match[y]);
                }
        }
    }
    void work() {
        tot = ans = 0;
        memset(tag, 0, sizeof(tag));
        memset(match, 0, sizeof(match));
        for (int i = 1; i <= n; ++i)
            if (!match[i])
                bfs(i);
    }
} Flower;
void add(int u, int v) {
    Flower.G[u].push_back(v);
    Flower.G[v].push_back(u);
}