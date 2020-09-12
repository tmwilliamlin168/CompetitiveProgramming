#include "swap.h"
#include <bits/stdc++.h>
using namespace std;

#define ar array

const int mxN=1e5;
int a[mxN], r[mxN], d[mxN], anc[mxN][17], b[mxN][17];
vector<ar<int, 2>> adj[mxN];
vector<int> adj2[mxN];

int find(int x) {
	return x^r[x]?r[x]=find(r[x]):x;
}

void dfs2(int u, int w) {
	a[u]=min(w, a[u]);
	for(int v : adj2[u])
		dfs2(v, w);
	adj2[u].clear();
}

bool join(int x, int y, int w) {
	if((x=find(x))==(y=find(y)))
		return 0;
	r[x]=y;
	if(a[y]<=1e9)
		dfs2(x, w);
	if(a[x]<=1e9)
		dfs2(y, w);
	adj2[y].push_back(x);
	return 1;
}

void dfs(int u=0, int p=-1) {
	anc[u][0]=p;
	for(int i=1; i<17; ++i) {
		anc[u][i]=~anc[u][i-1]?anc[anc[u][i-1]][i-1]:-1;
		b[u][i]=~anc[u][i-1]?max(b[u][i-1], b[anc[u][i-1]][i-1]):0;
	}
	for(auto v : adj[u]) {
		if(v[1]^p) {
			b[v[1]][0]=v[0];
			d[v[1]]=d[u]+1;
			dfs(v[1], u);
		}
	}
}

int qry(int x, int y) {
	if(d[x]<d[y])
		swap(x, y);
	int r=0;
	for(int i=16; ~i; --i) {
		if(d[x]-(1<<i)>=d[y]) {
			r=max(b[x][i], r);
			x=anc[x][i];
		}
	}
	if(x==y)
		return r;
	for(int i=16; ~i; --i) {
		if(anc[x][i]^anc[y][i]) {
			r=max({b[x][i], b[y][i], r});
			x=anc[x][i];
			y=anc[y][i];
		}
	}
	return max({b[x][0], b[y][0], r});
}

void init(int n, int m, vector<int> u, vector<int> v, vector<int> w) {
	vector<ar<int, 3>> e;
	for(int i=0; i<m; ++i)
		e.push_back({w[i], u[i], v[i]});
	sort(e.begin(), e.end());
	memset(a, 0x3f, 4*n);
	iota(r, r+n, 0);
	for(auto f : e) {
		if(join(f[1], f[2], f[0])) {
			adj[f[1]].push_back({f[0], f[2]});
			adj[f[2]].push_back({f[0], f[1]});
			if(adj[f[1]].size()>2||adj[f[2]].size()>2)
				dfs2(find(f[1]), f[0]);
		} else
			dfs2(find(f[1]), f[0]);
	}
	dfs();
}

int getMinimumFuelCapacity(int x, int y) {
	int b=max(qry(x, y), a[x]);
	return b>1e9?-1:b;
}
