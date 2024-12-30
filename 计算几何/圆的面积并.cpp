#include <bits/stdc++.h>
// #define int long long
#define inf 0x3f3f3f3f
#define ll long long
#define pii pair<int, int>
#define tii tuple<int, int, int>
#define db double
#define all(a) a.begin(), a.end()
using namespace std;
const int maxn = 1e5 + 10;
const int mod = 998244353;
const db eps = 1e-8;
struct Circle {
    db x, y, r;
} cir[maxn];
bool operator<(const Circle& a, const Circle& b) {
    return a.r > b.r;
}
struct Seg {
    db l, r;
} seg[maxn], seg2[maxn];
bool operator<(const Seg& a, const Seg& b) {
    return a.l < b.l;
}
int n;
int sgn(db x) {
    if (fabs(x) < eps)
        return 0;
    return x > 0 ? 1 : -1;
}
map<db, db> mp;
db F(db x) {
    if (mp.count(x))
        return mp[x];
    int cnt = 0;
    db f;  // 弦长
    for (int i = 1; i <= n; i++) {
        f = cir[i].r * cir[i].r - (cir[i].x - x) * (cir[i].x - x);
        if (f <= eps)
            continue;
        f = sqrt(f);
        seg2[++cnt] = Seg{cir[i].y - f, cir[i].y + f};
    }
    sort(seg2 + 1, seg2 + 1 + cnt);
    db nowr = -1e9, res = 0;
    Seg now;
    for (int i = 1; i <= cnt; i++) {
        now = seg2[i];
        if (now.l > nowr) {
            res += now.r - now.l, nowr = now.r;
        } else if (now.r > nowr)
            res += now.r - nowr, nowr = now.r;
    }
    return mp[x] = res;
}
db simpson(db L, db R) {
    db mid = (L + R) / 2.0;
    return (R - L) * (F(L) + 4 * F(mid) + F(R)) / 6.0;
}
db work(db L, db R, db ans) {
    db mid = (L + R) / 2.0;
    db left = simpson(L, mid), right = simpson(mid, R);
    if (fabs(left + right - ans) < eps)
        return left + right;
    return work(L, mid, left) + work(mid, R, right);
}
int bei[maxn];
db dis(db x1, db y1, db x2, db y2) {
    return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}
void solve() {
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> cir[i].x >> cir[i].y >> cir[i].r;
    int cnt = 0;
    sort(cir + 1, cir + 1 + n);
    for (int i = 1; i <= n; i++) {
        if (bei[i])
            continue;
        cir[++cnt] = cir[i];
        for (int j = i + 1; j <= n; j++) {
            if (bei[j])
                continue;
            if (sgn(dis(cir[i].x, cir[i].y, cir[j].x, cir[j].y) + cir[j].r -
                    cir[i].r) != 1)
                bei[j] = 1;
        }
    }
    n = cnt;
    for (int i = 1; i <= n; i++) {
        seg[i] = Seg{cir[i].x - cir[i].r, cir[i].x + cir[i].r};
    }
    sort(seg + 1, seg + 1 + n);
    Seg now;
    db nowr = -1e9, ans = 0;
    for (int i = 1; i <= n; i++) {
        now = seg[i];
        if (now.l > nowr) {
            ans += work(now.l, now.r, simpson(now.l, now.r));
            nowr = now.r;
        } else if (now.r > nowr){
            ans += work(nowr, now.r, simpson(now.l, now.r));
            nowr = now.r;
        }
    }
    cout << fixed << setprecision(3) << ans << "\n";
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