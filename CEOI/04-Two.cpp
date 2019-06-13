/*
	- DP with CHT
*/

#include <bits/stdc++.h>
using namespace std;

const int mxN=2e4;
int n, w[mxN+2], d[mxN+2], ans, dp[4][mxN+2], a[mxN], b[mxN], qh, qt;

void al(int ai, int bi) {
	while(qt-qh>1&&(bi-b[qt-1])/(a[qt-1]-ai)>(b[qt-1]-b[qt-2])/(a[qt-2]-a[qt-1]))
		--qt;
	a[qt]=ai;
	b[qt]=bi;
	++qt;
}

int qry(int x) {
	while(qt-qh>1&&a[qh+1]*x+b[qh+1]>a[qh]*x+b[qh])
		++qh;
	return a[qh]*x+b[qh];
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> n;
	for(int i=0; i<n; ++i)
		cin >> w[i+1] >> d[i];
	w[n+1]=1;
	for(int i=n-1; ~i; --i) {
		d[i]+=d[i+1];
		ans+=w[i+1]*d[i];
	}
	for(int i=0; i<=n; ++i)
		w[i+1]+=w[i];
	for(int i=1; i<4; ++i) {
		qh=qt=0;
		for(int j=1; j<=n+1; ++j) {
			al(-w[j-1], dp[i-1][j-1]);
			dp[i][j]=qry(d[j-1])+w[j]*d[j-1];
		}
	}
	cout << ans-dp[3][n+1];
}
