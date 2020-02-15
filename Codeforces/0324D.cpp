/*
	- dp[i][j][k] = number of ways to cover the first i columns such that the next 2 columns have bitmask k
	- j = 1 if the empty cell has a domino pointing towards it
*/

#include <bits/stdc++.h>
using namespace std;

const int mxN=1e4, M=1e9+7;
int n, m1, dp[mxN+1][2][64];
string s[3];

inline void cdp(int i, int a, int b, bool c) {
	for(int j=0; j<2; ++j) {
		for(int m=0; m<64; ++m) {
			if(m&1<<a|m&1<<b)
				continue;
			dp[i][j|c][m|1<<a|1<<b]+=dp[i][j][m];
			if(dp[i][j|c][m|1<<a|1<<b]>=M)
				dp[i][j|c][m|1<<a|1<<b]-=M;
		}
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n;
	for(int i=0; i<3; ++i) {
		cin >> s[i], s[i]+="..";
		m1|=(s[i][0]!='.')<<i|(s[i][1]!='.')<<(i+3);
	}
	for(int i=0; i<2; ++i)
		for(int j=0; j<3; ++j)
			m1|=(s[j][i]!='.')<<(3*i+j);
	dp[0][0][m1]=1;
	for(int i=0; i<n; ++i) {
		cdp(i, 0, 1, s[2][i]=='O');
		cdp(i, 1, 2, s[0][i]=='O');
		m1=0;
		for(int j=0; j<3; ++j) {
			cdp(i, j, j+3, s[j][i+2]=='O'||i&&s[j][i-1]=='O');
			m1|=(s[j][i+2]!='.')<<(j+3);
		}
		for(int j=0; j<2; ++j)
			for(int m=0; m<8; ++m)
				dp[i+1][j][m|m1]=dp[i][j][m<<3|7];
	}
	cout << dp[n][1][0];
}
