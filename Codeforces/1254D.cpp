#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int mxN=1.5e5, M=998244353;
int n, q, s[mxN], dt, ds[mxN], de[mxN], hv[mxN], prt[mxN], p[mxN];
vector<int> adj[mxN];
ll iv[mxN+1], ft[mxN+1], e[mxN];

void upd(int i, ll x) {
	for(++i; i<=n; i+=i&-i)
		ft[i]+=x;
}

ll qry(int i) {
	ll r=0;
	for(++i; i; i-=i&-i)
		r+=ft[i];
	return r;
}

void dfs(int u=0) {
	ds[u]=dt++;
	s[u]=1;
	for(int v : adj[u]) {
		if(v==p[u])
			continue;
		p[v]=u;
		dfs(v);
		s[u]+=s[v];
		if(hv[u]<0||s[v]>s[hv[u]])
			hv[u]=v;
	}
	de[u]=dt;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> n >> q;
	for(int i=1, u, v; i<n; ++i) {
		cin >> u >> v, --u, --v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	memset(hv, -1, 4*n);
	dfs();
	for(int i=0; i<n; ++i)
		if(!i||hv[p[i]]^i)
			for(int j=i; ~j; j=hv[j])
				prt[j]=i;
	iv[1]=1;
	for(int i=2; i<=n; ++i)
		iv[i]=M-M/i*iv[M%i]%M;
	for(int qt, v, d; q--; ) {
		cin >> qt >> v, --v;
		if(qt==1) {
			cin >> d;
			e[v]+=d;
			upd(0, (ll)d*s[v]);
			upd(ds[v], -(ll)d*s[v]);
			upd(de[v], (ll)d*s[v]);
			if(~hv[v]) {
				upd(ds[hv[v]], (ll)d*(n-s[hv[v]]));
				upd(de[hv[v]], -(ll)d*(n-s[hv[v]]));
			}
		} else {
			ll ans=(e[v]*n+qry(ds[v]))%M;
			for(v=prt[v]; v; v=prt[p[v]])
				ans=(ans+e[p[v]]*(n-s[v]))%M;
			cout << ans*iv[n]%M << "\n";
		}
	}
}
