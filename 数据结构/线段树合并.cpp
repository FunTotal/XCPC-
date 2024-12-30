struct SegmentTree {
    struct Node {
        int ls, rs, sum;
    };
#define lson t[rt].ls
#define rson t[rt].rs
#define mid ((l + r) >> 1)
    Node t[maxn << 5];
    int tot = 0;
    void push_up(int rt) {t[rt].sum = t[lson].sum + t[rson].sum;}
    int Merge(int x, int y, int l, int r) { //如果可以破坏信息，就不要++tot，返回x
        if (!x || !y) return x | y;
        int now = ++tot;
        if (l == r) {
            t[now].sum = t[x].sum + t[y].sum;
            return now;
        }
        t[now].ls = Merge(t[x].ls, t[y].ls, l, mid);
        t[now].rs = Merge(t[x].rs, t[y].rs, mid + 1, r);
        push_up(now);
        return now;
    }
    void modify(int& rt, int l, int r, int pos) {
        if (!rt) rt = ++tot;
        if (l == r) {
            t[rt].sum++;
            return;
        }
        if (pos <= mid) modify(lson, l, mid, pos);
        else modify(rson, mid + 1, r, pos);
        push_up(rt);
    }
    int query(int rt, int l, int r, int p, int q) {
        if (!rt || p > r || q < l) return 0;
        if (p <= l && r <= q) return t[rt].sum;
        return query(lson, l, mid, p, q) + query(rson, mid + 1, r, p , q);
    }
} seg;