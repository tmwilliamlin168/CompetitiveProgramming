/*
	- O(18nlogn) but can be proven to run within 37k queries with dp
*/

/*
int dp[2000]={0, 0}, s;
for(int i=2; i<2000; s+=dp[i++]) {
	dp[i]=2;
	for(int j=1; j<=(min(i-1, 18)+1)/2; ++j)
		dp[i]=max(dp[i], dp[i/(2*j+1)]+j);
}
cout << s;
*/

#include "meetings.h"
#include <bits/stdc++.h>
using namespace std;

set<int> adj[2000];
int sz[2000];

void dfs1(int u, int p=-1) {
	sz[u]=1;
	for(int v : adj[u]) {
		if(v^p&&~sz[v]) {
			dfs1(v, u);
			sz[u]+=sz[v];
		}
	}
}

int dfs2(int u, int n, int p=-1) {
	for(int v : adj[u])
		if(v^p&&sz[v]>n/2)
			return dfs2(v, n, u);
	return u;
}

void cd(int u, int w) {
	dfs1(u);
	u=dfs2(u, sz[u]);
	sz[u]=-1;
	vector<int> ta;
	for(int v : adj[u])
		if(~sz[v])
			ta.push_back(v);
	sort(ta.begin(), ta.end(), [](int i, int j) {
		return sz[i]>sz[j];
	});
	if(ta.size()&1)
		ta.push_back(u);
	for(int j=0; j<ta.size(); j+=2) {
		int x=Query(ta[j], ta[j+1], w);
		for(int k=0; k<=(sz[ta[j+1]]!=-1); ++k) {
			if(x==ta[j+k]) {
				cd(ta[j+k], w);
				return;
			}
		}
		if(x^u) {
			int v=Query(ta[j], u, w)^u?ta[j]:ta[j+1];
			adj[u].erase(v);
			adj[v].erase(u);
			adj[u].insert(x);
			adj[x].insert(u);
			adj[v].insert(x);
			adj[x].insert(v);
			if(x^w) {
				adj[x].insert(w);
				adj[w].insert(x);
			}
			return;
		}
	}
	adj[u].insert(w);
	adj[w].insert(u);
}

void Solve(int n) {
	for(int i=1; i<n; ++i) {
		if(adj[i].size())
			continue;
		memset(sz, 0, 4*n);
		cd(0, i);
	}
	for(int i=0; i<n; ++i)
		for(int j : adj[i])
			if(i<j)
				Bridge(i, j);
}
