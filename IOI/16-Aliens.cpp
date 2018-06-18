/*
	- http://ioinformatics.org/locations/ioi16/contest/IOI2016_analysis.pdf
*/

#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pii pair<int, int>
#define pli pair<ll, int>
#define fi first
#define se second

const int mxN=1e5;
int n, m, k, qh, qt, a[mxN], c[mxN];
ll b[mxN];
pii ps1[mxN];
vector<pii> ps2;

inline void al(int ai, ll bi, int ci) {
	while(qt-qh>1&&pli((b[qt-1]-b[qt-2])*(a[qt-1]-ai), c[qt-1])>pli((bi-b[qt-1])*(a[qt-2]-a[qt-1]), ci))
		--qt;
	a[qt]=ai, b[qt]=bi, c[qt]=ci;
	++qt;
}

inline pli qry(ll xi) {
	while(qt-qh>1&&pli(a[qh+1]*xi+b[qh+1], c[qh+1])<pli(a[qh]*xi+b[qh], c[qh]))
		++qh;
	return pli(a[qh]*xi+b[qh], c[qh]);
}

inline pli ddp(ll c) {
	qh=qt=0;
	pli dp;
	for(int i=0; i<ps2.size(); ++i) {
		ll d1=max(i?ps2[i-1].fi-ps2[i].se+1:0, 0), d2=ps2[i].se;
		al(-2*d2, dp.fi-d1*d1+d2*d2, dp.se);
		d1=ps2[i].fi+1;
		dp=qry(d1);
		dp.fi+=d1*d1+c, ++dp.se;
	}
	return dp;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> m >> k;
	for(int i=0; i<n; ++i) {
		cin >> ps1[i].fi >> ps1[i].se;
		if(ps1[i].se>ps1[i].fi)
			swap(ps1[i].se, ps1[i].fi);
	}
	sort(ps1, ps1+n);
	ps2.clear();
	for(int i=0; i<n; ++i) {
		while(!ps2.empty()&&ps1[i].se<=ps2.back().se)
			ps2.pop_back();
		ps2.push_back(ps1[i]);
	}
	ll lb=0, rb=(ll)m*m, ans;
	while(lb<=rb) {
		ll mb=(lb+rb)/2;
		pli dp=ddp(mb);
		if(dp.se<=k) {
			ans=dp.fi;
			rb=mb-1;
		} else
			lb=mb+1;
	}
	cout << ans-lb*k;
}
