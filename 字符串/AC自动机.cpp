
// AC
// 自动机解决多个模式串和主串匹配的问题
// 如出现次数最多的模式串，出现了几个模式串
struct ACAM {
    queue<int> q;
    int c[maxn][26], fail[maxn], tot;
    void insert(string& str) {
        int len = str.length(), p = 0;
        for (int i = 0; i < len; i++) {
            int v = str[i] - 'a';
            if (!c[p][v])
                c[p][v] = ++tot;
            p = c[p][v];
        }
        //这里的p对应节点就是该字符串结束位置,通常会记录数量,或者字符串编号
    }
    void build() {  // 建立fail指针, 自动机上fail指针指向, 该节点表示串的最长后缀
        for (int i = 0; i < 26; i++)
            if (c[0][i])
                fail[c[0][i]] = 0, q.push(c[0][i]);
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int i = 0; i < 26; i++)
                if (c[u][i])
                    fail[c[u][i]] = c[fail[u]][i], q.push(c[u][i]);
                else
                    c[u][i] = c[fail[u]][i];
        }
    }
} ac;