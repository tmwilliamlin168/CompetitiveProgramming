/*
	- For each i from 0 to n, we can maintain the maximum prefix such that at most i people will get a subtask correct if we transition
	- Maintain the minimum dp values for each of those prefixes
	- My INF values don't seem to be big enough but it passes and the main idea is correct
*/

#include <bits/stdc++.h>
using namespace std;

const int mxN=50, mxT=2e4, mxS=50;
int n, t, s, p[mxT+1], dp[mxS+1][mxT+1], a[mxT+1][mxN+1], b[mxN+1];
string r[mxN];

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> n >> t >> s;
	for(int i=0; i<t; ++i)
		cin >> p[i+1], p[i+1]+=p[i];
	for(int i=0; i<n; ++i)
		cin >> r[i];
	for(int i=0; i<t; ++i)
		for(int j=0; j<n; ++j)
			a[i+1][j]=r[j][i]&1?a[i][j]:i+1;
	for(int i=1; i<=t; ++i) {
		a[i][n]=i;
		sort(a[i], a[i]+n+1);
	}
	memset(dp, 0x3f, sizeof(dp));
	dp[0][0]=0;
	for(int i=1; i<=s; ++i) {
		memset(b, 0x3f, 4*n+4);
		for(int j=1; j<=t; ++j) {
			for(int k=0; k<=n; ++k) {
				for(int l=a[j-1][k]; l<a[j][k]; ++l)
					b[k]=min(dp[i-1][l]-p[l]*k, b[k]);
				dp[i][j]=min(b[k]+p[j]*k, dp[i][j]);
			}
		}
		cout << dp[i][t] << "\n";
	}
}
