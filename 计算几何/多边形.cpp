using Points = vector<Point>;

// 判断多边形poly是否是凸多边形（前提是多边形）
// Need: Cross
bool IsConvex(Points poly) {
    int n = poly.size();
    if (n < 3)
        return false;
    Line side = {poly[0], poly[1]};
    // double rel = Cross(side.s, side.e, poly[2]);
    int f1 = 1, f2 = 1;
    for (int i = 0; i < n; i++) {
        side.s = poly[i];
        side.e = poly[(i + 1) % n];
        if (Cross(side.s, side.e, poly[(i + 2) % n]) == -1)
            f1 = 0;
        if (Cross(side.s, side.e, poly[(i + 2) % n]) == 1)
            f2 = 0;
    }
    return f1 | f2;
}

// 求凸多边形的有向面积
// Need: (^)
// 叉积的几何意义就是三角形有向面积的二倍，所以这里要除以二
db convex_polygon_area(Points p) {
    db area = 0;
    int n = p.size();
    for (int i = 1; i <= n - 2; ++i)
        area += (p[i] - p[0]) ^ (p[i + 1] - p[0]);
    // return area / 2;
    return fabs(area / 2);  // 不加的话求的是有向面积，逆时针为负，顺时针为正
}

// 求非凸多边形的有向面积
// Need: (^)
// 我们叉积求得的三角形面积是有向的，在外面的面积可以正负抵消掉，
// 因此非凸多边形也适用，可以从任意点出发划分
// 可以取原点为起点，减少叉乘次数
db polyg_on_area(Points p) {
    int n = p.size();
    db area = 0;
    for (int i = 1; i <= n - 2; ++i)
        area += (p[i] - p[0]) ^ (p[i + 1] - p[0]);
    return area / 2;
}

// 判断点是否在多边形内，若点在多边形内返回1，在多边形外部返回0，在多边形上返回-1
// Need: (^), OnSegment, sgn
// 待判断的点和该多边形的所有点的合集
int is_point_in_polygon(Point p, Points poly) {
    int wn = 0;
    int n = poly.size();
    for (int i = 0; i < n; ++i) {
        if (OnSegment(p, poly[i], poly[(i + 1) % n]))
            return -1;
        int k = sgn((poly[(i + 1) % n] - poly[i]) ^ (p - poly[i]));
        int d1 = sgn(poly[i].y - p.y);
        int d2 = sgn(poly[(i + 1) % n].y - p.y);
        if (k > 0 && d1 <= 0 && d2 > 0)
            wn++;
        if (k < 0 && d2 <= 0 && d1 > 0)
            wn--;
    }
    if (wn != 0)
        return 1;
    return 0;
}

// 判断线段是否在多边形内
// Need: is_point_in_polygon, OnSegment
// 判断线段是否在多边形内 (线段的点可能在多边形上)
// 多边形可以是任意简单多边形
bool InsidePolygon(Points poly,
                   Seg L)  // 判断线段是否在多边形内 (线段的点可能在多边形上)
{
    Points points;
    Point p;
    Seg side;
    int result = ((is_point_in_polygon(L.s, poly) != 0) &&
                  (is_point_in_polygon(L.e, poly) != 0));
    if (!result)
        return false;

    int n = poly.size();
    for (int i = 0; i < n; i++) {
        side.s = poly[i];
        side.e = poly[(i + 1) % n];

        if (OnSegment(L.s, side.s, side.e))
            points.push_back(L.s);
        else if (OnSegment(L.e, side.s, side.e))
            points.push_back(L.e);
        else if (OnSegment(side.s, L.s, L.e))
            points.push_back(side.s);
        else if (OnSegment(side.e, L.s, L.e))
            points.push_back(side.e);
        else if (Intersect_seg(side.s, side.e, L.s, L.e))
            return false;
    }
    // 对交点进行排序
    std::sort(points.begin(), points.end());

    for (int i = 1; i < points.size(); i++) {
        if (points[i - 1] != points[i]) {
            p.x = (points[i - 1].x + points[i].x) / 2.0;
            p.y = (points[i - 1].y + points[i].y) / 2.0;
            if (is_point_in_polygon(p, poly) == 0)
                return false;
        }
    }
    return true;
}

// 求多边形重心
// Need: area
Point barycenter(Points p) {
    int n = p.size();
    Point p0 = p[0], p1 = p[1], p2, center;
    db Area, sumarea = 0, sumx = 0, sumy = 0;
    for (int i = 2; i < n; i++) {
        p2 = p[i];
        center.x = p0.x + p1.x + p2.x;
        center.y = p0.y + p1.y + p2.y;
        Area = area(p0, p1, p2);
        sumarea += Area;  // 图形总面积
        sumx += center.x * Area;
        sumy += center.y * Area;
        p1 = p2;
    }
    return {sumx / sumarea / 3, sumy / sumarea / 3};
}