#include <bits/stdc++.h>
#define int long long
#define ull unsigned long long
using namespace std;
const int maxn = 1e6 + 10;
vector<int> G[maxn];
set<ull> s;
ull Hash[maxn];
ull mask = 1e9 + 7;
ull shift(ull x) {
    x ^= mask;
    x ^= x << 13;
    x ^= x >> 7;
    x ^= x << 17;
    x ^= mask;
    return x;
}
void dfs(int u, int f) {
    Hash[u] = 1;
    for (auto v : G[u]) {
        if (v == f)
            continue;
        dfs(v, u);
        Hash[u] += shift(Hash[v]);
    }
    s.insert(Hash[u]);
}