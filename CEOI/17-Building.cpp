/*
	- dp[i] = dp[j] + w[j+1...i-1] + (h[i]-h[j])^2
	- Dynamic convex hull trick with Lichao segment tree
*/

#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pll pair<ll, ll>
#define fi first
#define se second

const int mxN=1e5, mxH=1e6, sts=1<<21;
int n;
ll h[mxN], pw[mxN+1];
pll st[sts];

void upd(pll nl, int i=1, int l=0, int r=mxH) {
	int m=(l+r)/2;
	if(nl.fi*m+nl.se<st[i].fi*m+st[i].se)
		swap(nl, st[i]);
	if(l==r)
		return;
	if(nl.fi*l+nl.se<st[i].fi*l+st[i].se)
		upd(nl, 2*i, l, m);
	else
		upd(nl, 2*i+1, m+1, r);
}

ll qry(int x, int i=1, int l=0, int r=mxH) {
	int m=(l+r)/2;
	ll s=st[i].fi*x+st[i].se;
	if(l<r) {
		if(x<=m)
			s=min(qry(x, 2*i, l, m), s);
		else
			s=min(qry(x, 2*i+1, m+1, r), s);
	}
	return s;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n;
	for(int i=0; i<n; ++i)
		cin >> h[i];
	for(int i=0; i<n; ++i)
		cin >> pw[i+1], pw[i+1]+=pw[i];
	for(int i=1; i<sts; ++i)
		st[i]={-2*h[0], h[0]*h[0]-pw[1]};
	for(int i=1; i<n; ++i) {
		ll dp=h[i]*h[i]+pw[i]+qry(h[i]);
		upd({-2*h[i], dp-pw[i+1]+h[i]*h[i]});
		if(i==n-1)
			cout << dp;
	}
}
