#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int mxN=2e5, mxM=3e3, M=998244353;
int n, m, a[mxN], w[mxN], wt[2];
ll dp[mxM+1][mxM+1], b[2];

ll iv(ll a, ll m) {
	return a<=1?1:(1-iv(m%a, a)*m)/a+m;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> n >> m;
	for(int i=0; i<n; ++i)
		cin >> a[i];
	for(int i=0; i<n; ++i)
		cin >> w[i], wt[a[i]]+=w[i];
	dp[0][0]=1;
	for(int i=0; i<m; ++i) {
		for(int j=0; j<=min(i, wt[0]); ++j) {
			ll f=iv(wt[0]-j+wt[1]+i-j, M);
			dp[i+1][j+1]=(dp[i+1][j+1]+(wt[0]-j)*f%M*dp[i][j])%M;
			dp[i+1][j]=(dp[i+1][j]+(wt[1]+i-j)*f%M*dp[i][j])%M;
		}
	}
	for(int i=0; i<=m; ++i) {
		b[0]=(b[0]+M-i*dp[m][i]%M)%M;
		b[1]=(b[1]+(m-i)*dp[m][i])%M;
	}
	for(int i=0; i<n; ++i)
		cout << w[i]*(1+iv(wt[a[i]], M)*b[a[i]]%M)%M << "\n";
}
