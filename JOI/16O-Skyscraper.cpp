/*
	- http://codeforces.com/blog/entry/47764
*/

#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int mxN=100, mxM=1e3, M=1e9+7;
int n, m, a[mxN];
ll dp[mxN][4][mxN+1][mxM+1], ans;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> n >> m;
	if(n<2) {
		cout << 1;
		return 0;
	}
	for(int i=0; i<n; ++i)
		cin >> a[i];
	sort(a, a+n);
	dp[0][0][1][0]=1;
	dp[0][1][1][0]=2;
	for(int i=0; i+1<n; ++i) {
		for(int j=0; j<3; ++j) {
			for(int k=1; k<n; ++k) {
				for(int l=0; l<=m; ++l) {
					int nl=l+(2*k-j)*(a[i+1]-a[i]);
					if(nl>m)
						break;
					dp[i][j][k][l]%=M;
					dp[i+1][j][k+1][nl]+=dp[i][j][k][l];
					dp[i+1][j+1][k+1][nl]+=(2-j)*dp[i][j][k][l];
					dp[i+1][j][k][nl]+=(2*k-j)*dp[i][j][k][l];
					dp[i+1][j+1][k][nl]+=(2-j)*(k-j)*dp[i][j][k][l];
					dp[i+1][j][k-1][nl]+=(k-j)*(k-1)*dp[i][j][k][l];
					if(i+2==n&&(j==1&&k==1||j==2&&k==2))
						ans+=dp[i][j][k][l];
				}
			}
		}
	}
	cout << ans%M;
}
