int p[65];  // 表示用某个数能表示出二进制第几位
void insert(int x) {
    for (int i = 63; i >= 0; i--) {
        if ((x >> i) == 0)  // 找到最高位
            continue;
        if (!p[i]) {
            p[i] = x;
            break;
        } else
            x = x ^ p[i];
    }
}