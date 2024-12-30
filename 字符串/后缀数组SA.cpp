struct SufArray {
    // rk[i] i 的排名  sa[i] 第i名
    // 字符串的序号  +k 就是往后走k个
    int rk[maxn + 10], sa[maxn + 10], n, lstrk[maxn + 10], lstsa[maxn], w,
        m = 127, cnt[maxn], h[maxn], f[maxn][20];
    string s;

#define siz n * sizeof(int)
    void init() {
        m = 127;
        n = s.length();
        memset(cnt, 0, sizeof cnt);
        memset(sa, 0, sizeof sa);
        memset(rk, 0, sizeof rk);
        memset(h, 0, sizeof h);
        for (int i = 1; i <= n; ++i) ++cnt[rk[i] = s[i - 1]];
        for (int i = 1; i <= m; ++i) cnt[i] += cnt[i - 1];
        for (int i = n; i >= 1; --i) sa[cnt[rk[i]]--] = i;
        memcpy(lstrk + 1, rk + 1, siz);
        for (int p = 0, i = 1; i <= n; ++i)
            if (lstrk[sa[i]] == lstrk[sa[i - 1]])
                rk[sa[i]] = p;
            else
                rk[sa[i]] = ++p;
        for (w = 1; w < n; w <<= 1, m = n) {
            for (int p = 0, i = n; i >= n - w + 1; --i)
                lstsa[++p] = i;
            for (int p = w, i = 1; i <= n; ++i)
                if (sa[i] > w) lstsa[++p] = sa[i] - w;
            memset(cnt, 0, sizeof cnt);
            for (int i = 1; i <= n; ++i) ++cnt[rk[lstsa[i]]];
            for (int i = 1; i <= m; ++i) cnt[i] += cnt[i - 1];
            for (int i = n; i >= 1; --i) sa[cnt[rk[lstsa[i]]]--] = lstsa[i];
            memcpy(lstrk + 1, rk + 1, siz);
            for (int p = 0, i = 1; i <= n; ++i)
                if (lstrk[sa[i]] == lstrk[sa[i - 1]] && lstrk[sa[i] + w] == lstrk[sa[i - 1] + w])
                    rk[sa[i]] = p;
                else
                    rk[sa[i]] = ++p;
        }
        for (int i = 1, k = 0; i <= n; ++i) {
            if (rk[i] == 0) continue;
            if (k) --k;
            while (s[i + k - 1] == s[sa[rk[i] - 1] + k - 1]) ++k;
            h[rk[i]] = k;
        }
        
        memset(f, 0x3f, sizeof f);
        for (int i = 1; i <= n; ++i)
            f[i][0] = h[i];
        for (int j = 1; (1 << j) <= n; ++j)
            for (int i = 1; i <= n - (1 << j) + 1; ++i)
                f[i][j] = min(f[i][j - 1], f[i + (1 << (j - 1))][j - 1]);
    }
    int lcp(int x, int y) {  // 后缀x和后缀y的最长公共前缀
        if (x == y)
            return n - y + 1;
        x = rk[x], y = rk[y];
        if (x >= y) swap(x, y);
        int k = log2(y - (x + 1) + 1);
        return min(f[x + 1][k], f[y - (1 << k) + 1][k]);
    }
} SA;