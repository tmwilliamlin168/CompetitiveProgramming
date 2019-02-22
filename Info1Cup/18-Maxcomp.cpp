#include <bits/stdc++.h>
using namespace std;

const int mxN=1e3;
int n, m, a[mxN][mxN], b1[mxN+1][mxN+1], b2[mxN+1][mxN+1], b3[mxN+1][mxN+1], b4[mxN+1][mxN+1], ans;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> n >> m;
	memset(b1, 0xbf, sizeof(b1));
	memset(b2, 0xbf, sizeof(b2));
	memset(b3, 0xbf, sizeof(b3));
	memset(b4, 0xbf, sizeof(b4));
	for(int i=0; i<n; ++i) {
		for(int j=0; j<m; ++j) {
			cin >> a[i][j];
			b1[i+1][j+1]=max({b1[i][j+1], b1[i+1][j], -a[i][j]+i+j});
		}
		for(int j=m-1; ~j; --j)
			b2[i+1][j]=max({b2[i][j], b2[i+1][j+1], -a[i][j]+i-j});
	}
	for(int i=n-1; ~i; --i) {
		for(int j=0; j<m; ++j)
			b3[i][j+1]=max({b3[i+1][j+1], b3[i][j], -a[i][j]-i+j});
		for(int j=m-1; ~j; --j)
			b4[i][j]=max({b4[i+1][j], b4[i][j+1], -a[i][j]-i-j});
	}
	for(int i=0; i<n; ++i)
		for(int j=0; j<m; ++j)
			ans=max(a[i][j]+max({b1[i+1][j+1]-i-j, b2[i+1][j]-i+j, b3[i][j+1]+i-j, b4[i][j]+i+j}), ans);
	cout << ans-1;
}
