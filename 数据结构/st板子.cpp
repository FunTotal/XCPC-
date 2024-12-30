struct stable {
    vector<vector<int>> mylist;
    int n;
    int (*op)(int a, int b);
    stable(vector<int>& a, int (*f)(int, int)) {
        op = f;
        n = a.size() - 1;
        mylist = vector<vector<int>>(n + 1, vector<int>(__lg(n) + 1));
        for (int i = 1; i <= n; i++)
            mylist[i][0] = a[i];
        for (int j = 1; j <= __lg(n); j++)
            for (int i = 1; i <= n - (1 << j) + 1; i++)
                mylist[i][j] =
                    op(mylist[i][j - 1], mylist[i + (1 << j - 1)][j - 1]);
    }
    int query(int l, int r) {
        assert(l >= 1 && r <= n && l <= r);
        int len = __lg(r - l + 1);
        return op(mylist[l][len], mylist[r - (1 << len) + 1][len]);
    }
};