// 取余最好最后取余后加mod再取余一次
const int mod = 998244353;
const int maxm = 10;
struct Node {
    int arr[maxm][maxm];
    Node() { memset(arr, 0, sizeof arr); }
};
Node operator*(Node a, Node b) {
    Node res;
    for (int i = 0; i < maxm; i++)
        for (int j = 0; j < maxm; j++)
            for (int k = 0; k < maxm; k++)
                res.arr[i][j] =
                    (res.arr[i][j] + a.arr[i][k] * b.arr[k][j] % mod) % mod;
    return res;
}
Node ksm(Node a, int b) {
    Node res;
    for (int i = 0; i < maxm; i++)
        res.arr[i][i] = 1;
    for (; b; b >>= 1, a = a * a)
        if (b & 1)
            res = res * a;
    return res;
}

struct mat {
    vector<vector<int>> arr;
};
mat operator*(mat a, mat b) {
    int n = a.arr.size(), m = b.arr[0].size();
    vector<vector<int>> res(n, vector<int>(m));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) {
            for (int k = 0; k < a.arr[0].size(); k++)
                res[i][j] += a.arr[i][k] * b.arr[k][j];
        }
    return mat{res};
}