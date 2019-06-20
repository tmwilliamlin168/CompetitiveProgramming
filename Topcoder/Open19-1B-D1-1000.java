public class EllysPearls {
	public int getMin(int n, int m, int[] p) {
		for(int i=0; i<n; ++i)
			--p[i];
		int[][][] dp = new int[n+1][1<<m][m];
		for(int i=0; i<n; ++i) {
			for(int j=0; j<1<<m; ++j) {
				for(int k=0; k<m; ++k) {
					dp[i+1][j][k]=Math.max(dp[i][j][k], dp[i+1][j][k]);
					if((j>>p[i]&1)>0) {
						if(k==p[i])
							dp[i+1][j][k]=Math.max(dp[i][j][k]+1, dp[i+1][j][k]);
					} else {
						dp[i+1][j|1<<p[i]][p[i]]=Math.max(dp[i][j][k]+1, dp[i+1][j|1<<p[i]][p[i]]);
					}
				}
			}
		}
		int ans=0;
		for(int i=0; i<m; ++i)
			ans=Math.max(dp[n][(1<<m)-1][i], ans);
		return n-ans;
	}
}
