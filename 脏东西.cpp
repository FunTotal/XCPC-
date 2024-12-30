#define gc()                                                             \
    (is == it                 ? it = (is = in) + fread(in, 1, Q, stdin), \
     (is == it ? EOF : *is++) : *is++)
const int Q = (1 << 24) + 1;
char in[Q], *is = in, *it = in, c;
void read(long long& n) {  // 变态快读，不过只能读正数,而且好像读入量跟Q有关
    for (n = 0; (c = gc()) < '0' || c > '9';)
        ;
    for (; c <= '9' && c >= '0'; c = gc())
        n = n * 10 + c - 48;
}

#pragma GCC optimize("O3")
#pragma GCC target( \
    "sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native")
#pragma GCC optimize("inline", "fast-math", "unroll-loops", \
                     "no-stack-protector")

inline int red() {
    int data = 0;
    int w = 1;
    char ch = 0;
    ch = getchar();
    while (ch != '-' && (ch < '0' || ch > '9'))
        ch = getchar();
    if (ch == '-')
        w = -1, ch = getchar();
    while (ch >= '0' && ch <= '9')
        data = (data << 3) + (data << 1) + ch - '0', ch = getchar();
    return data * w;
}

ll clk() {
    return chrono::steady_clock::now().time_since_epoch().count();
}

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

tii tem;
get<0>(tem)