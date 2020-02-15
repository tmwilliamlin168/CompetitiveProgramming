#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int mxN=2.5e5, mxM=1e7;
int n, m, q, h[mxM], l[mxM], r[mxM];
vector<array<int, 2>> a[mxN];
ll c[mxM], dp[mxM+1], rm[mxM];

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> n >> m;
	for(int i=0, k; i<n; ++i) {
		cin >> k;
		a[i].resize(k);
		for(int b : {0, 1})
			for(int j=0; j<k; ++j)
				cin >> a[i][j][b];
	}
	cin >> q;
	for(int i=0, x, y; q--; ) {
		cin >> x >> y, --x;
		for(int j=0; j<a[x].size(); ++j, ++i) {
			h[i]=a[x][j][0];
			c[i]=(ll)y*a[x][j][1];
			l[i]=i-1;
			while(l[i]>=0&&i-l[i]<h[i])
				l[i]=l[l[i]];
		}
	}
	memset(dp, 0x3f, 8*m);
	for(int i=m-1; i>=0; --i) {
		rm[i]=dp[i+1];
		r[i]=i+1;
		while(r[i]<m&&r[i]-i<h[i]) {
			rm[i]=min(rm[r[i]], rm[i]);
			r[i]=r[r[i]];
		}
		dp[l[i]+1]=min(dp[i+1]+c[i], dp[l[i]+1]);
		dp[i]=min(rm[i]+c[i], dp[i]);
	}
	cout << dp[0];
}
