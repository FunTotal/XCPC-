struct QUERY {
    int l, r, id;  
    bool operator<( const QUERY& o) {  
        if (bel[l] != bel[o.l]) return bel[l] < bel[o.l];
        if (bel[l] & 1) return bel[r] < bel[o.r];
        return bel[r] > bel[o.r];
    }
} query[maxn];
void add(int num) {  // ����ת�ƣ��������
    if (cnt[arr[num]] == 0)
        cur++;
    cnt[arr[num]]++;
}
void del(int num) {  // ɾ��ʱ�ȼ�����
    cnt[arr[num]]--;
    if (cnt[arr[num]] == 0)
        cur--;
}
signed main() {
    int sq = sqrt(n);
    for (int i = 1; i <= n; i++)
        bel[i] = i / sq + 1;
    for (int i = 1; i <= q; i++) {  // 4��ѭ����˳��Ҫ��ס
        while (l > query[i].l) add(--l);
        while (r < query[i].r) add(++r);
        while (l < query[i].l) del(l++);
        while (r > query[i].r) del(r--);
        ans[query[i].id] = cur;  // �����
    }
}