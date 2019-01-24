#include <bits/stdc++.h>
using namespace std;

const int mxN=2e5;
int n, m, eu[mxN], ev[mxN], d[mxN], anc[mxN][18], dt, ds[mxN], de[mxN], c1[mxN], c2[mxN], ft[mxN+1];
vector<int> adj[mxN], fs[mxN+1];
vector<array<int, 3>> es[mxN+1];
long long ans;

void dfs1(int u=0, int p=-1) {
	ds[u]=dt++;
	d[u]=p==-1?0:d[p]+1;
	anc[u][0]=p;
	for(int i=1; i<18; ++i)
		anc[u][i]=anc[u][i-1]==-1?-1:anc[anc[u][i-1]][i-1];
	for(int v : adj[u])
		if(v!=p)
			dfs1(v, u);
	de[u]=dt;
}

int ga(int u, int k) {
	for(int i=17; i>=0; --i) {
		if(1<<i<=k) {
			u=anc[u][i];
			k-=1<<i;
		}
	}
	return u;
}

int lca(int u, int v) {
	if((u=ga(u, d[u]-d[v]))==v)
		return u;
	for(int i=17; i>=0; --i) {
		if(anc[u][i]!=anc[v][i]) {
			u=anc[u][i];
			v=anc[v][i];
		}
	}
	return anc[u][0];
}

void ae(int l1, int r1, int l2, int r2, int w=1) {
	es[l1].push_back({l2, r2, -w});
	es[r1+1].push_back({l2, r2, w});
}

void af(vector<array<int, 2>> v, int w=1) {
	for(int i=0; i<v.size(); ++i)
		for(int j=0; j<v.size(); ++j)
			ae(v[i][0], v[i][1], v[j][0], v[j][1], w);
}

int dfs2(int u=0, int p=-1) {
	for(int v : adj[u])
		if(v!=p)
			c2[u]+=dfs2(v, u);
	if(c2[u])
		af({{ds[p], ds[u]-1}, {de[u], de[p]-1}}, c2[u]);
	return c2[u];
}

void upd(int i, int x) {
	for(++i; i<=n; i+=i&-i)
		ft[i]+=x;
}

int qry(int i) {
	int r=0;
	for(; i; i-=i&-i)
		r+=ft[i];
	return r;
}

int main() {
	ifstream cin("exercise.in");
	ofstream cout("exercise.out");

	cin >> n >> m;
	m-=n-1;
	for(int i=1; i<n; ++i) {
		cin >> eu[0] >> ev[0], --eu[0], --ev[0];
		adj[eu[0]].push_back(ev[0]);
		adj[ev[0]].push_back(eu[0]);
	}
	dfs1();
	for(int i=0; i<m; ++i) {
		cin >> eu[i] >> ev[i], --eu[i], --ev[i];
		if(d[eu[i]]<d[ev[i]])
			swap(eu[i], ev[i]);
		int w=lca(eu[i], ev[i]), u2=ga(eu[i], d[eu[i]]-d[w]-1);
		++c1[eu[i]];
		++c2[eu[i]];
		--c2[u2];
		if(w==ev[i]) {
			af({{0, ds[u2]-1}, {de[u2], n-1}});
		} else {
			++c1[ev[i]];
			++c2[ev[i]];
			int v2=ga(ev[i], d[ev[i]]-d[w]-1);
			--c2[v2];
			if(ds[u2]>ds[v2])
				swap(u2, v2);
			af({{0, ds[u2]-1}, {de[u2], ds[v2]-1}, {de[v2], n-1}});
		}
		fs[ds[eu[i]]].push_back(ds[ev[i]]);
	}
	for(int i=0; i<n; ++i)
		if(c1[i])
			ae(ds[i], de[i]-1, ds[i], de[i]-1, c1[i]);
	dfs2();
	ans=(long long)m*(m-1);
	for(int i=0; i<=n; ++i) {
		for(array<int, 3> a : es[i])
			ans-=a[2]*(qry(a[1]+1)-qry(a[0]));
		for(int a : fs[i])
			upd(a, 1);
	}
	cout << ans/2;
}
