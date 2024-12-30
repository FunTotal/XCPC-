const int maxn=1e5+10;
const int mod=998244353;
const ll inf=1e18;
ll adj[520][520];
ll dis[520][520];
ll cnt[520][520];
int main(){
    int t=read();
    while(t--){
        memset(adj,0,sizeof(adj));
        memset(cnt,0,sizeof(cnt));
        int n=read(),m=read();
        for(int i=1;i<=n;i++)
            for(int j=1;j<=n;j++){
                if(i==j) dis[i][j]=0;
                else
                dis[i][j]=inf;
            }
        for(int i=0;i<m;i++){
            int u=read(),v=read(),w=read();
            adj[u][v]=w;//初始邻接矩阵
            dis[u][v]=w;//最短路
            cnt[u][v]=1;
        }
        ll mn=inf;//mn表示最小环的长度
        ll c=0;//c记录最小环的个数
        for(int k=1;k<=n;k++){
            for(int i=1;i<=n;i++)
                for(int j=1;j<=n;j++){
                    if(dis[i][j]>dis[i][k]+dis[k][j]){//更新最短路和最短路对应的路径数
                        dis[i][j]=dis[i][k]+dis[k][j];
                        cnt[i][j]=cnt[i][k]*cnt[k][j]%mod;
                    }
                    else if(dis[i][j]==dis[i][k]+dis[k][j])
                        cnt[i][j]=(cnt[i][j]+cnt[i][k]*cnt[k][j])%mod;
                }
            for(int i=1;i<=k-1;i++){//判断是否有环，统计环的最大标号
                if(adj[k][i]){//i到k的最短路加上原图中的ki边是否构成环
                    if(adj[k][i]+dis[i][k]<mn){
                        mn=adj[k][i]+dis[i][k];
                        c=cnt[i][k];
                    }
                    else if(adj[k][i]+dis[i][k]==mn){
                        c=(c+cnt[i][k])%mod;
                    }
                }
            }
        }
    if(mn==inf) mn=-1,c=-1;
    cout<<mn<<" "<<c<<endl;
    }
    system("pause");
    return 0;
}