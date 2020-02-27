#include <bits/stdc++.h>
using namespace std;

const int M=1e9+7;

class DominoPlacement {
public:
	int dp[1<<17], dp2[1<<17], c[18];
	int countWays(vector<string> T) {
		vector<string> g;
		int n=T.size(), m=T[0].size();
		if(n<m) {
			swap(n, m);
			g=vector<string>(n, string(m, 0));
			for(int i=0; i<n; ++i)
				for(int j=0; j<m; ++j)
					g[i][j]=T[j][i];
		} else
			g=T;
		memset(c, 0, sizeof(c));
		c[0]=1;
		for(int i=1; i<=m; ++i)
			for(int j=0; j<i-1; ++j)
				c[i]=(c[j]+c[i])%M;
		memset(dp, 0, sizeof(dp));
		dp[0]=1;
		for(int i=0; i<n; ++i) {
			for(int j=0; j<m; ++j) {
				memset(dp2, 0, sizeof(dp2));
				for(int k=0; k<1<<m; ++k) {
					int k2=k&~(1<<j), k3=k|1<<j;
					dp2[k2]=(dp[k]+dp2[k2])%M;
					if(g[i][j]=='.') {
						dp2[k3]=(dp[k]+dp2[k3])%M;
						if(k>>j&1)
							dp2[k3]=(dp[k]+dp2[k3])%M;
					}
				}
				memcpy(dp, dp2, 4<<m);
			}
			for(int k=0; k<1<<m; ++k) {
				for(int j1=0, j2=0; j1<m; j1=j2) {
					if(k>>j1&1||g[i][j1]=='#') {
						++j2;
						continue;
					} else
						for(; j2<m&&(k>>j2&1)^1&&g[i][j2]=='.'; ++j2);
					dp[k]=(long long)dp[k]*c[j2-j1]%M;
				}
			}
		}
		int ans=0;
		for(int i=0; i<1<<m; ++i)
			ans=(dp[i]+ans)%M;
		return ans;
	}
};
