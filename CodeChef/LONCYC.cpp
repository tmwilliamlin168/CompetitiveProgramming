#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int mxN=2e5, mxM=5e6;
int t, n, m, eu[mxM], ev[mxM], tin[mxN], low[mxN], dt=1;
vector<int> adj1[mxN], adj2[mxN];
bool b[mxM];
ll s[mxN], s2[mxN], s3[mxN], ans[mxM];

void dfs1(int u, int p) {
	tin[u]=low[u]=dt++;
	for(int e : adj1[u]) {
		int v=u^eu[e]^ev[e];
		if(!tin[v]) {
			dfs1(v, u);
			if(low[v]>tin[u]) {
				b[e]=1;
				adj2[u].push_back(e);
				adj2[v].push_back(e);
			} else
				low[u]=min(low[v], low[u]);
		} else if(v!=p)
			low[u]=min(tin[v], low[u]);
	}
}

void dfs2(int u, int p) {
	s[u]=1;
	for(int e : adj2[u]) {
		int v=u^eu[e]^ev[e];
		if(v==p)
			continue;
		dfs2(v, u);
		s[u]+=s[v];
	}
}

void dfs3(int u, int p) {
	for(int e : adj2[u]) {
		int v=u^eu[e]^ev[e];
		if(v==p)
			continue;
		s[v]=s[u];
		dfs3(v, u);
	}
}

void dfs4(int u, int p) {
	s3[u]=s2[u];
	for(int e : adj2[u]) {
		int v=u^eu[e]^ev[e];
		if(v==p)
			continue;
		dfs4(v, u);
		s3[u]+=s3[v];
	}
}

void dfs5(int u, int p) {
	for(int e : adj2[u]) {
		int v=u^eu[e]^ev[e];
		if(v==p)
			continue;
		ans[e]=(s3[u]-s3[v])*s[v]+(s[u]-s[v])*(s[v]+s3[v]);
		s[v]=s[u];
		s3[v]=s3[u];
		dfs5(v, u);
	}
}

inline void solve() {
	cin >> n >> m;
	for(int i=0; i<n; ++i) {
		adj1[i].clear();
		adj2[i].clear();
	}
	for(int i=0; i<m; ++i) {
		cin >> eu[i] >> ev[i], --eu[i], --ev[i];
		adj1[eu[i]].push_back(i);
		adj1[ev[i]].push_back(i);
	}
	memset(tin, 0, 4*n);
	memset(low, 0, 4*n);
	memset(b, 0, m);
	dfs1(0, -1);
	memset(s, 0, 8*n);
	for(int i=0; i<n; ++i) {
		if(s[i])
			continue;
		dfs2(i, -1);
		dfs3(i, -1);
	}
	memset(s2, 0, 8*n);
	for(int i=0; i<m; ++i) {
		if(b[i])
			continue;
		s2[eu[i]]+=s[ev[i]];
		s2[ev[i]]+=s[eu[i]];
		ans[i]=s[eu[i]]*s[ev[i]];
	}
	memset(s3, 0, 8*n);
	for(int i=0; i<n; ++i) {
		if(s3[i])
			continue;
		dfs2(i, -1);
		dfs4(i, -1);
		dfs5(i, -1);
	}
	for(int i=0; i<m; ++i)
		cout << ans[i] << "\n";
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> t;
	while(t--)
		solve();
}
