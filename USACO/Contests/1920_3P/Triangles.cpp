#include <bits/stdc++.h>
using namespace std;

const int mxN=300;
int n, ans, a[mxN][mxN];
string g[mxN], g2[mxN];

void solve() {
	memset(a, 0, sizeof(a));
	for(int i=0; i<n; ++i) {
		for(int j=0; j<n; ++j) {
			a[i][j]=g[i][j]=='*';
			if(i&&j<n-1)
				a[i][j]+=a[i-1][j+1];
		}
	}
	for(int i=0; i<n; ++i) {
		for(int j=0; j<n; ++j) {
			for(int k=1; i+k<n&&j+k<n&&i+j>=k; ++k) {
				if(g[i][j+k]=='.'||g[i+k][j]=='.')
					continue;
				int k2=min(k, j);
				ans+=a[i-k+k2][j-k2];
				if(i>=k)
					ans-=a[i-k][j];
			}
		}
	}
}

void rot() {
	for(int i=0; i<n; ++i)
		for(int j=0; j<n; ++j)
			g2[j][n-1-i]=g[i][j];
	for(int i=0; i<n; ++i)
		g[i]=g2[i];
}

int main() {
	ifstream cin("triangles.in");
	ofstream cout("triangles.out");
	
	cin >> n;
	for(int i=0; i<n; ++i) {
		cin >> g[i];
		g2[i].resize(n);
	}
	for(int k=0; k<4; ++k) {
		solve();
		rot();
	}
	cout << ans;
}
