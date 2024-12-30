// Need: cross/Intersection_line
db Angle(Line a) {
    return atan2(a.e.y - a.s.y, a.e.x - a.s.x);
}  // 夹角
bool cmp(Line a, Line b)  // 极角排序
{
    db A = Angle(a), B = Angle(b);
    return fabs(A - B) > eps ? A < B : ((a.e - a.s) ^ (b.e - a.s)) < 0;
}
Point p[maxn];
Line a[maxn], q[maxn];
int cnt, k;
db res;
db HalfPlane() {  // 给多个多边形，求交集面积
    // 共有cnt条边
    sort(a + 1, a + cnt + 1, cmp);
    int head = 1, tail = 1;
    q[1] = a[1];
    for (int i = 2; i <= cnt; i++) {
        if (Angle(a[i]) - Angle(a[i - 1]) < eps)
            continue;
        while (head < tail && cross(a[i], q[tail], q[tail - 1]))
            tail--;
        while (head < tail && cross(a[i], q[head], q[head + 1]))
            head++;
        q[++tail] = a[i];
    }
    while (head < tail && cross(q[head], q[tail], q[tail - 1]))
        tail--;
    q[++tail] = q[head];
    for (int i = head; i < tail; i++)
        p[++k] = Intersection_line(q[i], q[i + 1]);
    if (k <= 2)
        return 0;
    for (int i = 1; i <= k; i++)
        res += p[i] ^ p[i % k + 1];
    return res / 2;
}
// 注意如何使用，直接将所有点读入p，一个多边形中相邻点连线读入a