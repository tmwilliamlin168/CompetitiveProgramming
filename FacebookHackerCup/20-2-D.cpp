#include <bits/stdc++.h>
using namespace std;

#define ll long long

struct line {
	ll m, b;
	mutable function<const line *()> succ;
	bool operator<(const line &o) const {
		if(o.b^LLONG_MAX)
			return m<o.m;
		const line *s=succ();
		return s?b-s->b<(s->m-m)*o.m:0;
	}
};
struct dynamic_hull : public multiset<line> {
	bool bad(auto y) {
		auto z=next(y);
		if(y==begin())
			return z==end()?0:y->m==z->m&&y->b<=z->b;
		auto x=prev(y);
		return z==end()?y->m==x->m&&y->b<=x->b:(__int128)(x->b-y->b)*(z->m-y->m)>=(__int128)(y->b-z->b)*(y->m-x->m);
	}
	void upd(ll m, ll b) {
		auto y=insert({m, b});
		y->succ=[=] {
			return next(y)==end()?0:&*next(y);
		};
		if(bad(y)) {
			erase(y);
			return;
		}
		while(next(y)!=end()&&bad(next(y)))
			erase(next(y));
		while(y!=begin()&&bad(prev(y)))
			erase(prev(y));
	}
	ll qry(ll x) {
		line l=*lower_bound((line){x, LLONG_MAX});
		return l.m*x+l.b;
	}
};

const int mxN=1e6, M=1e9+7;
int n, q, k;
vector<int> p, l, h, qh, qu, adj[mxN], ta[mxN];
ll ans, d[mxN], dp[mxN];
dynamic_hull* ds[mxN];

void ra(vector<int> &x, int n, int e) {
	x.resize(n);
	for(int i=0; i<k; ++i)
		cin >> x[i];
	ll a, b, c, d;
	cin >> a >> b >> c;
	if(e>0)
		d=e;
	else if(!e)
		cin >> d;
	for(int i=k; i<n; ++i)
		x[i]=(a*x[i-2]+b*x[i-1]+c)%(e<0?i:d)+1;
}

void dfs(int u=0) {
	d[u]=u?d[p[u]]+l[u]:0;
	ds[u] = new dynamic_hull();
	if(adj[u].size()) {
		for(int v : adj[u]) {
			dfs(v);
			if(ds[u]->size()<ds[v]->size())
				swap(ds[u], ds[v]);
			for(line l : *ds[v])
				ds[u]->upd(l.m, l.b);
		}
		dp[u]=-(ds[u]->qry(h[u]))-h[u]*d[u];
		for(int a : ta[u])
			ans=(min(-(ds[u]->qry(a))-a*d[u], dp[u])+1)%M*ans%M;
	} else
		dp[u]=0;
	ds[u]->upd(-d[u], -dp[u]);
}

void solve() {
	cin >> n >> q >> k;
	ra(p, n, -1);
	ra(l, n, 0);
	ra(h, n, 0);
	ra(qu, q, n);
	ra(qh, q, 0);
	for(int i=0; i<n; ++i)
		--p[i];
	for(int i=0; i<q; ++i)
		--qu[i];
	for(int i=1; i<n; ++i)
		adj[p[i]].push_back(i);
	for(int i=0; i<q; ++i)
		ta[qu[i]].push_back(qh[i]);
	ans=1;
	dfs();
	cout << ans << "\n";
	for(int i=0; i<n; ++i) {
		adj[i].clear();
		ta[i].clear();
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	int t;
	cin >> t;
	for(int i=1; i<=t; ++i) {
		cout << "Case #" << i << ": ";
		solve();
	}
}
