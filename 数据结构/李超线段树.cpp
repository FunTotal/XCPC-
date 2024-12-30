struct LCtree {
    //维护的是最小值
    int tot = 0;
#define lson t[rt].ls
#define rson t[rt].rs
#define mid ((l + r) >> 1)
    struct line {
        int rt, b;
        int calc(int x) { return rt * x + b; }
    };
    struct tree {
        line l;
        int ls, rs;
    } t[maxn << 2];
    void insert(int& rt, int l, int r, line g) {
        if (!rt) {
            rt = ++tot;
            t[rt].l = g;
            return;
        }
        if (l == r) {
            if (g.calc(l) < t[rt].l.calc(l)) t[rt].l = g;
            return;
        }
        if (g.calc(mid) < t[rt].l.calc(mid)) swap(t[rt].l, g);
        if (g.rt > t[rt].l.rt) insert(lson, l, mid, g);
        else if (g.rt < t[rt].l.rt) insert(rson, mid + 1, r, g);
    }
    int query(int rt, int l, int r, int x) {
        if (!rt) return 1e18;
        if (l == r) return t[rt].l.calc(x);
        if (x <= mid) return min(query(lson, l, mid, x), t[rt].l.calc(x));
        else return min(query(rson, mid + 1, r, x), t[rt].l.calc(x));
    }
} seg;