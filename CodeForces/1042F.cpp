/*
	- Wrote this to test my iterative segment tree with lazy propagation
	- The solution with only point updates works almost 2 times faster
*/

#include <bits/stdc++.h>
using namespace std;

const int mxN=1e6;
int n, k, rt, d[mxN], p[mxN], ds[mxN], de[mxN], dt, ans, h;
vector<int> adj[mxN];
array<int, 2> st[2*mxN], lz[mxN];

void dfs(int u, int pu) {
	p[u]=pu;
	d[u]=pu==-1?0:d[pu]+1;
	if(adj[u].size()==1)
		st[dt+n]={d[u], u};
	else
		st[dt+n]={0, -1};
	ds[u]=dt++;
	for(int v : adj[u])
		if(v!=pu)
			dfs(v, u);
	de[u]=dt;
}

void app(int i, array<int, 2> x) {
	st[i]=x;
	if(i<n)
		lz[i]=x;
}

void psh(int i) {
	for(int s=h; s; --s) {
		int j=i>>s;
		if(lz[j]==array<int, 2>())
			continue;
		app(2*j, lz[j]);
		app(2*j+1, lz[j]);
		lz[j]={};
	}
}

void bld(int i) {
	while(i>>=1)
		st[i]=lz[i]==array<int, 2>{}?max(st[2*i], st[2*i+1]):lz[i];
}

void upd(int l, int r, array<int, 2> x) {
	psh(l+n);
	psh(r+n-1);
	for(int l2=l+n, r2=r+n; l2<r2; ++l2/=2, r2/=2) {
		if(l2&1)
			app(l2, x);
		if(r2&1)
			app(r2-1, x);
	}
	bld(l+n);
	bld(r+n-1);
}

array<int, 2> qry(int l, int r) {
	psh(l+n);
	psh(r+n-1);
	array<int, 2> a={0, -1};
	for(l+=n, r+=n; l<r; ++l/=2, r/=2) {
		if(l&1)
			a=max(st[l], a);
		if(r&1)
			a=max(st[r-1], a);
	}
	return a;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> k;
	for(int i=0; i<n-1; ++i) {
		int u, v;
		cin >> u >> v, --u, --v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	while(adj[rt].size()<=1)
		++rt;
	dfs(rt, -1);
	h=32-__builtin_clz(n);
	for(int i=n-1; i; --i)
		st[i]=max(st[2*i], st[2*i+1]);
	while(1) {
		int u=qry(0, n)[1], k2=k;
		if(u<0)
			break;
		upd(ds[u], ds[u]+1, {0, -1});
		while((u=p[u])>=0) {
			--k2;
			if(qry(ds[u], de[u])[0]-d[u]>k2)
				break;
			upd(ds[u], de[u], {0, -1});
		}
		++ans;
	}
	cout << ans;
}
