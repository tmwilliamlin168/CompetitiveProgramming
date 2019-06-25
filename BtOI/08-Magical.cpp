/*
	- Binary search
	- Run a digit DP, building the strings from the middle
	- dp[a][b][c][d][e]
		- we built the ath layer
		- b adjacent pairs which are not the same
		- c stores the first and last letters
		- d stores whether the current string is less than or equal to the reverse
		- e stores whether the current string is less than, equal to, or greater than the target string
	- O(n^3) but can be improved to O(n^2) by not recalculating entire dp array
*/

#include <bits/stdc++.h>
using namespace std;

#define ll long long

int n, m, x[60], d[4][4];
ll k, dp[30][62][4][2][3];

int e(int a, int b, int c) {
	if(a/2>x[(n-1)/2-b])
		return 2;
	if(a/2<x[(n-1)/2-b])
		return 1;
	if(!c&&a%2>x[n/2+b])
		return 2;
	if(!c&&a%2<x[n/2+b])
		return 1;
	return c;
}

ll chk() {
	memset(dp, 0, sizeof(dp));
	dp[0][0][0][1][e(0, 0, 0)]=dp[0][0][3][1][e(3, 0, 0)]=1;
	if(~n&1)
		dp[0][1][1][1][e(1, 0, 0)]=dp[0][1][2][0][e(2, 0, 0)]=1;
	for(int i=0; i<(n-1)/2; ++i)
		for(int j=0; j<=m; ++j)
			for(int a=0; a<4; ++a)
				for(int b : {0, 1})
					for(int c : {0, 1, 2})
						for(int f=0; f<4; ++f)
							dp[i+1][j+d[a][f]][f][f>0&&f<3?2-f:b][e(f, i+1, c)]+=dp[i][j][a][b][c];
	ll r=0;
	for(int i=0; i<=m; ++i)
		for(int j=0; j<4; ++j)
			r+=dp[(n-1)/2][i][j][1][1];
	return r;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	for(int i=0; i<4; ++i)
		for(int j=0; j<4; ++j)
			d[i][j]=(i&1^j&1)+(i/2^j/2);
	cin >> n >> m >> k;
	for(int i=0; i<n; ++i) {
		x[i]=1;
		if(chk()>=k)
			x[i]=0;
	}
	if(chk()<k-1)
		cout << "NO SUCH STONE\n";
	else
		for(int i=0; i<n; ++i)
			cout << (x[i]?'X':'I');
}
