struct BIT {
    vector<int> v;
    int len;
    int lowbit(int x) { return x & (-x); }
    BIT(int n) {
        len = n;
        v.resize(n + 1);
    }
    void update(int i, int x) {
        for (int pos = i; pos <= len; pos += lowbit(pos))
            v[pos] += x;
    }
    int ask(int i) {
        int res = 0;
        for (int pos = i; pos; pos -= lowbit(pos))
            res += v[pos];
        return res;
    }
    void clear() {
        for (int i = 0; i <= len; i++)
            v[i] = 0;
    }
};
int find_first(int sum) {  // 最小的大于等于sum的位置
    int ans = 0;
    int val = 0;
    for (int i = __lg(len); i >= 0; i--) {
        if ((ans | (1 << i)) <= len && val + tree[ans | (1 << i)] < sum) {
            ans |= 1 << i;
            val += tree[ans];
        }
    }
    return ans + 1;
}
