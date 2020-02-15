#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define ar array

const int mxN=1.5e5;
int n, s[mxN], ctp[mxN], a[mxN];
vector<int> adj[mxN];
ll ans;
vector<vector<ar<ll, 2>>> v1, v2;

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
		return z==end()?y->m==x->m&&y->b<=x->b:(x->b-y->b)*(z->m-y->m)>=(y->b-z->b)*(y->m-x->m);
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

void dfs2(int u, int p=-1) {
	s[u]=1;
	for(int v : adj[u]) {
		if(v^p&&ctp[v]==-1) {
			dfs2(v, u);
			s[u]+=s[v];
		}
	}
}

int dfs4(int u, int n, int p=-1) {
	for(int v : adj[u])
		if(v^p&&ctp[v]==-1&&s[v]>n/2)
			return dfs4(v, n, u);
	return u;
}

void dfs5(int u, int d, ll s10, ll s11, ll s20, ll s21, int p=-1) {
	int nc=0;
	s10+=a[u];
	s11+=(ll)a[u]*(d+1);
	s20+=a[u];
	s21+=s20;
	for(int v : adj[u]) {
		if(v==p||~ctp[v])
			continue;
		++nc;
		dfs5(v, d+1, s10, s11, s20, s21, u);
	}
	if(!nc) {
		v1.back().push_back({s10, s11});
		v2.back().push_back({d, s21});
	}
}

void dfs3(int u=0, int p=-2) {
	int c=dfs4(u, s[u]);
	ctp[c]=p;
	dfs2(c);
	v1.push_back({{a[c], a[c]}});
	v2.push_back({{0, 0}});
	for(int v : adj[c]) {
		if(~ctp[v])
			continue;
		v1.push_back({});
		v2.push_back({});
		dfs5(v, 1, a[c], a[c], 0, 0);
	}
	for(int k : {0, 1}) {
		dynamic_hull d;
		d.upd(0, 0);
		for(int i=0; i<v1.size(); ++i) {
			for(ar<ll, 2> a : v2[i])
				ans=max(d.qry(a[0])+a[1], ans);
			for(ar<ll, 2> a : v1[i])
				d.upd(a[0], a[1]);
		}
		reverse(v1.begin(), v1.end());
		reverse(v2.begin(), v2.end());
	}
	v1.clear();
	v2.clear();
	for(int v : adj[c])
		if(ctp[v]==-1)
			dfs3(v, c);
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> n;
	for(int i=1, u, v; i<n; ++i) {
		cin >> u >> v, --u, --v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	for(int i=0; i<n; ++i)
		cin >> a[i];
	memset(ctp, -1, 4*n);
	dfs2(0);
	dfs3();
	cout << ans;
}
