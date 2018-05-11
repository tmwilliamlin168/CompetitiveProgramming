/*
	- Split array into parts consisting of at least k elements
	- cost[i, j]=sum[i+1, j]-(j-i)*a[i+1]
	- Convex hull trick
*/

#include <iostream>
using namespace std;

#define ll long long

const int mxN=5e5;
int t, n, k, qh, qt;
ll a[mxN], ps[mxN+1], dp[mxN+1], m[mxN], b[mxN];

inline void al(ll mi, ll bi) {
	if(qt-qh>=1&&m[qt-1]==mi) {
		if(bi<b[qt-1])
			--qt;
		else
			return;
	}
	while(qt-qh>=2&&(b[qt-1]-b[qt-2])/(m[qt-2]-m[qt-1])>=(bi-b[qt-1])/(m[qt-1]-mi))
		--qt;
	m[qt]=mi, b[qt]=bi;
	++qt;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> t;
	while(t--) {
		cin >> n >> k;
		for(int i=0; i<n; ++i) {
			cin >> a[i];
			ps[i+1]=a[i]+ps[i];
		}
		qh=qt=0;
		for(int i=1; i<k; ++i)
			dp[i]=1e18;
		for(int i=k; i<=n; ++i) {
			al(-a[i-k], (i-k)*a[i-k]-ps[i-k]+dp[i-k]);
			while(qt-qh>=2&&m[qh]*i+b[qh]>=m[qh+1]*i+b[qh+1])
				++qh;
			dp[i]=ps[i]+m[qh]*i+b[qh];
		}
		cout << dp[n] << endl;
	}
}
