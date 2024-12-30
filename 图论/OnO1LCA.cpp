#include <bits/stdc++.h>
using namespace std;

const int maxn = 5e5 + 5;
vector<int> G[maxn];
struct PlusMinusOneRMQ {
    // 使用方法 rmq.initLCA(root)
    const static int M = 9;
    int blocklen, block, Minv[maxn], F[maxn / M * 2 + 5][M << 1], T[maxn],
        f[1 << M][M][M], S[maxn];
    void init(int n) {  // 初始化
        blocklen = std::max(1, (int)(log(n * 1.0) / log(2.0)) / 2);
        block = n / blocklen + (n % blocklen > 0);
        int total = 1 << (blocklen - 1);
        for (int i = 0; i < total; i++) {
            for (int l = 0; l < blocklen; l++) {
                f[i][l][l] = l;
                int now = 0, minv = 0;
                for (int r = l + 1; r < blocklen; r++) {
                    f[i][l][r] = f[i][l][r - 1];
                    if ((1 << (r - 1)) & i) {
                        now++;
                    } else {
                        now--;
                        if (now < minv) {
                            minv = now;
                            f[i][l][r] = r;
                        }
                    }
                }
            }
        }
        T[1] = 0;
        for (int i = 2; i < maxn; i++) {
            T[i] = T[i - 1];
            if (!(i & (i - 1))) {
                T[i]++;
            }
        }
    }
    void initmin(int a[], int n) {
        for (int i = 0; i < n; i++) {
            if (i % blocklen == 0) {
                Minv[i / blocklen] = i;
                S[i / blocklen] = 0;
            } else {
                if (a[i] < a[Minv[i / blocklen]]) {
                    Minv[i / blocklen] = i;
                }
                if (a[i] > a[i - 1]) {
                    S[i / blocklen] |= 1 << (i % blocklen - 1);
                }
            }
        }
        for (int i = 0; i < block; i++) {
            F[i][0] = Minv[i];
        }
        for (int j = 1; (1 << j) <= block; j++) {
            for (int i = 0; i + (1 << j) - 1 < block; i++) {
                int b1 = F[i][j - 1], b2 = F[i + (1 << (j - 1))][j - 1];
                F[i][j] = a[b1] < a[b2] ? b1 : b2;
            }
        }
    }
    int querymin(int a[], int L, int R) {
        int idl = L / blocklen, idr = R / blocklen;
        if (idl == idr)
            return idl * blocklen + f[S[idl]][L % blocklen][R % blocklen];
        else {
            int b1 = idl * blocklen + f[S[idl]][L % blocklen][blocklen - 1];
            int b2 = idr * blocklen + f[S[idr]][0][R % blocklen];
            int buf = a[b1] < a[b2] ? b1 : b2;
            int c = T[idr - idl - 1];
            if (idr - idl - 1) {
                int b1 = F[idl + 1][c];
                int b2 = F[idr - 1 - (1 << c) + 1][c];
                int b = a[b1] < a[b2] ? b1 : b2;
                return a[buf] < a[b] ? buf : b;
            }
            return buf;
        }
    }
    int ncnt, dfn[maxn << 1], dep[maxn << 1], st[maxn];
    void dfs(int u, int fa, int d) {
        st[u] = ncnt;
        dfn[ncnt] = u;
        dep[ncnt] = d;
        ++ncnt;
        int v;
        for (auto v : G[u]) {
            if (v == fa)
                continue;
            dfs(v, u, d + 1);
            dfn[ncnt] = u;
            dep[ncnt] = d;
            ++ncnt;
        }
    }
    void initLCA(int root) {
        ncnt = 0;
        dfs(root, root, 0);
        init(ncnt);
        initmin(dep, ncnt);
    }
    int LCA(int u, int v) {
        int l = st[u], r = st[v];
        if (l > r)
            swap(l, r);
        return dfn[querymin(dep, l, r)];
    }
} rmq;