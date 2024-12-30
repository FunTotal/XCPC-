while (m--) {
    int k;
    cin >> k;
    for (int i = 1; i <= k; i++)
        cin >> h[i], query[h[i]] = 1;
    sort(h + 1, h + 1 + k, cmp);  // 按dfn序从小到大
    int top = 0;
    cnt2 = 0;
    sta[top = 1] = 1, head2[1] = 0;  // 1号结点先入栈
    for (int i = 1, lc; i <= k; i++) {
        if (h[i] == 1)
            continue;  // 避免重复1号结点
        lc = lca(h[i], sta[top]);
        if (lc != sta[top]) {
            while (dfn[lc] < dfn[sta[top - 1]]) {
                add2(sta[top - 1], sta[top], dis(sta[top - 1], sta[top]));
                top--;
            }
            if (dfn[lc] > dfn[sta[top - 1]]) {
                head2[lc] = 0;
                add2(lc, sta[top], dis(lc, sta[top]));
                sta[top] = lc;
            } else {
                add2(lc, sta[top], dis(lc, sta[top]));
                top--;
            }
        }
        head2[h[i]] = 0;
        sta[++top] = h[i];
    }
    for (int i = 1; i < top; i++)
        add2(sta[i], sta[i + 1], dis(sta[i], sta[i + 1]));
}