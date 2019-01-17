/*
	- https://codeforces.com/blog/entry/47821
*/

#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int mxN=2e5;
int t, n, eu[mxN], ev[mxN], di[mxN];
vector<int> adj[mxN];
array<ll, 2> l[mxN];
ll ans, ec[mxN], ed[mxN];

struct dat {
	ll y1=0, y2=0;
	map<ll, ll> mx;
	void in(ll x, ll a) {
		y1=-a;
		y2=a;
		mx[x]=2*a;
	}
	void operator+=(const dat &o) {
		y1+=o.y1;
		y2+=o.y2;
		for(auto it=o.mx.begin(); it!=o.mx.end(); ++it)
			mx[it->first]+=it->second;
	}
	array<ll, 2> l(ll a) {
		array<ll, 2> r{(ll)-1e18, (ll)1e18};
		if(y1<=-a) {
			while(y1<=-a) {
				auto it=mx.begin();
				r[0]=it->first;
				y1+=it->second;
				mx.erase(it);
			}
			mx[r[0]]+=a+y1;
			y1-=a+y1;
		}
		if(y2>=a) {
			while(y2>=a) {
				auto it=--mx.end();
				r[1]=it->first;
				y2-=it->second;
				mx.erase(it);
			}
			mx[r[1]]+=a-y2;
			y2+=a-y2;
		}
		return r;
	}
	ll fx() {
		ll a=y1;
		for(auto it=mx.begin(); it!=mx.end(); ++it) {
			a+=it->second;
			if(a>0)
				return it->first;
		}
	}
} ds[mxN];

int dfs1(int u=0, int pe=n-1, ll cd=0) {
	int s=0;
	di[u]=u;
	ds[u]={};
	for(int e : adj[u]) {
		int v=u^eu[e]^ev[e];
		if(e==pe)
			continue;
		int cs=dfs1(v, e, cd+ec[e]);
		if(cs>s)
			swap(di[u], di[v]);
		ds[di[u]]+=ds[di[v]];
		s+=cs;
	}
	if(!s)
		ds[di[u]].in(cd, ed[pe]);
	l[u]=ds[di[u]].l(ed[pe]);
	return s+1;
}

void dfs2(int u, int pe, ll td) {
	ll d=td-min(max(td, l[u][0]), l[u][1]);
	ans+=abs(d)*ed[pe];
	ec[pe]+=d;
	for(int e : adj[u])
		if(e!=pe)
			dfs2(u^eu[e]^ev[e], e, td-d);
	adj[u].clear();
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> t;
	while(t--) {
		cin >> n;
		for(int i=0; i<n-1; ++i) {
			cin >> eu[i] >> ev[i] >> ec[i] >> ed[i], --eu[i], --ev[i];
			adj[eu[i]].push_back(i);
			adj[ev[i]].push_back(i);
		}
		ec[n-1]=ed[n-1]=1;
		dfs1();
		dfs2(0, n-1, ds[di[0]].fx());
		cout << ans << "\n";
		for(int i=0; i<n-1; ++i)
			cout << ec[i] << "\n";
		ans=0;
	}
}
