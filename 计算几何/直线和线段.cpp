struct Line {
    Point s, e;
    Line() {}
    Line(Point x, Point y) : s(x), e(y) {}
};
struct Seg {
    Point s, e;
    Seg() {}
    Seg(Point x, Point y) : s(x), e(y) {}
};
Line read_Line() {
    Line a;
    cin >> a.s.x >> a.s.y >> a.e.x >> a.e.y;
    return a;
}

// 给定直线的横坐标求纵坐标
// NOTE 请确保直线不与y轴平行
db at_x(Line l, db x) {
    Vector lv = l.e - l.s;
    return l.s.y + (x - l.s.x) * lv.y / lv.x;
}

// 给定直线的纵坐标求横坐标
// NOTE 请确保直线不与x轴平行
db at_y(Line l, db y) {
    Vector lv = l.e - l.s;
    return l.s.x - (y + l.s.y) * lv.x / lv.y;
}

// 角平分线
// Need: (+), len, norm
Line bisec(Point P, Vector u, Vector v) {
    return {P, norm(u) + norm(v)};
}

// 线段的方向向量
// Need: (-)
// NOTE 直线的方向向量直接访问属性v
Vector dvec(Seg l) {
    return l.s - l.e;
}

// 线段中点
Point midp(Seg l) {
    return {(l.s.x + l.e.x) / 2, (l.s.y + l.e.y) / 2};
}

// 线段中垂线
// Need: (-), r90c, midp
Line perp(Seg l) {
    return {midp(l), midp(l) + r90c(l.s - l.e)};
}

// 判断点在直线的哪边
// Need: (-, ^), sgn()
// 点在直线上, 返回 0 (三点共线)
// 点在直线的逆时针方向, 返回 1
// 点在直线的顺时针方向, 返回 -1
// 点 a, b (向量ab) 所在的直线和点 c
// 使用的时候要注意 a 和 b 的顺序, 有时顺序不同, 结果不同
int Cross(Point a, Point b, Point c) {
    return sgn((b - a) ^ (c - a));
}
// 两种分情况使用
// db Cross(Point a, Point b, Point c) { return (b - a) ^ (c - a); }

// 判断三点共线
// Need: sgn(), 操作符重载(-, ^)
bool In_one_line(Point A, Point B, Point C) {
    return !sgn((B - A) ^ (C - B));
}

// 点到直线距离
// Need: (-, ^), len()
// 点 P 到直线 AB 的距离
db Dist_point_to_line(Point P, Point A, Point B) {
    Vector v1 = B - A, v2 = P - A;
    return fabs((v1 ^ v2) / len(v1));
}

// 点到线段距离
// Need: 操作符重载(==, -, *, ^), len(), sgn()
// 点 P 到线段 AB 的距离
db Dist_point_to_seg(Point P, Point A, Point B) {
    if (A == B)
        return len(P - A);  // 如果重合, 那么就是两点的距离
    Vector v1 = B - A, v2 = P - A, v3 = P - B;
    if (sgn(v1 * v2) < 0)
        return len(v2);  // AP 最短
    if (sgn(v1 * v3) > 0)
        return len(v3);                // BP 最短
    return fabs((v1 ^ v2) / len(v1));  // 垂线
}

// 线段到线段距离(不相交，则取4个端点到线段距离最小值)
// Need Dist_point_to_seg, Intersect_seg
db Dis_seg_to_seg(Seg a, Seg b) {
    db ans = min(
        {Dist_point_to_seg(a.s, b.s, b.e), Dist_point_to_seg(a.e, b.s, b.e),
         Dist_point_to_seg(b.s, a.s, a.e), Dist_point_to_seg(b.e, a.s, a.e)});
    if (Intersect_seg(a.s, a.e, b.s, b.e))
        ans = 0;
    return ans;
}
// 点是否在直线上
// Need: (-), eq
bool onLine(Point P, Line l) {
    Vector lv = l.e - l.s;
    return eq((P.x - l.e.x) * lv.y, (P.y - l.e.y) * lv.x);
}

// 点是否在线段上
// Need: (-, *, ^), sgn()
// 点 P 是否在线段 AB 上
bool OnSegment(Point P, Point A, Point B) {
    Vector PA = A - P, PB = B - P;
    return sgn(PA ^ PB) == 0 &&
           sgn(PA * PB) <= 0;  // <=, 包括端点; <, 不包括端点
}

// 判断直线与线段是否相交
// Need: Cross()
// 相交, 返回 true
// 不相交, 返回 false
// 直线 ab 与线段 cd
bool Intersect_line_seg(Point a, Point b, Point c, Point d) {
    return Cross(a, b, c) * Cross(a, b, d) <= 0;  // 等号是重合
}

// 判断两线段是否相交
// Need: Cross(), OnSegment()
// 相交, 返回 true (包括端点相交)
// 不相交, 返回 false
// 线段 ab 与线段 cd
bool Intersect_seg(Point a, Point b, Point c, Point d) {
    // 第一个if是判断是否在端点处相交
    if (OnSegment(a, c, d) || OnSegment(b, c, d) || OnSegment(c, a, b) ||
        OnSegment(d, a, b))
        return 1;
    if (Cross(a, b, c) * Cross(a, b, d) >= 0)
        return 0;
    if (Cross(c, d, a) * Cross(c, d, b) >= 0)
        return 0;
    return 1;
}

// 射线ab和射线cd相交(没判重合)
bool is_sx_inter(Point a, Point b, Point c, Point d) {
    int sg = sgn((b - a) ^ (d - c));
    if (sg == 0)
        return 0;  // 平行
    return Cross(c, d, a) == sg && Cross(a, b, c) == -sg;
}

// 判断两直线平行
// Need: (-, ^), sgn()
// 返回true: 平行/重合, false: 相交
bool Line_parallel(Line A, Line B) {
    return sgn((A.s - A.e) ^ (B.s - B.e)) == 0;
}

// 判断两直线重合
// Need: Line_parallel, In_one_line
// 返回true：重合
bool Line_coincident(Line A, Line B) {
    return Line_parallel(A, B) && In_one_line(A.s, A.e, B.s);
}

// 判断两直线是否垂直
// Need: (-, *), sgn()
// 返回true: 垂直, false: 不垂直
bool Line_vertical(Line A, Line B) {
    return sgn((A.e - A.s) * (B.s - B.e)) == 0;
}

// 求两直线交点
// Need: (-, *D, ^)
// 首先要判断两直线是否相交, 即不平行(不重合)
// a, b 所在直线与 c, d 所在直线的交点
Point Intersection_line(Line l1, Line l2)  // 直线交点
{
    Point a = l1.s, b = l1.e, c = l2.s, d = l2.e;
    Vector u = b - a, v = d - c;
    db t = ((a - c) ^ v) / (v ^ u);
    return a + u * t;
}

// 求点到直线的垂足
// Need: (-, *), len
// 点 p 到直线 ab 的垂足
Point FootPoint(Point p, Point a, Point b) {
    Vector v = a - b;
    return a - v * ((a - p) * v / (v * v));
}

// 过某点作直线的垂线
// Need: (-), r90c
Line perp(Line l, Point P) {
    Vector lv = l.e - l.s;
    return {P, r90c(lv)};
}

// 点关于直线的对称点
// Need: (-, +) FootPoint
// 点P关于直线AB的对称点
Point Symmetry_PL(Point p, Point a, Point b) {
    return p + (FootPoint(p, a, b) - p) * 2;
    // 实际上就是求垂足之后延长一倍得到的向量，与原来的点加起来就行了
}

// 两条直线是否重合
// Need: eq, onLine
bool operator==(Line a, Line b) {
    Vector v = a.s - a.e;
    return onLine(a.s, b) && onLine(a.s + v, b);
}

// 两条线段是否重合
// Need: (==), eq
bool operator==(Seg a, Seg b) {
    return (a.s == b.s && a.e == b.e) || (a.s == b.e && a.e == b.s);
}