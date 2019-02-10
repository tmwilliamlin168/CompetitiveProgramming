/*
	- For each node, find a connected component of size 60 in which each node has a distinct color from 1 to 60
*/

#include "Joi.h"
#include <bits/stdc++.h>
using namespace std;

const int mxN=1e4;
static int p[mxN], r[mxN];
static vector<int> adj[mxN], c[mxN];
static vector<vector<int>> d[mxN];
static long long x;

static int find(int x) {
	return x==p[x]?x:(p[x]=find(p[x]));
}

static bool join(int x, int y) {
	if((x=find(x))==(y=find(y)))
		return 0;
	if(r[x]<r[y])
		swap(x, y);
	p[y]=x;
	r[x]+=r[x]==r[y];
	return 1;
}

static void dfs1(int u=0, int p=0) {
	if(c[0].size()>=60)
		return;
	MessageBoard(u, x>>(c[0].size())&1);
	c[0].push_back(u);
	d[0].push_back({});
	if(u) {
		d[0][find(c[0].begin(), c[0].end(), p)-c[0].begin()].push_back(u);
		d[0].back().push_back(p);
	}
	for(int v : adj[u])
		if(v!=p)
			dfs1(v, u);
}

static void dfs2(int u=0, int p=0) {
	c[u]=c[p];
	d[u]=d[p];
	if(find(c[u].begin(), c[u].end(), u)==c[u].end()) {
		for(int i=0; i<60; ++i) {
			if(d[u][i].size()>1||c[u][i]==p)
				continue;
			int j=find(c[u].begin(), c[u].end(), d[u][i][0])-c[u].begin();
			d[u][j].erase(find(d[u][j].begin(), d[u][j].end(), c[u][i]));
			MessageBoard(u, x>>i&1);
			c[u][i]=u;
			d[u][i][0]=p;
			d[u][find(c[u].begin(), c[u].end(), p)-c[u].begin()].push_back(u);
			break;
		}
	}
	for(int v : adj[u])
		if(v!=p)
			dfs2(v, u);
}

void Joi(int n, int m, int a[], int b[], long long X, int t) {
	x=X;
	for(int i=0; i<n; ++i)
		p[i]=i;
	while(m--) {
		if(join(a[m], b[m])) {
			adj[a[m]].push_back(b[m]);
			adj[b[m]].push_back(a[m]);
		}
	}
	dfs1();
	dfs2();
}
