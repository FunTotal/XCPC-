const int maxn = 100010, maxm = 100010;  // ！注意，边和点的max值可能不一样
using namespace std;
vector<int> G[maxn];
int in[maxn], out[maxn];  // 记录结点的出入度
int sta[maxn], top = 0;   // 手动栈
int del[maxn];            // 记录删边
// 欧拉路径：通过图中每条边恰好一次的路径。
//(起点与终点不同时的判据)
// 有向图：起点出度比入度多 1，终点入度比出度多 1，其余点出入度相等。
// 无向图：起点和终点是奇度数，其余点偶度数。
// 欧拉回路：起点和终点相同的欧拉路径。
// 有向图：所有点出入度相同。
// 无向图：所有点偶度数。
void dfs(int u) {
    for (int i = del[u]; i < G[u].size(); i = del[u]) {
        del[u] = i + 1;  // 删边
        dfs(G[u][i]);
    }
    sta[++top] = u;
}