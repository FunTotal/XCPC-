struct Node {
    int l, r;
    mutable int v;
    bool operator<(const Node& o) const { return l < o.l; }
};
set<Node> tree;
auto split(int pos) {  // 分裂操作
    auto it = tree.lower_bound(Node{pos, 0, 0});
    if (it != tree.end() && it->l == pos)
        return it;
    it--;
    int l = it->l, r = it->r, v = it->v;
    tree.erase(it);
    tree.insert(Node{l, pos - 1, v});
    return tree.insert(Node{pos, r, v}).first;
}
void assign(int l, int r, int v) {  // 区间赋值
    auto end = split(r + 1), begin = split(l);
    tree.erase(begin, end);
    tree.insert(Node{l, r, v});
}
void add(int l, int r, int v) {  // 区间加
    auto end = split(r + 1);
    for (auto it = split(l); it != end; it++)
        it->v += v;
}
int kth(int l, int r, int k) {  // 区间第k大
    auto end = split(r + 1);
    vector<pair<int, int>> v;
    for (auto it = split(l); it != end; it++)
        v.push_back(make_pair(it->v, it->r - it->l + 1));
    sort(v.begin(), v.end());
    for (int i = 0; i < v.size(); i++) {
        k -= v[i].second;
        if (k <= 0)
            return v[i].first;
    }
}