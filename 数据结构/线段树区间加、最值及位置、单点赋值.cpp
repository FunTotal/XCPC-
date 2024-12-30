#include <bits/stdc++.h>
#define int long long
#define pii pair<int, int>
using namespace std;
const int maxn = 1e5 + 10;
const int mod = 998244353;
struct Seg {
#define ls rt << 1
#define rs rt << 1 | 1
    struct Node {
        pii mx, mn;
        int sum, laz;
    };
    vector<Node> t;
    vector<int> arr;
    Seg(int n) {
        t.resize(4 * n);
        arr.resize(n);
    }

    void fun(int rt, int l, int r, int k) {
        t[rt].sum += (r - l + 1) * k;
        t[rt].mn.first += k;
        t[rt].laz += k;
        t[rt].mx.first += k;
    }
    void push_down(int rt, int l, int r) {
        if (t[rt].laz) {
            int mid = (l + r) >> 1;
            fun(ls, l, mid, t[rt].laz);
            fun(rs, mid + 1, r, t[rt].laz);
            t[rt].laz = 0;
        }
    }
    void push_up(int rt) {
        t[rt].sum = t[ls].sum + t[rs].sum;
        t[rt].mn = min(t[ls].mn, t[rs].mn);
        t[rt].mx = max(t[ls].mx, t[rs].mx);
    }
    void build(int rt, int l, int r) {
        if (l == r) {
            t[rt].sum = arr[l];
            t[rt].laz = 0;
            t[rt].mx = t[rt].mn = pii(arr[l], l);
            return;
        }
        int mid = (l + r) >> 1;
        build(ls, l, mid), build(rs, mid + 1, r);
        push_up(rt);
    }
    void modify_add(int rt, int l, int r, int p, int q, int k) {
        if (l == p && r == q) {
            t[rt].sum += (r - l + 1) * k;
            t[rt].laz += k;
            t[rt].mn.first += k;
            t[rt].mx.first += k;
            return;
        }
        push_down(rt, l, r);
        int mid = (l + r) >> 1;
        if (q <= mid)
            modify_add(ls, l, mid, p, q, k);
        else if (p > mid)
            modify_add(rs, mid + 1, r, p, q, k);
        else
            modify_add(ls, l, mid, p, mid, k),
                modify_add(rs, mid + 1, r, mid + 1, q, k);
        push_up(rt);
    }
    void modify_ass(int rt, int l, int r, int pos, int val) {
        if (l == r) {
            t[rt].sum = t[rt].mn.first = t[rt].mx.first = val;
            return;
        }
        push_down(rt, l, r);
        int mid = (l + r) >> 1;
        if (pos <= mid)
            modify_ass(ls, l, mid, pos, val);
        else
            modify_ass(rs, mid + 1, r, pos, val);
        push_up(rt);
    }
    pii querymn(int rt, int l, int r, int p, int q) {
        if (l == p && r == q)
            return t[rt].mn;
        push_down(rt, l, r);
        int mid = (l + r) >> 1;
        if (q <= mid)
            return querymn(ls, l, mid, p, q);
        else if (p > mid)
            return querymn(rs, mid + 1, r, p, q);
        else
            return min(querymn(ls, l, mid, p, mid),
                       querymn(rs, mid + 1, r, mid + 1, q));
    }
    pii querymx(int rt, int l, int r, int p, int q) {
        if (l == p && r == q)
            return t[rt].mx;
        push_down(rt, l, r);
        int mid = (l + r) >> 1;
        if (q <= mid)
            return querymx(ls, l, mid, p, q);
        else if (p > mid)
            return querymx(rs, mid + 1, r, p, q);
        else
            return max(querymx(ls, l, mid, p, mid),
                       querymx(rs, mid + 1, r, mid + 1, q));
    }
    int querypos(int rt, int l, int r, int pos) {
        if (l == r)
            return t[rt].sum;
        push_down(rt, l, r);
        int mid = (l + r) >> 1;
        if (pos <= mid)
            return querypos(ls, l, mid, pos);
        else
            return querypos(rs, mid + 1, r, pos);
    }
};