struct Stack {
    int x, y, add;
} stk[maxn];
void Union(int i, int j) {
    i = Find(i), j = Find(j);
    if (rk[i] > rk[j])
        swap(i, j);
    stk[++top] = Stack{i, j, rk[i] == rk[j]};
    fa[i] = j;
    if (rk[i] == rk[j])
        rk[j]++;
}
int Find(int x) {
    return fa[x] == x ? fa[x] : Find(fa[x]);
}

while (top > lsttop) {
    rk[fa[stk[top].x]] -= stk[top].add;
    fa[stk[top].x] = stk[top].x;
    top--;
}