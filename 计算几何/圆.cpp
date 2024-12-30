// 圆<---------------------------------------------->
struct Circle {
    Point c;
    db r;
    Circle(Point c = Point(), db r = 0) : c(c), r(r) {}
    inline Point point(db a)  // 通过圆心角求坐标
    {
        return Point(c.x + cos(a) * r, c.y + sin(a) * r);
    }
};

// 读入
inline Circle read_circle() {
    Circle C;
    cin >> C.c.x >> C.c.y >> C.r;
    return C;
}

db distance(Point p1, Point p2) {
    return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

// 计算圆上到点p最近点,如p与圆心重合,返回p本身
Point dot_to_circle(Circle pc, Point p) {
    Point c = pc.c;
    db r = pc.r;
    Point u, v;
    if (distance(p, c) < eps)
        return p;
    u.x = c.x + r * fabs(c.x - p.x) / distance(c, p);
    u.y = c.y + r * fabs(c.y - p.y) / distance(c, p) *
                    ((c.x - p.x) * (c.y - p.y) < 0 ? -1 : 1);
    v.x = c.x - r * fabs(c.x - p.x) / distance(c, p);
    v.y = c.y - r * fabs(c.y - p.y) / distance(c, p) *
                    ((c.x - p.x) * (c.y - p.y) < 0 ? -1 : 1);
    return distance(u, p) < distance(v, p) ? u : v;
}

// 点到圆的切线
// 过点p到圆c的切线，v[i]是第i条切线
vector<Vector> get_tangents(Point p, Circle C) {
    Vector u = C.c - p;
    db dist = len(u);
    if (dist < C.r)
        return {};                    // 点在内部，没有切线
    else if (sgn(dist - C.r) == 0) {  // p在圆上，只有一条切线
        return {Rotate(u, PI / 2)};
    } else {  // 否则是两条切线
        db ang = asin(C.r / dist);
        return {Rotate(u, -ang), Rotate(u, +ang)};
    }
}

// 求圆与直线交点
// Need: (-,*), FootPoint, gt, eq, len
// 根据返回vector大小判断情况
vector<Point> inter_line_circle(Line l, Circle C) {
    Point P = FootPoint(C.c, l.s, l.e);
    db h = len(P - C.c);
    if (gt(h, C.r))
        return {};
    if (eq(h, C.r))
        return {P};
    db d = sqrt(C.r * C.r - h * h);
    Vector fx = l.e - l.s;
    Vector vec = fx * (d / len(fx));
    return {P + vec, P - vec};
}

// 求两圆交点
vector<Point> inter_circle_circle(Circle C1, Circle C2) {
    Vector v1 = C2.c - C1.c, v2 = r90c(v1);
    db d = len(v1);
    if (gt(d, C1.r + C2.r) || gt(abs(C1.r - C2.r), d))
        return {};
    if (eq(d, C1.r + C2.r) || eq(d, abs(C1.r - C2.r)))
        return {C1.c + v1 * (C1.r / d)};
    db a = ((C1.r * C1.r - C2.r * C2.r) / d + d) / 2;
    db h = sqrt(C1.r * C1.r - a * a);
    Vector av = v1 * (a / len(v1)), hv = v2 * (h / len(v2));
    return {C1.c + av + hv, C1.c + av - hv};
}

// 两圆相交面积
// Need: (-,*), len
db AreaOfOverlap(Point c1, db r1, Point c2, db r2) {
    db d = len(c1 - c2);
    if (r1 + r2 < d + eps)
        return 0.0;
    if (d < fabs(r1 - r2) + eps) {
        db r = min(r1, r2);
        return PI * r * r;
    }
    db costh1 = (r1 * r1 + d * d - r2 * r2) / (2 * r1 * d),
       costh2 = (r2 * r2 + d * d - r1 * r1) / (2 * r2 * d);
    db sinth1 = sqrt(1 - costh1 * costh1), sinth2 = sqrt(1 - costh2 * costh2);
    db th1 = acos(costh1), th2 = acos(costh2);
    return r1 * r1 * (th1 - costh1 * sinth1) +
           r2 * r2 * (th2 - costh2 * sinth2);
}

// 两圆的公切线
// 返回切线的条数，-1表示无穷条切线
// a[i]和b[i] 分别是第i条切线在圆A和圆B上的切点
int get_tangents(Circle A, Circle B, Point* a, Point* b) {
    int cnt = 0;
    if (A.r < B.r)
        swap(A, B), swap(a, b);
    int d2 =
        (A.c.x - B.c.x) * (A.c.x - B.c.x) + (A.c.y - B.c.y) * (A.c.y - B.c.y);
    int rdiff = A.r - B.r;
    int rsum = A.r + B.r;
    if (d2 < rdiff * rdiff)
        return 0;  // 内含
    db base = atan2(B.c.y - A.c.y, B.c.x - A.c.x);
    if (d2 == 0 && A.r == B.r)
        return -1;              // 无限多条切线
    if (d2 == rdiff * rdiff) {  // 内切，1条切线
        a[cnt] = A.point(base);
        b[cnt] = B.point(base);
        cnt++;
        return 1;
    }
    // 有外共切线
    db ang = acos((A.r - B.r) / sqrt(d2));
    a[cnt] = A.point(base + ang);
    b[cnt] = B.point(base + ang);
    cnt++;
    a[cnt] = A.point(base - ang);
    b[cnt] = B.point(base - ang);
    cnt++;
    if (d2 == rsum * rsum) {  // 一条内公切线
        a[cnt] = A.point(base);
        b[cnt] = B.point(PI + base);
        cnt++;
    } else if (d2 > rsum * rsum) {  // 两条内公切线
        db ang = acos((A.r + B.r) / sqrt(d2));
        a[cnt] = A.point(base + ang);
        b[cnt] = B.point(PI + base + ang);
        cnt++;
        a[cnt] = A.point(base - ang);
        b[cnt] = B.point(PI + base - ang);
        cnt++;
    }
    return cnt;
}

// 求三角形外接圆
Circle WaiJieYuan(Point p1, Point p2, Point p3) {
    db Bx = p2.x - p1.x, By = p2.y - p1.y;
    db Cx = p3.x - p1.x, Cy = p3.y - p1.y;
    db D = 2 * (Bx * Cy - By * Cx);
    db ansx = (Cy * (Bx * Bx + By * By) - By * (Cx * Cx + Cy * Cy)) / D + p1.x;
    db ansy = (Bx * (Cx * Cx + Cy * Cy) - Cx * (Bx * Bx + By * By)) / D + p1.y;
    Point p(ansx, ansy);
    return Circle(p, len(p1 - p));
}

// 求三角形内接圆
Circle NeiJieYuan(Point p1, Point p2, Point p3) {
    db a = len(p2 - p3);
    db b = len(p3 - p1);
    db c = len(p1 - p2);
    Point p = (p1 * a + p2 * b + p3 * c) / (a + b + c);
    return Circle(p, Dist_point_to_line(p, p1, p2));
}

// 两圆的关系
// 5 相离
// 4 外切
// 3 相交
// 2 内切
// 1 内含
int relationcircle(Circle p1, Circle p2) {
    db d = distance(p1.c, p2.c);
    db r1 = p1.r, r2 = p2.r;
    if (sgn(d - r1 - r2) > 0)
        return 5;
    if (sgn(d - r1 - r2) == 0)
        return 4;
    db l = fabs(r1 - r2);
    if (sgn(d - r1 - r2) < 0 && sgn(d - l) > 0)
        return 3;
    if (sgn(d - l) == 0)
        return 2;
    if (sgn(d - l) < 0)
        return 1;
    return 0;
}

//最小圆覆盖
Circle minyuan(Points& poly) {
    random_shuffle(poly.begin(), poly.end());
    Circle res = Circle{poly[0], 0};
    for (int i = 1; i < poly.size(); i++)
        if (dis(poly[i], res.c) > res.r + eps) {
            res.c = poly[i];
            res.r = dis(res.c, poly[i]);
            for (int j = 0; j < i; j++)
                if (dis(poly[j], res.c) > res.r + eps) {
                    res.c.x = (poly[i].x + poly[j].x) / 2;
                    res.c.y = (poly[i].y + poly[j].y) / 2;
                    res.r = dis(res.c, poly[j]);
                    for (int k = 0; k < j; k++)
                        if (dis(poly[k], res.c) > res.r + eps) {
                            res = waijieyuan(poly[i], poly[j], poly[k]);
                        }
                }
        }
    return res;
}