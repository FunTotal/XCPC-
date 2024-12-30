struct QUERY {
    int l, r, id;  
    bool operator<( const QUERY& o) {  
        if (bel[l] != bel[o.l]) return bel[l] < bel[o.l];
        if (bel[l] & 1) return bel[r] < bel[o.r];
        return bel[r] > bel[o.r];
    }
} query[maxn];
void add(int num) {  // 区间转移，先算后增
    if (cnt[arr[num]] == 0)
        cur++;
    cnt[arr[num]]++;
}
void del(int num) {  // 删数时先减后算
    cnt[arr[num]]--;
    if (cnt[arr[num]] == 0)
        cur--;
}
signed main() {
    int sq = sqrt(n);
    for (int i = 1; i <= n; i++)
        bel[i] = i / sq + 1;
    for (int i = 1; i <= q; i++) {  // 4个循环的顺序要记住
        while (l > query[i].l) add(--l);
        while (r < query[i].r) add(++r);
        while (l < query[i].l) del(l++);
        while (r > query[i].r) del(r--);
        ans[query[i].id] = cur;  // 储存答案
    }
}