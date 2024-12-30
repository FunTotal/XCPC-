struct tree {
    int sum = 0, laz1 = 0, laz2 = 1;  // 当前结点的值和懒标记
} t[maxn << 2];
void push_up(int rt) {
    t[rt].sum = (t[ls].sum + t[rs].sum) % mod;
}
void build(int rt, int l, int r) {  // 建树
    t[rt].laz1 = 0, t[rt].laz2 = 1;
    if (l == r) {  // 是叶子结点
        t[rt].sum = arr[l];
        return;
    }
    int mid = l + r >> 1;
    build(ls, l, mid);
    build(rs, mid + 1, r);
    push_up(rt);
}
void fun(int rt, int l, int r, int laz1, int laz2) {
    t[rt].sum = (t[rt].sum * laz2 % mod + laz1 * (r - l + 1) % mod) % mod;
    t[rt].laz1 = (t[rt].laz1 * laz2 % mod + laz1) % mod;
    t[rt].laz2 = t[rt].laz2 * laz2 % mod;
}
void push_down(int rt, int l, int r) {
    if (t[rt].laz1 || t[rt].laz2 != 1) {
        int mid = (l + r) >> 1;
        fun(ls, l, mid, t[rt].laz1, t[rt].laz2);
        fun(rs, mid + 1, r, t[rt].laz1, t[rt].laz2);
        t[rt].laz1 = 0, t[rt].laz2 = 1;
    }
}
void modify_add(int rt, int l, int r, int p, int q, int k) {  // 区间增加k
    if (p > r || q < l)
        return;
    if (p <= l && r <= q) {
        t[rt].sum = (t[rt].sum + (r - l + 1) * k % mod) % mod;
        t[rt].laz1 = (t[rt].laz1 + k) % mod;
        return;
    }
    push_down(rt, l, r);
    int mid = (l + r) >> 1;
    modify_add(ls, l, mid, p, q, k);
    modify_add(rs, mid + 1, r, p, q, k);
    push_up(rt);
}
void modify_mul(int rt, int l, int r, int p, int q, int k) {  // 区间乘法
    if (q < l || p > r)
        return;
    if (p <= l && r <= q) {
        t[rt].sum = t[rt].sum * k % mod;
        t[rt].laz1 = t[rt].laz1 * k % mod;
        t[rt].laz2 = t[rt].laz2 * k % mod;
        return;
    }
    push_down(rt, l, r);
    int mid = (l + r) >> 1;
    modify_mul(ls, l, mid, p, q, k);
    modify_mul(rs, mid + 1, r, p, q, k);
    push_up(rt);
}
int query(int rt, int l, int r, int p, int q) {
    if (q < l || p > r)
        return 0;
    if (p <= l && r <= q)
        return t[rt].sum;
    push_down(rt, l, r);
    int res = 0, mid = (l + r) >> 1;
    res += query(ls, l, mid, p, q);
    res %= mod;
    res += query(rs, mid + 1, r, p, q);
    res %= mod;
    return res;
}