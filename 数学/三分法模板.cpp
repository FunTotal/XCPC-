{
    db l, r;
    db eps = 1e-6;  // 一般到精确度要求的后一位
    while (r - l > eps) {
        db mid = (l + r) / 2;
        db res1 = cal(mid - eps),
           res2 = cal(mid + eps);  // 比较中点两侧的函数值
        if (res1 > res2)
            r = mid;
        else
            l = mid;
    }
    // 整数三分
    int l = 1, r = n, ans = 0;
    while (l <= r) {
        int midl = l + (r - l) / 3, midr = r - (r - l) / 3;
        if (ck(midl) > ck(midr))
            ans = l, r = midr - 1;
        else
            ans = r, l = midl + 1;
    }
    cout << ck(ans) << "\n";
}