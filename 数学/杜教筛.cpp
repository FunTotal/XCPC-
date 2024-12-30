
// 基本都要记忆化+手动筛比较小的前缀和,而且注意是平方数列求和，开始先对n取余，防止爆longlong
int getsum_f(int n) {      // 目标函数f 的前缀和sum[n]
    int ans = f_g_sum(n);  // 算 f*g的前缀和
    for (int l = 2, r; l <= n; l = r + 1) {
        r = n / (n / l);
        ans -= (g_sum(r) - g_sum(l - 1)) * getsum_f(n / l);
    }
    return ans;
}
struct Find_mu {
    int mu[maxn], prime[maxn], vis[maxn], cnt, mu_sum[maxn];
    void init_mu() {
        mu[1] = 1;
        for (int i = 2; i < maxn; i++) {
            if (!vis[i])
                prime[++cnt] = i, mu[i] = -1;
            for (int j = 1; j <= cnt && i * prime[j] < maxn; j++) {
                vis[i * prime[j]] = 1;
                if (i % prime[j] == 0) {
                    mu[i * prime[j]] = 0;
                    break;
                }
                mu[i * prime[j]] = -mu[i];
            }
        }
        for (int i = 1; i < maxn; i++)
            mu_sum[i] = mu_sum[i - 1] + mu[i];
    }
} Mu;
struct Find_phi {
    int phi[maxn], vis[maxn], cnt = 0, prime[maxn], phi_sum[maxn];
    void init_phi() {
        phi[1] = 1;
        for (int i = 2; i < maxn; i++) {
            if (!vis[i])
                prime[++cnt] = i, phi[i] = i - 1;
            for (int j = 1; j <= cnt && i * prime[j] < maxn; j++) {
                vis[i * prime[j]] = 1;
                if (i % prime[j] == 0) {
                    phi[i * prime[j]] = phi[i] * prime[j];
                    break;
                } else
                    phi[i * prime[j]] = phi[prime[j]] * phi[i];
            }
        }
        for (int i = 1; i < maxn; i++)
            phi_sum[i] = phi_sum[i - 1] + phi[i];
    }
} Phi;
unordered_map<int, int> sum_mu, sum_phi;
int getsum_mu(int n) {  // 取g = I,  mu * I , f*g = e
    if (n < maxn)
        return Mu.mu_sum[n];
    int ans = 1;
    if (sum_mu.count(n))
        return sum_mu[n];
    for (int l = 2, r; l <= n; l = r + 1) {
        r = n / (n / l);
        ans -= (r - (l - 1)) * getsum_mu(n / l);
    }
    return sum_mu[n] = ans;
}
int getsum_phi(int n) {  // f = phi, g = I, f*g=id
    if (n < maxn)
        return Phi.phi_sum[n];
    int ans = n * (n + 1) / 2;
    if (sum_phi.count(n))
        return sum_phi[n];
    for (int l = 2, r; l <= n; l = r + 1) {
        r = n / (n / l);
        ans -= (r - (l - 1)) * getsum_phi(n / l);
    }
    return sum_phi[n] = ans;
}