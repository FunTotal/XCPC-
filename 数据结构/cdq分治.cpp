void cdq(int l, int r) {
    if (l == r)
        return;
    int mid = (l + r) >> 1;
    cdq(l, mid), cdq(mid + 1, r);
    sort(arr + l, arr + 1 + mid, cmp2);
    sort(arr + mid + 1, arr + 1 + r, cmp2);
    int i = l, j = mid + 1;
    while (j <= r) {
        while (i <= mid && arr[i].b <= arr[j].b)
            bit.update(arr[i].c, arr[i].sum), i++;
        arr[j].ans += bit.ask(arr[j].c);
        j++;
    }
    for (int k = l; k < i; k++)
        bit.update(arr[k].c, -arr[k].sum);
}