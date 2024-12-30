#include <bits/stdc++.h>
// #define int long long
#define inf 0x3f3f3f3f
#define ll long long
#define pii pair<int, int>
#define tii tuple<int, int, int>
#define db double
#define all(a) a.begin(), a.end()
using namespace std;
const int maxn = 1e3 + 10;
const int mod = 998244353;
int arr[maxn];
struct Trie {
    int cnt, root[maxn * 2];
    struct Node {
        int siz, son[2];
    };
    Node t[maxn * 30];
    void insert(int& now, int pre, int x) {
        now = ++cnt;
        t[now] = t[pre];
        int p1 = now, p2 = pre;
        for (int i = 29; ~i; i--) {
            int bit = x >> i & 1;
            t[p1].son[bit] = ++cnt;
            t[cnt] = t[t[p2].son[bit]];
            t[cnt].siz++;
            p1 = t[p1].son[bit];
            p2 = t[p2].son[bit];
        }
    }
    int query(int pre, int now, int x) {
        int ans = 0;
        for (int i = 29; ~i; i--) {
            int bit = x >> i & 1;
            if (t[t[now].son[bit ^ 1]].siz - t[t[pre].son[bit ^ 1]].siz > 0) {
                ans |= 1 << i;
                pre = t[pre].son[bit ^ 1], now = t[now].son[bit ^ 1];
            } else {
                pre = t[pre].son[bit], now = t[now].son[bit];
            }
        }
        return ans;
    }
} trie;
void solve() {
    trie.insert(trie.root[0], trie.root[0], 0);
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
        arr[i] ^= arr[i - 1];
        trie.insert(trie.root[i], trie.root[i - 1], arr[i]);
    }
    while (m--) {
        char op;
        cin >> op;
        if (op == 'A') {
            int x;
            cin >> x;
            arr[++n] = x;
            arr[n] ^= arr[n - 1];
            trie.insert(trie.root[n], trie.root[n - 1], arr[n]);
        } else {
            int l, r, x;
            cin >> l >> r >> x;
            cout << trie.query(trie.root[l - 1], trie.root[r], x ^ arr[n])
                 << "\n";
        }
    }
}
signed main() {
    // freopen("1.in", "r", stdin);
    // freopen("1.out", "w", stdout);
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int t = 1;
    // cin >> t;
    while (t--)
        solve();
    return 0;
}