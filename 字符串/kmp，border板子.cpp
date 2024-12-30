const int maxn = 1e5 + 10;
int nxt[maxn];
void getnxt(string str) {  // 得到str的next数组，next数组为对应位置的最长border
    nxt[0] = 0;
    for (int i = 1, j = 0; i < str.length(); i++) {
        while (j && str[i] != str[j])
            j = nxt[j - 1];
        if (str[i] == str[j])
            j++;
        nxt[i] = j;
    }
}
void kmp(string a, string b) {  // a是长的串，b是短的串，要求的是b的next数组
    getnxt(b);
    for (int i = 0, j = 0; i < a.length(); i++) {
        while (j && a[i] != b[j])
            j = nxt[j - 1];  // 不断前移j指针，直到成功匹配或移到头为止
        if (a[i] == b[j])
            j++;  // 当前位匹配成功，j指针右移
        if (j == b.length()) {
            // 可以对每次成功的匹配进行对应操作
            cout << i - j + 2 << endl;  // 这里是输出b在a中的每一个位置
            j = nxt[j - 1];  // 成功时也按失配处理，就可以多次匹配
        }
    }
}