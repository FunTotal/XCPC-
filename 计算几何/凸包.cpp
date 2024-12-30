// 凸包
// Andrew算法求凸包，最后一个点与第一个点重合
// Need: (^,-,<), sgn, le
using Points = vector<Point>;
bool check(Point p, Point q, Point r) {
    return le(0, (q - p) ^ (r - q));
}
vector<Point> Andrew(Points poly) {  // 末尾额外塞了个头
    int n = poly.size(), top = 0;
    vector<int> stk(n + 2, 0), used(n + 2, 0);
    sort(poly.begin(), poly.end());
    stk[++top] = 0;
    for (int i = 1; i < n; i++) {
        while (top > 1 &&
               sgn((poly[stk[top]] - poly[stk[top - 1]]) ^
                   (poly[i] - poly[stk[top]])) <= 0)  // 去掉等号可以找共线的点
            used[stk[top--]] = 0;

        used[i] = 1;
        stk[++top] = i;
    }
    int tmp = top;
    for (int i = n - 2; i >= 0; i--) {
        if (used[i])
            continue;
        while (top > tmp && sgn((poly[stk[top]] - poly[stk[top - 1]]) ^
                                (poly[i] - poly[stk[top]])) <= 0)
            used[stk[top--]] = 0;

        used[i] = 1;
        stk[++top] = i;
    }
    vector<Point> a;
    for (int i = 1; i <= top; i++)
        a.push_back(poly[stk[i]]);
    return a;
}