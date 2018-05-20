/*
	- Problem becomes to split array into k+1 parts such that the sum of the products of the pairs of elements from distinct parts is maximized
	- With complementary counting => maximize sum of the products of all pairs - sum of the products of the pairs that belong in the same parts
	- Also the same as minimizing the sum of sum[i...j]^2 for all parts
	- DP can be optimized with Convex Hull Trick
	- Some elements of the given array can be 0, which means that some slopes can be the same and need to be handled separately when adding lines
	- Tight memory limit, store only 2 layers of dp
*/

#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int mxN=1e5;
int n, k, prv[201][mxN+1], qh, qt;
ll ps[mxN+1], dp[2][mxN+1], a[mxN+1], b[mxN+1], c[mxN+1];

inline void al(ll ai, ll bi, ll ci) {
	if(qt-qh>=1&&a[qt-1]==ai) {
		if(bi<b[qt-1])
			--qt;
		else
			return;
	}
	while(qt-qh>=2&&(b[qt-1]-b[qt-2])/(a[qt-2]-a[qt-1])>=(bi-b[qt-1])/(a[qt-1]-ai))
		--qt;
	a[qt]=ai;
	b[qt]=bi;
	c[qt]=ci;
	++qt;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> k;
	for(int i=0; i<n; ++i)
		cin >> ps[i+1], ps[i+1]+=ps[i];
	for(int i=1; i<=n; ++i)
		dp[1][i]=1e18;
	for(int i=0; i<=k; ++i) {
		qh=qt=0;
		al(-2*ps[i], ps[i]*ps[i]+dp[i&1^1][i], i);
		for(int j=i+1; j<=n; ++j) {
			while(qt-qh>=2&&a[qh+1]*ps[j]+b[qh+1]<=a[qh]*ps[j]+b[qh])
				++qh;
			dp[i&1][j]=ps[j]*ps[j]+a[qh]*ps[j]+b[qh];
			prv[i][j]=c[qh];
			al(-2*ps[j], ps[j]*ps[j]+dp[i&1^1][j], j);
		}
	}
	cout << (ps[n]*ps[n]-dp[k&1][n])/2 << "\n";
	for(int i=k, j=prv[k][n]; i; --i, j=prv[i][j])
		cout << j << " ";
} 
