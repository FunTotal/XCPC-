struct exKMP {
    int z[maxn]; //下标从0开始, z[i]表示字符串[i, n] 和字符串[1, n] 的最长公共前缀
    void get_z(string& c) {
        int len = c.length();
        int p = 0, k = 1, l;
        z[0] = len;
        while (p + 1 < len && c[p] == c[p + 1]) p++;
        z[1] = p;
        for (int i = 2; i < len; i++) {
            p = k + z[k] - 1;
            l = z[i - k];
            if (i + l <= p) z[i] = l;
            else {
                int j = max(0, p - i + 1);
                while (i + j < len && c[i + j] == c[j]) j++;
                z[i] = j;
                k = i;
            }
        }
    }
} Z;