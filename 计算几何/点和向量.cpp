const db eps = 1e-8;       // 根据题目精度要求进行修改
const db PI = acos(-1.0);  // pai, 3.1415916....

int sgn(db x) {  // 进行判断, 提高精度
    if (fabs(x) < eps)
        return 0;           // x == 0, 精度范围内的近似相等
    return x > 0 ? 1 : -1;  // 返回正负
}
bool eq(db a, db b) {
    return abs(a - b) < eps;
}  // ==
bool gt(db a, db b) {
    return a - b > eps;
}  // >
bool lt(db a, db b) {
    return a - b < -eps;
}  // <
bool ge(db a, db b) {
    return a - b > -eps;
}  // >=
bool le(db a, db b) {
    return a - b < eps;
}  // <=

// 点和向量<---------------------------------------------->
// Need: sgn()
typedef struct Point {
    db x, y;
    Point(db x = 0, db y = 0) : x(x), y(y) {}  // 构造函数, 初始值为 0
    Point operator-(const Point& B) const { return Point(x - B.x, y - B.y); }
    Point operator+(const Point& B) const { return Point(x + B.x, y + B.y); }
    db operator^(const Point& B) const { return x * B.y - y * B.x; }
    db operator*(const Point& B) const { return x * B.x + y * B.y; }
    Point operator*(const db& B) const { return Point(x * B, y * B); }
    Point operator/(const db& B) const { return Point(x / B, y / B); }
    bool operator<(const Point& B) const {return x < B.x || (x == B.x && y < B.y);}
    bool operator==(const Point& B) const {return sgn(x - B.x) == 0 && sgn(y - B.y) == 0;}
    bool operator!=(const Point& B) const {return sgn(x - B.x) || sgn(y - B.y);}
} Vector;

inline Point read_Point() {
    Point res;
    cin >> res.x >> res.y;
    return res;
}

// 两点间距离
// Need: (-, *)
db dist(Point a, Point b) {
    return sqrt((a - b) * (a - b));
}

// 向量的模
// Need: (*)
db len(Vector A) {
    return sqrt(A * A);
}

// 单位向量
// Need: (/), len()
Vector norm(Vector A) {
    return A / len(A);
}

// 两向量夹角
// Need: (*), len(), PI
db Angle(Vector A, Vector B) {
    db t = acos((A * B) / len(A) / len(B));
    return t;               // 返回 [0, π]
    return t * (180 / PI);  // 返回 [0, 180] (角度)
}

// 两向量的夹角余弦
// Need: (*), len
db cos_t(Vector u, Vector v) {
    return u * v / len(u) / len(v);
}

// 将向量逆时针旋转90度
Vector r90a(Vector v) {
    return {-v.y, v.x};
}

// 将向量顺时针旋转90度
Vector r90c(Vector v) {
    return {v.y, -v.x};
}

// 将向量逆时针旋转
// Need: (*, ^)
// 向量 A 和要逆时针转的角度 [0, PI]
// PI / 2, 90度
Vector Rotate(Vector A, db b) {
    Vector B(sin(b), cos(b));
    return Vector(A ^ B, A * B);
}

// 向量是否互相垂直
// Need: (*), eq
bool verti(Vector u, Vector v) {
    return eq(u * v, 0);
}

// 向量是否互相平行
// Need: (^), eq
bool paral(Vector u, Vector v) {
    return eq(u ^ v, 0);
}

// 向量是否与x轴平行
// Need: eq
bool paral_x(Vector v) {
    return eq(v.y, 0);
}

// 向量是否与y轴平行
// Need: eq
bool paral_y(Vector v) {
    return eq(v.x, 0);
}