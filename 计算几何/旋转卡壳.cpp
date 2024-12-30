// 旋转卡壳
// 求解凸包直径
// Need: (*,-,^)
db len(Vector A) {
    return sqrt(A * A);
}
db Dist_point_to_line(Point P, Point A, Point B) {
    // 点到直线距离
    Vector v1 = B - A, v2 = P - A;
    return fabs((v1 ^ v2) / len(v1));
}
db RoatingCalipers(vector<Point> poly) {  // 需要先求凸包，注意末尾塞个poly[0]
    if (poly.size() == 3)
        return len(poly[1] - poly[0]);
    int cur = 0, n = poly.size();
    db ans = 0;
    for (int i = 0; i < n - 1; i++) {
        while (Dist_point_to_line(poly[cur], poly[i], poly[i + 1]) <=
               Dist_point_to_line(poly[(cur + 1) % n], poly[i], poly[i + 1])) {
            cur = (cur + 1) % n;
        }
        ans = max(ans,
                  max(len(poly[i] - poly[cur]), len(poly[i + 1] - poly[cur])));
    }
    return ans;
}