#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int mxN=1e5;
int n, q, w[mxN], ds[mxN], de[mxN], dt, ctp[mxN], s[mxN], rt;
vector<int> adj[mxN], cd[mxN];
vector<array<int, 2>> cc[mxN];
ll st[1<<18], lz[1<<18];

void app(int i, ll x, int l, int r) {
	st[i]+=x*(r-l+1);
	lz[i]+=x;
}

void psh(int i, int l, int m, int r) {
	app(2*i, lz[i], l, m);
	app(2*i+1, lz[i], m+1, r);
	lz[i]=0;
}

void upd(int l1, int r1, ll x, int i=1, int l2=0, int r2=n-1) {
	if(l1<=l2&&r2<=r1) {
		app(i, x, l2, r2);
		return;
	}
	int m2=(l2+r2)/2;
	psh(i, l2, m2, r2);
	if(l1<=m2)
		upd(l1, r1, x, 2*i, l2, m2);
	if(m2<r1)
		upd(l1, r1, x, 2*i+1, m2+1, r2);
	st[i]=st[2*i]+st[2*i+1];
}

ll qry(int l1, int r1, int i=1, int l2=0, int r2=n-1) {
	if(l1<=l2&&r2<=r1)
		return st[i];
	int m2=(l2+r2)/2;
	psh(i, l2, m2, r2);
	return (l1<=m2?qry(l1, r1, 2*i, l2, m2):0)+(m2<r1?qry(l1, r1, 2*i+1, m2+1, r2):0);
}

int bs(ll x, int i=1, int l2=0, int r2=n-1) {
	if(l2==r2)
		return l2;
	int m2=(l2+r2)/2;
	psh(i, l2, m2, r2);
	return x>st[2*i]?bs(x-st[2*i], 2*i+1, m2+1, r2):bs(x, 2*i, l2, m2);
}

void dfs1(int u=0, int p=-1) {
	upd(dt, dt, w[u]);
	ds[u]=dt++;
	for(int i=0; i<adj[u].size()-(p!=-1); ++i) {
		if(adj[u][i]==p)
			swap(adj[u][i], adj[u].back());
		dfs1(adj[u][i], u);
		cd[u].push_back(dt);
	}
	de[u]=dt;
}

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

int dfs3(int u=0, int p=-2) {
	int c=dfs4(u, s[u]);
	ctp[c]=p;
	dfs2(c);
	for(int v : adj[c])
		if(ctp[v]==-1)
			cc[c].push_back({v, dfs3(v, c)});
	sort(cc[c].begin(), cc[c].end());
	return c;
}

int ca(int u) {
	if(qry(ds[u], de[u]-1)*2==st[1])
		return min(u, adj[u].back());
	if(qry(ds[u], de[u]-1)*2<st[1])
		return ca((*lower_bound(cc[u].begin(), cc[u].end(), array<int, 2>{adj[u].back()}))[1]);
	int p=bs(qry(0, ds[u])+(st[1]+1)/2);
	if(ds[u]<p&&p<de[u]) {
		int v=adj[u][upper_bound(cd[u].begin(), cd[u].end(), p)-cd[u].begin()];
		if(qry(ds[v], de[v]-1)>=(st[1]+1)/2)
			return ca((*lower_bound(cc[u].begin(), cc[u].end(), array<int, 2>{v}))[1]);
	}
	return u;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> n >> q;
	for(int i=0; i<n; ++i)
		cin >> w[i];
	for(int i=1, u, v; i<n; ++i) {
		cin >> u >> v, --u, --v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	dfs1();
	memset(ctp, -1, 4*n);
	dfs2(0);
	rt=dfs3();
	for(int qt, u, x; q--; ) {
		cin >> qt >> u >> x, --u;
		upd(ds[u], qt<2?ds[u]:de[u]-1, x);
		cout << ca(rt)+1 << "\n";
	}
}
