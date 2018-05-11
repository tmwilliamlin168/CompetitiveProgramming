/*
	- dp[i][j] = maximium happiness after exiting row i column j
	- from left to right dp[i][j]=max(dp[i-1][k]+welcome_sum[k...j])=max(dp[i-1][k]+welcome_sum[0...j]-welcome_sum[0...k]) with length_sum[k...j]<=k
	- Regardless of what j is, we want the maximum dp[i-1][k]-welcome_sum[0...k]
	- Deque for sliding window maximum
*/

#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int mxN=100, mxM=10000;
int n, m, k, qu[mxM+1], qh, qt;
ll dp[mxN+2][mxM+1], ps1[mxN+2][mxM+1], ps2[mxN+2][mxM+1], ans;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	while(1) {
		cin >> n >> m >> k;
		if(!n)
			break;
		for(int i=1; i<=n+1; ++i)
			for(int j=0; j<m; ++j)
				cin >> ps1[i][j+1], ps1[i][j+1]+=ps1[i][j];
		for(int i=1; i<=n+1; ++i)
			for(int j=0; j<m; ++j)
				cin >> ps2[i][j+1], ps2[i][j+1]+=ps2[i][j];
		for(int i=1; i<=n+1; ++i) {
			qh=qt=0;
			for(int j1=0, j2=0; j1<=m; ++j1) {
				while(qt>qh&&dp[i-1][j1]-ps1[i][j1]>dp[i-1][qu[qt-1]]-ps1[i][qu[qt-1]])
					--qt;
				qu[qt++]=j1;
				while(ps2[i][j1]-ps2[i][j2]>k) {
					if(qu[qh]==j2)
						++qh;
					++j2;
				}
				dp[i][j1]=dp[i-1][qu[qh]]+ps1[i][j1]-ps1[i][qu[qh]];
			}
			qt=qh=0;
			for(int j1=m, j2=m; j1>=0; --j1) {
				while(qt>qh&&dp[i-1][j1]+ps1[i][j1]>dp[i-1][qu[qt-1]]+ps1[i][qu[qt-1]])
					--qt;
				qu[qt++]=j1;
				while(ps2[i][j2]-ps2[i][j1]>k) {
					if(qu[qh]==j2)
						++qh;
					--j2;
				}
				dp[i][j1]=max(dp[i-1][qu[qh]]+ps1[i][qu[qh]]-ps1[i][j1], dp[i][j1]);
			}
		}
		ans=LLONG_MIN;
		for(int i=0; i<=m; ++i)
			ans=max(dp[n+1][i], ans);
		cout << ans << "\n";
	}
}
