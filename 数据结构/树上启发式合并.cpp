const int maxn = 1e5 + 10;
vector<int> G[maxn];
int cnt[maxn], ans[maxn], col[maxn], sum;  // sum全局变量，是题目询问的数值
int siz[maxn], son[maxn];                  // 区分重儿子
int dfn = 0, L[maxn], R[maxn], mp[maxn];  // dfn序写法,mp将dfn序映射回原先的点
void dfs1(int u, int f) {
    L[u] = ++dfn, mp[dfn] = u, siz[u] = 1;
    int maxson = 0;
    for (auto v : G[u]) {
        if (v == f)
            continue;
        dfs1(v, u);
        siz[u] += siz[v];
        if (siz[v] > maxson)
            maxson = siz[v], son[u] = v;
    }
    R[u] = dfn;
}
void add(int u) {  // 加入单点的贡献
    cnt[col[u]]++;
    if (cnt[col[u]] == 1)
        sum++;
}
void del(int u) {   // 删除单点的贡献
    cnt[col[u]]--;  // 一旦开始del，几乎都有都会清空，所以在外面一次性清零就可
    if (cnt[col[u]] == 0)
        sum--;
}
void dfs2(int u, int f, bool keep) {  // keep是否保留u子树对答案的贡献
    for (auto v : G[u])
        if (v != f && v != son[u])
            dfs2(v, u, 0);  // 先遍历轻儿子，计算答案，不保留贡献
    if (son[u])
        dfs2(son[u], u, 1);  // 再遍历重儿子，保留贡献
    // 然后加入u单点的贡献
    add(u);
    for (auto v : G[u])  // 第二次遍历轻儿子，保留贡献
        if (v != f && v != son[u])
            for (int i = L[v]; i <= R[v]; i++)
                add(mp[i]);
    for (auto it : q[u])
        ans[it] = sum;
    if (!keep) {
        for (int i = L[u]; i <= R[u]; i++)
            del(mp[i]);
        sum = 0;
    }
}