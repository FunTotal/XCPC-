
struct SegmentTree {
#define ls rt << 1
#define rs rt << 1 | 1
#define mid ((l + r) >> 1)
    struct Node {
        int sum, laz;
    };
    vector<Node> t;
    SegmentTree(int n) { t.resize((n + 1) << 2); }
    void push_up(int rt) { t[rt].sum = t[ls].sum + t[rs].sum; }
    void fun(int rt, int l, int r, int laz) {
        t[rt].sum += (r - l + 1) * laz;
        t[rt].laz += laz;
    }
    void push_down(int rt, int l, int r) {
        if (t[rt].laz) {  // 如果有标记
            fun(ls, l, mid, t[rt].laz);
            fun(rs, mid + 1, r, t[rt].laz);
            t[rt].laz = 0;
        }
    }
    void build(int rt, int l, int r) {
        t[rt].laz = 0;
        if (l == r) {
            t[rt].sum = arr[l];
            return;
        }
        build(ls, l, mid);
        build(rs, mid + 1, r);
        push_up(rt);
    }
    void modify(int rt, int l, int r, int p, int q, int k) {
        if (q < l || p > r)
            return;
        if (p <= l && r <= q) {
            t[rt].sum += k * (r - l + 1);
            t[rt].laz += k;
            return;
        }
        push_down(rt, l, r);
        modify(ls, l, mid, p, q, k);
        modify(rs, mid + 1, r, p, q, k);
        push_up(rt);
    }
    int query(int rt, int l, int r, int p, int q) {
        if (q < l || p > r)
            return 0;
        if (p <= l && r <= q)
            return t[rt].sum;
        push_down(rt, l, r);
        return query(ls, l, mid, p, q) + query(rs, mid + 1, r, p, q);
    }
};