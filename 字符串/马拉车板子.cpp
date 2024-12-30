const int maxn = 2e7 + 10;
int d[maxn];   // d[i]表示以i为中心的最长回文子串长度
char s[maxn];  // s表示经过处理后的字符串,#a#b#,第一个#从0开始
int maxpos;    // maxpos记录处理后最后一个字符的下标
void init(string str) {  // 将字符串str预处理成s[]
    maxpos = str.length() * 2;
    s[0] = '#';
    for (int i = 0; str[i]; i++) {
        s[2 * i + 1] = str[i];
        s[2 * i + 2] = '#';
    }
}
// 求出str以每个字符为中心的最大回文子串长度,记录到d[]
void manacher(string str) {
    init(str);
    for (int i = 0, l = 0, r = -1; i <= maxpos; i++) {
        int k = (i > r) ? 1 : min(d[l + r - i], r - i);
        while (i - k >= 0 && i + k <= maxpos && s[i - k] == s[i + k])
            k++;  // 调用朴素算法
        k--;
        d[i] = k;
        if (i + k > r) {
            r = i + k;
            l = i - k;
        }
    }
}