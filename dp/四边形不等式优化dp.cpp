int m[maxn][maxn],dp[maxn][maxn],sum[maxn],arr[maxn];
//m是区间分割点
signed main(){
    int n;cin>>n;
    for(int i=1;i<=n;i++){
        cin>>arr[i];
        sum[i]=sum[i-1]+arr[i];
        m[i][i]=i;
    }
    for(int len=2;len<=n;len++){//枚举区间长度，也是对角线条数
        for(int i=1,j=len;j<=n;i++,j++){
            dp[i][j]=inf;
            for(int k=m[i][j-1];k<=m[i+1][j];k++){
                if(dp[i][k]+dp[k+1][j]+sum[j]-sum[i-1]<dp[i][j]){
                    dp[i][j]=dp[i][k]+dp[k+1][j]+sum[j]-sum[i-1];
                    m[i][j]=k;
                }
            }
        }
    }
    cout<<dp[1][n]<<endl;
}