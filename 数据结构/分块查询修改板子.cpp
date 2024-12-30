using namespace std;
const int maxn = 1e5 + 10;
ll st[maxn], ed[maxn], blk[maxn], sum[maxn];//��¼��ĺ�;
ll mark[maxn],siz[maxn];//��¼��������˶��� ,�Լ�ÿ����Ĵ�С
ll arr[maxn];
int main() {
	int n = read(), m = read();
	int sq = sqrt(n);
	for (int i = 1;i <= sq;i++) {
		st[i] = n / sq * (i - 1) + 1;//��ʾ��i����ĳ�ʼԪ�ص��±�
		ed[i] = n / sq * i;
	}
	ed[sq] = n;//����Ϊ���Ŀ�ȷ���յ㣬��ֹ������ 
	for (int i = 1;i <= sq;i++) {
		for (int j = st[i];j <= ed[i];j++) {
			blk[j] = i;//��j��Ԫ���ڵĿ�Ϊi 
		}
	}
	for (int i = 1;i <= sq;i++)
		siz[i] = ed[i] - st[i] + 1;
	for (int i = 1;i <= n;i++)
		arr[i] = read();
	for (int i = 1;i <= sq;i++) {
		for (int j = st[i];j <= ed[i];j++) {
			sum[i] += arr[j];//��ʼ�����ÿ����ĺ� 
		}
	}
	while (m--) {
		int flag = read();
		if (flag == 1) {//�޸�
			int x = read(), y = read(), k = read();
			if (blk[x] == blk[y]) {//x��y��ͬһ������ 
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
		else if (flag == 2) {//��ѯ
			int x = read(), y = read();
			ll res = 0;
			if (blk[x] == blk[y]) {//x��y��ͬһ������ 
				for (int i = x;i <= y;i++)
					res += arr[i] + mark[blk[x]];
			}
			else {
				for (int i = x;i <= ed[blk[x]];i++)
					res += arr[i] + mark[blk[x]];
				for (int i = st[blk[y]];i <= y;i++)
					res += arr[i] + mark[blk[y]];
				for (int i = blk[x] + 1;i < blk[y];i++)
					res += sum[i] + mark[i]*siz[i];//ע��Ҫ�˿�Ĵ�С
			}
			cout << res << endl;
		}
	}
	return 0;
}