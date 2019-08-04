#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int mxN=1e5, M=1e9;
array<int, 2> a[mxN];
int n, c[mxN], d[mxN], s[mxN];
vector<int> adj[mxN];
ll ans;

ll dfs1(int u=0, int p=-1) {
	ll t=0;
	for(int v : adj[u]) {
		if(v==p)
			continue;
		t+=dfs1(v, u);
		s[u]+=s[v];
	}
	return t+s[u];
}

void dfs2(ll t, int u=0, int p=-1) {
	ans+=t*d[u];
	for(int v : adj[u])
		if(v^p)
			dfs2(t+n-2*s[v], v, u);
}

void solve(int *x, int *y) {
	for(int i=0; i<n; ++i)
		a[i]={x[i], y[i]};
	sort(a, a+n);
	int m=0;
	for(int i=0, j=0; i<n; i=j, ++m) {
		for(c[j++]=m; j<n&&a[j][0]==a[j-1][0]&&a[j][1]==a[j-1][1]+1; c[j++]=m);
		d[m]=s[m]=j-i;
	}
	for(int i=0; i<n; ++i) {
		int p=lower_bound(a, a+n, array<int, 2>{a[i][0]+1, a[i][1]})-a;
		if(p<n&&a[p][0]==a[i][0]+1&&a[p][1]==a[i][1]) {
			adj[c[i]].push_back(c[p]);
			adj[c[p]].push_back(c[i]);
		}
	}
	for(int i=0; i<m; ++i) {
		sort(adj[i].begin(), adj[i].end());
		adj[i].resize(unique(adj[i].begin(), adj[i].end())-adj[i].begin());
	}
	dfs2(dfs1()-n);
}

int DistanceSum(int N, int *x, int *y) {
	n=N;
	solve(x, y);
	for(int i=0; i<n; ++i)
		adj[i].clear();
	solve(y, x);
	return ans/2%M;
}
