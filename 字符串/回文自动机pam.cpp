struct PAM {
	int tot, last, fail[maxn], c[maxn][27], len[maxn], cnt[maxn];
	int diff[maxn], slink[maxn]; //diff维护i到fail[i]的长度公差,slink跳到前一个等差数列的最长节点
	//len[i] 是节点i表示的回文串的长度, cnt[i]是 i 节点的回文串个数
	char s[maxn]; //下标从1开始的字符串
	PAM() { tot = last = fail[0] = 1, len[1] = -1;}	
	int getfail(int x, int i) {
		while (s[i - len[x] - 1] != s[i]) x = fail[x];
		return x;
	}
	void extend(char ch, int i) { //插入位置 i 的字符 ch
		s[i] = ch;
		int x = getfail(last, i), v = ch - 'a';
		if (!c[x][v]) {
			len[++tot] = len[x] + 2;
			int tem = getfail(fail[x], i);
			fail[tot] = c[tem][v];
			c[x][v] = tot; //必须放最后

			if (diff[tot] == diff[fail[tot]]) slink[tot] = slink[fail[tot]];
            else slink[tot] = fail[tot];
		}
		last = c[x][v];
		cnt[last]++;
	}
};
{ //回文dp优化模板
    for (int i = 1; i <= n; i++) {
        pam.insert(s[i - 1], i);
        for (int x = pam.lst; x > 1; x = pam.slink[x]) {
            g[x] = dp[i - pam.len[pam.slink[x]] - pam.diff[x]];
            if (pam.diff[x] == pam.diff[pam.fail[x]])
                g[x] = (g[x] + g[pam.fail[x]]) % mod;
        }
    }
}