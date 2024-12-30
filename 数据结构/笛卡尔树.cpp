int top = 0;
for (int i = 1; i <= n; i++) {
    while (top && arr[stk[top]] > arr[i]) //大于号是小根堆
        ls[i] = stk[top--];
    rs[stk[top]] = i;
    stk[++top] = i;
}