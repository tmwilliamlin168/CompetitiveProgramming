#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int mxN=1e5;
int n, ui, vi, li;
ll ih, s[mxN], ft[mxN+1];
vector<array<int, 2>> adj[mxN];
array<ll, 2> h[mxN], h2[mxN];
bool ans[mxN];

void upd(int i, ll x) {
	for(++i; i<=n; i+=i&-i)
		ft[i]+=x;
}

ll qry(int i) {
	ll r=0;
	for(; i; i-=i&-i)
		r+=ft[i];
	return r;
}

void dfs1(int u=0, int p=-1) {
	for(array<int, 2> v : adj[u]) {
		if(v[1]==p)
			continue;
		h[v[1]]={h[u][0]+v[0], v[1]};
		s[v[1]]+=v[0];
		dfs1(v[1], u);
		s[u]+=s[v[1]];
	}
}

void dfs2(int u=0, int p=-1, ll rh=ih) {
	while(1) {
		ll nh=qry(upper_bound(h2, h2+n, array<ll, 2>{rh, n})-h2)+ih;
		if(nh<=rh)
			break;
		rh=nh;
	}
	if(rh<h[u][0])
		return;
	ans[u]=1;
	for(array<int, 2> v : adj[u])
		if(v[1]!=p)
			upd(lower_bound(h2, h2+n, h[v[1]])-h2, s[v[1]]);
	for(array<int, 2> v : adj[u]) {
		if(v[1]==p)
			continue;
		upd(lower_bound(h2, h2+n, h[v[1]])-h2, -s[v[1]]);
		dfs2(v[1], u, rh);
		upd(lower_bound(h2, h2+n, h[v[1]])-h2, s[v[1]]);
	}
	for(array<int, 2> v : adj[u])
		if(v[1]!=p)
			upd(lower_bound(h2, h2+n, h[v[1]])-h2, -s[v[1]]);
}

int main() {
	ifstream cin("invtree.in");
	ofstream cout("invtree.out");
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> ih;
	for(int i=0; i<n-1; ++i) {
		cin >> ui >> vi >> li, --ui, --vi;
		adj[ui].push_back({li, vi});
		adj[vi].push_back({li, ui});
	}
	dfs1();
	memcpy(h2, h, sizeof(h[0])*n);
	sort(h2, h2+n);
	dfs2();
	for(int i=0; i<n; ++i)
		cout << ans[i];
}
