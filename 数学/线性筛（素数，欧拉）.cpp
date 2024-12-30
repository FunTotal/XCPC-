struct Find_prime {
    int cnt = 0, vis[maxn],
        prime[maxn];  // cnt为素数的个数,maxn是要找的素数的上界
    void find_prime() {
        vis[1] = 1;
        for (int i = 2; i < maxn; i++) {
            if (vis[i] == 0)
                prime[++cnt] = i;
            for (int j = 1; j <= cnt && i * prime[j] < maxn; j++) {
                vis[i * prime[j]] = 1;
                if (i % prime[j] == 0)
                    break;
            }
        }
    }
} Pri;

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