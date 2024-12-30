using namespace std;
const int maxn = 1e5 + 10;
ll st[maxn], ed[maxn], blk[maxn], sum[maxn];//记录块的和;
ll mark[maxn],siz[maxn];//记录块整体加了多少 ,以及每个块的大小
ll arr[maxn];
int main() {
	int n = read(), m = read();
	int sq = sqrt(n);
	for (int i = 1;i <= sq;i++) {
		st[i] = n / sq * (i - 1) + 1;//表示第i个块的初始元素的下标
		ed[i] = n / sq * i;
	}
	ed[sq] = n;//单独为最后的块确认终点，防止不整除 
	for (int i = 1;i <= sq;i++) {
		for (int j = st[i];j <= ed[i];j++) {
			blk[j] = i;//第j个元素在的块为i 
		}
	}
	for (int i = 1;i <= sq;i++)
		siz[i] = ed[i] - st[i] + 1;
	for (int i = 1;i <= n;i++)
		arr[i] = read();
	for (int i = 1;i <= sq;i++) {
		for (int j = st[i];j <= ed[i];j++) {
			sum[i] += arr[j];//开始处理好每个块的和 
		}
	}
	while (m--) {
		int flag = read();
		if (flag == 1) {//修改
			int x = read(), y = read(), k = read();
			if (blk[x] == blk[y]) {//x和y在同一个块内 
				for (int i = x;i <= y;i++)
					arr[i] += k, sum[blk[i]] += k;
			}
			else {
				for (int i = x;i <= ed[blk[x]];i++)
					arr[i] += k, sum[blk[i]] += k;
				for (int i = st[blk[y]];i <= y;i++)
					arr[i] += k, sum[blk[i]] += k;
				for (int i = blk[x] + 1;i < blk[y];i++)
					mark[i] += k;
			}
		}
		else if (flag == 2) {//查询
			int x = read(), y = read();
			ll res = 0;
			if (blk[x] == blk[y]) {//x和y在同一个块内 
				for (int i = x;i <= y;i++)
					res += arr[i] + mark[blk[x]];
			}
			else {
				for (int i = x;i <= ed[blk[x]];i++)
					res += arr[i] + mark[blk[x]];
				for (int i = st[blk[y]];i <= y;i++)
					res += arr[i] + mark[blk[y]];
				for (int i = blk[x] + 1;i < blk[y];i++)
					res += sum[i] + mark[i]*siz[i];//注意要乘块的大小
			}
			cout << res << endl;
		}
	}
	return 0;
}