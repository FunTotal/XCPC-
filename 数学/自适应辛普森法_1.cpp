struct ASR {
    // 积分函数F在L, R输出 work(L, R, simpson(L, R))
    const db eps = 1e-8;
    db F(db x) {  // 待积函数
        return (c * x + d) / (a * x + b);
    }
    db simpson(db l, db r) {
        db mid = (l + r) / 2.0;
        return (r - l) * (F(l) + 4 * F(mid) + F(r)) / 6.0;
    }
    db work(db l, db r, db ans) {
        db mid = (l + r) / 2;
        db left = simpson(l, mid), right = simpson(mid, r);
        if (fabs(left + right - ans) < eps)
            return left + right;
        else
            return work(l, mid, left) + work(mid, r, right);
    }
} asr;