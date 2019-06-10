/*
	- Maximize g[i...j] so that i <= j and x[j]-x[i] <= d[i...j]
	- Iterate through all i
	- Problem becomes to maximize g[j] so that i <= j and x[j]-d[1...j] <= x[i]-d[1...i-1]
	- This can be done with a 2d prefix rmq with sweeping BIT / segment tree
*/

#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int mxN=1e5;
int n, x[mxN];
ll pg[mxN+1], pd[mxN+1], pts[mxN], ft[mxN+1], ans;

inline void upd(int i, ll x) {
	for(++i; i<=n; i+=i&-i)
		ft[i]=max(x, ft[i]);
}

inline ll qry(int i) {
	ll r=0;
	for(; i; i-=i&-i)
		r=max(ft[i], r);
	return r;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n;
	for(int i=0; i<n; ++i) {
		cin >> x[i] >> pg[i+1] >> pd[i+1], pg[i+1]+=pg[i], pd[i+1]+=pd[i];
		pts[i]=x[i]-pd[i+1];
	}
	sort(pts, pts+n);
	for(int i=n-1; i>=0; --i) {
		upd(lower_bound(pts, pts+n, x[i]-pd[i+1])-pts, pg[i+1]);
		ans=max(qry(upper_bound(pts, pts+n, x[i]-pd[i])-pts)-pg[i], ans);
	}
	cout << ans;
}
