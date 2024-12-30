#include <bits/stdc++.h>
// #define int long long
#define ll long long
#define db double
// 精度有问题时考虑换long double
using namespace std;
const int maxn = 3e6 + 10;
const db Pi = acos(-1);
int rev[maxn];
complex<db> F[maxn], G[maxn], H[maxn];
int R[maxn];
void FFT(complex<db>* A, int n, int inv) {
    int bit = 1;
    while ((1 << bit) < n)
        bit++;
    for (int i = 0; i < n; i++) {
        rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (bit - 1));
        if (i < rev[i])
            swap(A[i], A[rev[i]]);
    }
    for (int mid = 1; mid < n; mid <<= 1) {
        complex<db> temp(cos(Pi / mid), inv * sin(Pi / mid));
        for (int i = 0; i < n; i += mid << 1) {
            complex<db> omega(1, 0);
            for (int j = 0; j < mid; j++, omega *= temp) {
                complex<db> x = A[i + j], y = omega * A[i + j + mid];
                A[i + j] = x + y;
                A[i + j + mid] = x - y;
            }
        }
    }
}
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int n, m;
    cin >> n >> m;
    for (int i = 0; i <= n; i++) {
        int tem;
        cin >> tem;
        F[i].real(tem);
    }
    for (int i = 0; i <= m; i++) {
        int tem;
        cin >> tem;
        G[i].real(tem);
    }
    int N = 1 << __lg(n + m + 1) + 1;
    FFT(F, N, 1);
    FFT(G, N, 1);
    for (int i = 0; i <= N; i++)
        H[i] = F[i] * G[i];
    FFT(H, N, -1);
    for (int i = 0; i <= n + m; i++)
        R[i] = (int)(H[i].real() / N + 0.5);
    for (int i = 0; i <= n + m; i++)
        cout << R[i] << " ";
    // system("pause");
    return 0;
}