/*
	- https://csacademy.com/contest/archive/task/cats/solution/
*/

#include <bits/stdc++.h>
using namespace std;

const int mxN=5e3;
int t, n, s2, a[mxN], dp[2][mxN+1][3][4], ans;
bool h0, h1;

inline void solve() {
	cin >> n;
	h0=h1=s2=0;
	for(int i=0; i<n; ++i) {
		cin >> a[i];
		h0|=a[i]==0;
		h1|=a[i]==1;
		s2+=a[i]==2;
	}
	if(!h0||!h1) {
		cout << "0\n";
		return;
	}
	if(!s2) {
		cout << "-1\n";
		return;
	}
	memset(dp[0], 0x3F, sizeof(dp[0][0]));
	dp[0][0][2][0]=0;
	for(int i=0; i<n; ++i) {
		memset(dp[i&1^1], 0x3F, sizeof(dp[i^1][0])*(min(i+1, s2)+1));
		for(int j=0; j<=min(i, s2); ++j) {
			for(int k=0; k<3; ++k) {
				for(int l=0; l<4; ++l) {
					if(dp[i&1][j][k][l]>n)
						continue;
					dp[i&1^1][j][k][l]=min(dp[i&1][j][k][l]+1, dp[i&1^1][j][k][l]);
					if(a[i]==2&&j+1<=s2) {
						dp[i&1^1][j+1][2][l]=min(dp[i&1][j][k][l], dp[i&1^1][j+1][2][l]);
						if(k==2) {
							dp[i&1^1][j+1][2][l|1]=min(dp[i&1][j][k][l], dp[i&1^1][j+1][2][l|1]);
							dp[i&1^1][j+1][2][l|2]=min(dp[i&1][j][k][l], dp[i&1^1][j+1][2][l|2]);
						}
					} else if(a[i]!=2&&j+(a[i]==(k^1))<=s2)
						dp[i&1^1][j+(a[i]==(k^1))][a[i]][l|1<<a[i]]=min(dp[i&1][j][k][l], dp[i&1^1][j+(a[i]==(k^1))][a[i]][l|1<<a[i]]);
				}
			}
		}
	}
	ans=min(dp[n&1][s2][2][1], dp[n&1][s2][2][2]);
	for(int i=0; i<3; ++i)
		ans=min(dp[n&1][s2][i][3], ans);
	cout << ans << "\n";
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> t;
	while(t--)
		solve();
}
