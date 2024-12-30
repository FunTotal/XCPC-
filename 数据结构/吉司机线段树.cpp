struct JSJSegmentTree {
#define ls rt << 1
#define rs rt << 1 | 1
#define mid ((l + r) >> 1)
    struct Node1 {
        int mx1, mx1cnt, mx2, sum, laz;
    };
    vector<Node1> t;
    JSJSegmentTree(int n) { t.resize((n + 1) << 2); }
    void push_up(int rt) {
        t[rt].sum = t[ls].sum + t[rs].sum;
        if (t[ls].mx1 == t[rs].mx1) {
            t[rt].mx1 = t[ls].mx1;
            t[rt].mx1cnt = t[ls].mx1cnt + t[rs].mx1cnt;
            t[rt].mx2 = max(t[ls].mx2, t[rs].mx2);
        }
        else if (t[ls].mx1 > t[rs].mx1) {
            t[rt].mx1 = t[ls].mx1;
            t[rt].mx1cnt = t[ls].mx1cnt;
            t[rt].mx2 = max(t[ls].mx2, t[rs].mx1);
        } else {
            t[rt].mx1 = t[rs].mx1;
            t[rt].mx1cnt = t[rs].mx1cnt;
            t[rt].mx2 = max(t[ls].mx1, t[rs].mx2);
        }
    }
    void fun(int rt, int l, int r, int laz) {
        if (t[rt].mx1 <= laz)
            return;
        else if (t[rt].mx2 <= laz) {
            t[rt].sum -= t[rt].mx1cnt * t[rt].mx1;
            t[rt].mx1 = laz;
            t[rt].sum += t[rt].mx1cnt * t[rt].mx1;
        }
        if (t[rt].laz != -1)
            t[rt].laz = min(t[rt].laz, laz);
        else
            t[rt].laz = laz;
    }
    void push_down(int rt, int l, int r) {
        if (~t[rt].laz) {
            fun(ls, l, mid, t[rt].laz);
            fun(rs, mid + 1, r, t[rt].laz);
            t[rt].laz = -1;
        }
    }
    void build(int rt, int l, int r) {
        t[rt].laz = -1;
        if (l == r) {
            t[rt].mx1 = t[rt].sum = inf, t[rt].mx1cnt = 1;
            t[rt].mx2 = -inf;
            return;
        }
        build(ls, l, mid), build(rs, mid + 1, r);
        push_up(rt);
    }
    void modifymin(int rt, int l, int r, int p, int q, int k) {
        if (p > r || q < l)
            return;
        if (k >= t[rt].mx1)
            return;
        if (p <= l && r <= q && k > t[rt].mx2) {
            fun(rt, l, r, k);
            return;
        }
        push_down(rt, l, r);
        modifymin(ls, l, mid, p, q, k);
        modifymin(rs, mid + 1, r, p, q, k);
        push_up(rt);
    }
    int querysum(int rt, int l, int r, int p, int q) {
        if (p > r || q < l)
            return 0;
        if (p <= l && r <= q)
            return t[rt].sum;
        push_down(rt, l, r);
        return querysum(ls, l, mid, p, q) + querysum(rs, mid + 1, r, p, q);
    }
#undef ls
#undef rs
};