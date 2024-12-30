struct SAM{
    int tot, fa[maxn], len[maxn], c[maxn][26];
    SAM(){tot = 1;}
    int id[maxn << 1], tong[maxn];
    void topo() { //基数排序后, 逆序枚举为拓扑序
        for (int i = 1; i <= tot; i++) tong[len[i]]++;
        for (int i = 1; i <= tot; i++) tong[i] += tong[i - 1];
        for (int i = tot; i; i--) id[tong[len[i]]--] = i;
    }
    int extend(char chr, int last){
        int ch = chr - 'a';
        if (c[last][ch]) {
            int p = last, x = c[p][ch];
            if (len[p] + 1 == len[x]) return x;
            else {
                int y = ++tot;
                len[y] = len[p] + 1;
                memcpy(c[y], c[x], sizeof c[y]);
                while (p && c[p][ch] == x)
                    c[p][ch] = y, p = fa[p];
                fa[y] = fa[x], fa[x] = y;
                return y; 
            }
        }
        int z = ++tot, p = last;
        len[z] = len[last] + 1;
        while (p && !c[p][ch])
            c[p][ch] = z, p = fa[p];
        if (!p) fa[z] = 1;
        else {
            int x = c[p][ch];
            if (len[p] + 1 == len[x]) fa[z] = x;
            else {
                int y = ++tot;
                len[y] = len[p] + 1;
                memcpy(c[y], c[x], sizeof c[y]);
                while (p && c[p][ch] == x)
                    c[p][ch] = y, p = fa[p];
                fa[y] = fa[x], fa[z] = fa[x] = y;
            }
        }
        return z;
    }
} sam;