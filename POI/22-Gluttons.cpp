/*
	- Fix the cakes that the first 2 gluttons choose
	- Run DP on the rest
	- https://github.com/mostafa-saad/MyCompetitiveProgramming/blob/master/Olympiad/POI/official/2015/EDITORIAL/las.pdf
		- A solution is always possible
*/

#include <bits/stdc++.h>
using namespace std;

const int mxN=1e6;
int n, c[mxN], dp[mxN][4], a[mxN];

bool cg(int i, bool g0, bool g1, bool g2) {
	return g1?c[i]*(1+!g2)<=c[(i+1)%n]*(1+g0):c[i]*(1+!g2)>=c[(i+1)%n]*(1+g0);
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> n;
	for(int i=0; i<n; ++i)
		cin >> c[i];
	for(int i=0; i<4; ++i) {
		memset(dp, -1, sizeof(dp));
		dp[1][i]=i%2*2;
		for(int j=1; j<n-1; ++j)
			for(int k=0; k<8; ++k)
				if(~dp[j][k&3]&&cg(j, k&1, k&2, k&4))
					dp[j+1][k/2]=k&3;
		for(int j=0; j<4; ++j) {
			if(dp[n-1][j]<0||!cg(0, j&2, i&1, i&2)||!cg(n-1, j&1, j&2, i&1))
				continue;
			for(int k=n-1; ~k; --k) {
				a[k]=j/2;
				j=dp[k][j];
			}
			for(int k=0; k<n; ++k)
				cout << (k+a[k])%n+1 << " ";
			return 0;
		}
	}
}
