struct SegmentTree {
#define ls rt << 1
#define rs rt << 1 | 1
#define mid ((l + r) >> 1)
    struct Node {
        int sum, laz;
    };
    vector<Node> t;
    SegmentTree(int n) { t.resize((n + 1) << 2); }
    SegmentTree() { ; }
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
        if (p <= mid) modify(ls, l, mid, p, q, k);
        if (q > mid) modify(rs, mid + 1, r, p, q, k);
        push_up(rt);
    }
    int query(int rt, int l, int r, int p, int q) {
        if (q < l || p > r) return 0;
        if (p <= l && r <= q) return t[rt].sum;
        push_down(rt, l, r);
        int ans = 0;
        if (p <= mid) ans += query(ls, l, mid, p, q);
        if (q > mid) ans += query(rs, mid + 1, r, p, q);
        return ans;
    }
} seg;
struct HLD {
    int dep[maxn], fa[maxn], mp[maxn], siz[maxn], n;
    int ncnt, son[maxn], top[maxn], L[maxn], R[maxn];
    void dfs1(int u, int f, int deep) {
        dep[u] = deep, siz[u] = 1, fa[u] = f;
        for (auto v : G[u]) {
            if (v == f) continue;
            dfs1(v, u, deep + 1);
            siz[u] += siz[v];
            if (siz[son[u]] < siz[v])
                son[u] = v;
        }
    }
    void dfs2(int u, int topf) {
        L[u] = ++ncnt, top[u] = topf, mp[ncnt] = u;
        if (!son[u]) {
            R[u] = ncnt;
            return;
        }
        dfs2(son[u], topf);
        for (auto v : G[u]) {
            if (v == fa[u] || v == son[u]) continue;
            dfs2(v, v);
        }
        R[u] = ncnt;
    }
    void modify(int u, int v, int x) {
        while (top[u] != top[v]) {
            if (dep[top[u]] < dep[top[v]]) swap(u, v);
            seg.modify(1, 1, n, L[top[u]], L[u], x);
            u = fa[top[u]];
        }
        if (dep[u] < dep[v]) swap(u, v);
        seg.modify(1, 1, n, L[v], L[u], x);
        return;
    }
    int query(int u, int v) {
        int res = 0;
        while (top[u] != top[v]) {
            if (dep[top[u]] < dep[top[v]]) swap(u, v);
            res += seg.query(1, 1, n, L[top[u]], L[u]);
            u = fa[top[u]];
        }
        if (dep[u] < dep[v]) swap(u, v);
        res += seg.query(1, 1, n, L[v], L[u]);
        return res;
    }
} hld;