struct TRIE {
    int cnt = 1;
    int son[maxn * 30][2], siz[maxn * 30]; //第一维开节点个数
    void insert(int x) {
        int p = 1;
        for (int i = 30; ~i; i--) {
            int f = x >> i & 1;
            if (!son[p][f])
                son[p][f] = ++cnt;
            p = son[p][f];
            siz[p]++;
        }
    }
    int query(int x, int k) {  // 找 ^ x >= k 的数量, 看题意进行按位贪心, 走对应儿子
        int p = 1, res = 0;
        for (int i = 30; ~i && p; i--) {
            int f1 = x >> i & 1;
            int f2 = k >> i & 1;
            if (!f2)
                res += siz[son[p][f1 ^ 1]];
            p = son[p][f1 ^ f2];
        }
        return res + siz[p];
    }
} trie;