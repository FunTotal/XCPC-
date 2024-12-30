// 注意int128在特殊时候甚至可以宏定义int
inline void readint(
    __int128& X) {  // 建议用的时候把int128宏定义换成短一点的字母
    X = 0;
    int w = 0;
    char ch = 0;
    while (!isdigit(ch)) {
        w |= ch == '-';
        ch = getchar();
    }
    while (isdigit(ch))
        X = (X << 3) + (X << 1) + (ch ^ 48), ch = getchar();
    if (w)
        X = -X;
}
inline void printint(__int128 x) {
    if (x < 0)
        putchar('-'), x = -x;
    if (x >= 10)
        printint(x / 10);
    putchar('0' ^ (x % 10));
}