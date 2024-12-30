struct SAM {
    int tot, lst, len[maxn << 1], fa[maxn << 1], c[maxn << 1][27];
    int cnt[maxn << 1];
    SAM() { tot = lst = 1; }
    int id[maxn << 1], tong[maxn];
    void topo() { //基数排序后, 逆序枚举为拓扑序
        for (int i = 1; i <= tot; i++) tong[len[i]]++;
        for (int i = 1; i <= tot; i++) tong[i] += tong[i - 1];
        for (int i = tot; i; i--) id[tong[len[i]]--] = i;
    }
    void extend(char ch) {
        int x = ch - 'a', cur = ++tot, u;
        cnt[cur] = 1, len[cur] = len[lst] + 1;
        for (u = lst; u && !c[u][x]; u = fa[u]) c[u][x] = cur;
        if (!u) fa[cur] = 1;
        else {
            int v = c[u][x];
            if (len[v] == len[u] + 1) fa[cur] = v;
            else {
                int clone = ++tot;
                len[clone] = len[u] + 1, fa[clone] = fa[v];
                memcpy(c[clone], c[v], sizeof c[v]);  // 时间复杂度在这个地方
                for (; u && c[u][x] == v; u = fa[u])
                    c[u][x] = clone;
                fa[cur] = fa[v] = clone;
            }
        }
        lst = cur;
    }
} sam;