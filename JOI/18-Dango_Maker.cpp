/*
	- Let (i, j) be the position of 'R' in a triple, 2 triples could intersect only if i1+j1 = i2+j2
	- For each possible i+j, use a dp to find the maximal independent set
*/

#include <bits/stdc++.h>
using namespace std;

const int mxN=3e3;
int n, m, dp[mxN+1][3], ans;
string g[mxN];

inline bool c(int i, int j, char c) {
	return i>=0&&i<n&&j>=0&&j<m&&g[i][j]==c;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> m;
	for(int i=0; i<n; ++i)
		cin >> g[i];
	for(int i=0; i<=n+m-4; ++i) {
		int jm=min(m, i+2);
		for(int j=0; j<jm; ++j) {
			dp[j+1][0]=max(dp[j][0], max(dp[j][1], dp[j][2]));
			dp[j+1][1]=c(i+1-j, j-1, 'R')&&c(i+1-j, j, 'G')&&c(i+1-j, j+1, 'W')?max(dp[j][0], dp[j][1])+1:0;
			dp[j+1][2]=c(i-j, j, 'R')&&c(i+1-j, j, 'G')&&c(i+2-j, j, 'W')?max(dp[j][0], dp[j][2])+1:0;
		}
		ans+=max(dp[jm][0], max(dp[jm][1], dp[jm][2]));
	}
	cout << ans;
}
