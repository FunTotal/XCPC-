struct FWT {
    const int P = 998244353;
    int n; //序列长度, 得是2的幂次
    //子集卷积(下标恰好拼起来的乘积和, 需要多记录一位i的popcount)
    //h[i][k] = \sigma a[j][k] * b[i - j][k], 之后再每一位Or的逆运算
    vector<int> Or(vector<int> b, int type = 1) {  // 逆运算type = -1
        vector<int> a = b;
        a.resize(n);
        for (ll x = 2; x <= n; x <<= 1) {
            ll k = x >> 1;
            for (ll i = 0; i < n; i += x) {
                for (ll j = 0; j < k; j++) {
                    a[i + j + k] = (a[i + j + k] + a[i + j] * type + P) % P;
                }
            }
        }
        return a;
    }
    vector<int> And(vector<int> b, int type = 1) {  // 逆运算type =-1
        vector<int> a = b;
        a.resize(n);
        for (ll x = 2; x <= n; x <<= 1) {
            ll k = x >> 1;
            for (ll i = 0; i < n; i += x) {
                for (ll j = 0; j < k; j++) {
                    a[i + j] = (a[i + j] + a[i + j + k] * type + P) % P;
                }
            }
        }
        return a;
    }
    vector<int> Xor(vector<int> b, int type = 1) {  // 逆运算type = inv2
        vector<int> a = b;
        a.resize(n);
        for (ll x = 2; x <= n; x <<= 1) {
            ll k = x >> 1;
            for (ll i = 0; i < n; i += x) {
                for (ll j = 0; j < k; j++) {
                    a[i + j] = (a[i + j] + a[i + j + k]) % P;
                    a[i + j + k] = (a[i + j] - a[i + j + k] * 2 % P + P) % P;
                    a[i + j] = a[i + j] * type % P;
                    a[i + j + k] = a[i + j + k] * type % P;
                }
            }
        }
        return a;
    }
} fwt;