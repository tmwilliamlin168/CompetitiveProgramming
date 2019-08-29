/*
	- http://agc004.contest.atcoder.jp/data/agc/004/editorial.pdf
*/

#include <bits/stdc++.h>
using namespace std;

const int mxN=100;
int h, w, ei, ej, a1[mxN][mxN+1], a2[mxN+1][mxN];
short dp[mxN][mxN][mxN][mxN];
string s[mxN];

void ud(short &x, short y) {
	x=max(x, y);
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> h >> w;
	for(int i=0; i<h; ++i) {
		cin >> s[i];
		for(int j=0; j<w; ++j) {
			if(s[i][j]=='E')
				ei=i, ej=j;
			a1[i][j+1]=a1[i][j]+(s[i][j]=='o');
			a2[i+1][j]=a2[i][j]+(s[i][j]=='o');
		}
	}
	memset(dp, 0xc0, sizeof(dp));
	dp[ei][ei][ej][ej]=0;
	for(int i1=ei; ~i1; --i1) {
		for(int i2=ei; i2<h; ++i2) {
			for(int j1=ej; ~j1; --j1) {
				for(int j2=ej; j2<w; ++j2) {
					int i3=max(i2-ei, i1), i4=min(h-1+i1-ei, i2)+1, j3=max(j2-ej, j1), j4=min(w-1+j1-ej, j2)+1;
					if(i1)
						ud(dp[i1-1][i2][j1][j2], dp[i1][i2][j1][j2]+(i1>i2-ei&&j3<j4?a1[i1-1][j4]-a1[i1-1][j3]:0));
					if(i2<h-1)
						ud(dp[i1][i2+1][j1][j2], dp[i1][i2][j1][j2]+(i2<h-1+i1-ei&&j3<j4?a1[i2+1][j4]-a1[i2+1][j3]:0));
					if(j1)
						ud(dp[i1][i2][j1-1][j2], dp[i1][i2][j1][j2]+(j1>j2-ej&&i3<i4?a2[i4][j1-1]-a2[i3][j1-1]:0));
					if(j2<w-1)
						ud(dp[i1][i2][j1][j2+1], dp[i1][i2][j1][j2]+(j2<w-1+j1-ej&&i3<i4?a2[i4][j2+1]-a2[i3][j2+1]:0));
				}
			}
		}
	}
	cout << dp[0][h-1][0][w-1];
}
