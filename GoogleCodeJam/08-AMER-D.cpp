/*
	- https://code.google.com/codejam/contest/32008/dashboard#s=a&a=3
*/

#include <bits/stdc++.h>
using namespace std;

const int mxN=15;
int t, r, c, ki, kj, dp[mxN*mxN][1<<mxN+1];
string s[mxN];

void dm(int &a, int b) {
	a=max(a, b);
}

int cdp() {
	memset(dp, 0xc0, sizeof(dp));
	dp[0][s[0][0]=='.']=0;
	for(int i=0; i<r; ++i) {
		for(int j=0; j<c; ++j) {
			if(!i&&!j)
				continue;
			for(int k=0; k<1<<c+1; ++k) {
				if(dp[i*c+j-1][k]<0)
					continue;
				if(s[i][j]=='.') {
					if(j) {
						if(k&1)
							dm(dp[i*c+j][k<<1&~2&~(1<<c+1)], dp[i*c+j-1][k]+1);
						if(k>>c&1)
							dm(dp[i*c+j][k<<1&~(1<<c+1)], dp[i*c+j-1][k]+1);
					}
					if(k>>c-1&1)
						dm(dp[i*c+j][k<<1&~(1<<c)&~(1<<c+1)], dp[i*c+j-1][k]+1);
					if(j<c-1&&k>>c-2&1)
						dm(dp[i*c+j][k<<1&~(1<<c-1)&~(1<<c+1)], dp[i*c+j-1][k]+1);
					dm(dp[i*c+j][k<<1&~(1<<c+1)|1], dp[i*c+j-1][k]);
				} else
					dm(dp[i*c+j][k<<1&~(1<<c+1)], dp[i*c+j-1][k]);
			}
		}
	}
	int x=0;
	for(int i=0; i<1<<c+1; ++i)
		dm(x, dp[r*c-1][i]);
	return x;
}

void solve() {
	cin >> r >> c;
	for(int i=0; i<r; ++i) {
		cin >> s[i];
		for(int j=0; j<c; ++j) {
			if(s[i][j]=='K') {
				ki=i;
				kj=j;
			}
		}
	}
	int m1=cdp();
	s[ki][kj]='.';
	cout << (cdp()>m1?"A":"B") << endl;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> t;
	for(int i=1; i<=t; ++i) {
		cout << "Case #" << i << ": ";
		solve();
	}
}
