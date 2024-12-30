// 三角形面积
// Need: (-, *)
db area(Point p0, Point p1, Point p2) {
    db k = p0.x * p1.y + p1.x * p2.y + p2.x * p0.y - p1.x * p0.y - p2.x * p1.y -
           p0.x * p2.y;
    return k /= 2;
}

// 三角形四心
// 三角形的重心
Point barycenter(Point A, Point B, Point C) {
    Line u, v;
    u.s.x = (A.x + B.x) / 2;
    u.s.y = (A.y + B.y) / 2;
    u.e = C;
    v.s.x = (A.x + C.x) / 2;
    v.s.y = (A.y + C.y) / 2;
    v.e = B;
    return Intersection_line(u, v);
}

// 三角形外心
// Need: r90c, V*V, d*V, V-V, V+V
// NOTE 给定圆上三点求圆，要先判断是否三点共线
Point circumcenter(Point A, Point B, Point C) {
    db a = A * A, b = B * B, c = C * C;
    db d = 2 * (A.x * (B.y - C.y) + B.x * (C.y - A.y) + C.x * (A.y - B.y));
    return r90c((B - C) * a + (C - A) * b + (A - B) * c) * (db)(1 / d);
}

// 三角形的内心
// DEPENDS len, d*V, V-V, V+V
Point incenter(Point A, Point B, Point C) {
    db a = len(B - C), b = len(A - C), c = len(A - B);
    db d = a + b + c;
    return (A * a + B * b + C * c) * (1.0 / d);
}

// 三角形的垂心
// DEPENDS V*V, d*V, V-V, V^V, r90c
Point orthocenter(Point A, Point B, Point C) {
    db n = B * (A - C), m = A * (B - C);
    db d = (B - C) ^ (A - C);
    return r90c((C - B) * n - (C - A) * m) * (1.0 / d);
}