/*
	- This looks like the standard nk dp, however some optimization needs to be used in order for it to be within O(n^2)
	- Each of the k ranges can be split into 2 halves, one to the left and the other to the right of the chosen mine
	- Double the amount of dp states for this
	- Each half can be optimized with convex hull
*/

#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int mxN=5000;
int n, k, qh, qt;
ll x[mxN+1], pw[mxN+1], pxw[mxN+1], a[mxN], b[mxN], dp[2][mxN+1];

inline void al(ll ai, ll bi) {
	while(qt-qh>=2&&(b[qt-1]-b[qt-2])/(a[qt-2]-a[qt-1])>=(bi-b[qt-1])/(a[qt-1]-ai))
		--qt;
	a[qt]=ai, b[qt]=bi;
	++qt;
}

inline ll qry(ll xi) {
	while(qt-qh>=2&&a[qh]*xi+b[qh]>=a[qh+1]*xi+b[qh+1])
		++qh;
	return a[qh]*xi+b[qh];
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> k;
	for(int i=0; i<n; ++i) {
		cin >> x[i+1] >> pw[i+1];
		pxw[i+1]=x[i+1]*pw[i+1]+pxw[i];
		pw[i+1]+=pw[i];
	}
	for(int i=1; i<=n; ++i)
		dp[1][i]=1e18;
	for(int i=1; i<=k; ++i) {
		qh=qt=0;
		for(int j=i; j<=n; ++j) {
			al(-pw[j-1], pxw[j-1]+dp[1][j-1]);
			dp[0][j]=x[j]*pw[j]-pxw[j]+qry(x[j]);
		}
		qh=qt=0;
		for(int j=i; j<=n; ++j) {
			al(-x[j], x[j]*pw[j]-pxw[j]+dp[0][j]);
			dp[1][j]=pxw[j]+qry(pw[j]);
		}
	}
	cout << dp[1][n];
}
