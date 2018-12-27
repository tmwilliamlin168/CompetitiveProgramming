/*
	- Find the connected component of size 60 associated with P
	- We can travel through all nodes with 60*2-1 moves
*/

#include "Ioi.h"
#include <bits/stdc++.h>
using namespace std;

const int mxN=1e4;
int p[mxN], r[mxN], s;
vector<int> adj[mxN], c[mxN];
vector<vector<int>> d[mxN];
long long ans;

int find(int x) {
	return x==p[x]?x:(p[x]=find(p[x]));
}

bool join(int x, int y) {
	if((x=find(x))==(y=find(y)))
		return 0;
	if(r[x]<r[y])
		swap(x, y);
	p[y]=x;
	r[x]+=r[x]==r[y];
	return 1;
}

void dfs1(int u=0, int p=0) {
	if(c[0].size()>=60)
		return;
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

void dfs2(int u=0, int p=0) {
	c[u]=c[p];
	d[u]=d[p];
	if(find(c[u].begin(), c[u].end(), u)==c[u].end()) {
		for(int i=0; i<60; ++i) {
			if(d[u][i].size()>1||c[u][i]==p)
				continue;
			int j=find(c[u].begin(), c[u].end(), d[u][i][0])-c[u].begin();
			d[u][j].erase(find(d[u][j].begin(), d[u][j].end(), c[u][i]));
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

void dfs3(int u, int p, int v) {
	ans|=(long long)v<<(find(c[s].begin(), c[s].end(), u)-c[s].begin());
	for(int v : adj[u]) {
		if(v==p||find(c[s].begin(), c[s].end(), v)==c[s].end())
			continue;
		dfs3(v, u, Move(v));
		Move(u);
	}
}

long long Ioi(int n, int m, int a[], int b[], int P, int v, int t) {
	s=P;
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
	dfs3(s, s, v);
	return ans;
}
