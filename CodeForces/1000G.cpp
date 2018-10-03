#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int mxN=3e5, mxQ=4e5;
int n, q, eu[mxN-1], ev[mxN-1], dep[mxN], fo[mxN], dt[20][2*mxN-1], dti, pew[mxN];
ll a[mxN], w[mxN-1], smp[mxN], smp2[mxN], pmp[mxN];
vector<int> adj[mxN];

void dfs1(int u, int p) {
	dep[u]=p==-1?0:dep[p]+1;
	fo[u]=dti;
	dt[0][dti++]=u;
	for(int e : adj[u]) {
		int v=u^eu[e]^ev[e];
		if(v==p)
			continue;
		pew[v]=w[e];
		dfs1(v, u);
		dt[0][dti++]=u;
		smp[u]+=max(smp[v], 0ll);
	}
	smp[u]+=a[u]-2*pew[u];
}

inline int lg2(int x) {
	return 31-__builtin_clz(x);
}

inline int lca(int u, int v) {
	if(u==v)
		return u;
	if((u=fo[u])>(v=fo[v]))
		swap(u, v);
	int k=lg2(v-u);
	return dep[dt[k][u]]<dep[dt[k][v-(1<<k)+1]]?dt[k][u]:dt[k][v-(1<<k)+1];
}

void dfs2(int u, int p) {
	smp2[u]+=smp[u]+pew[u]-max(smp[u], 0ll);
	ll ssmp=pmp[u];
	for(int e : adj[u]) {
		int v=u^eu[e]^ev[e];
		if(v==p)
			continue;
		smp2[v]+=smp2[u];
		ssmp+=max(smp[v], 0ll);
	}
	for(int e : adj[u]) {
		int v=u^eu[e]^ev[e];
		if(v==p)
			continue;
		pmp[v]=max(a[u]-2*w[e]+ssmp-max(smp[v], 0ll), 0ll);
		dfs2(v, u);
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> q;
	for(int i=0; i<n; ++i)
		cin >> a[i];
	for(int i=0; i<n-1; ++i) {
		cin >> eu[i] >> ev[i] >> w[i], --eu[i], --ev[i];
		adj[eu[i]].push_back(i);
		adj[ev[i]].push_back(i);
	}
	dfs1(0, -1);
	for(int i=1; i<=lg2(2*n-1); ++i)
		for(int j=0; j<2*n-(1<<i); ++j)
			dt[i][j]=dep[dt[i-1][j]]<dep[dt[i-1][j+(1<<(i-1))]]?dt[i-1][j]:dt[i-1][j+(1<<(i-1))];
	dfs2(0, -1);
	for(int i=0; i<q; ++i) {
		int qu, qv;
		cin >> qu >> qv, --qu, --qv;
		int qw=lca(qu, qv);
		ll ans=smp2[qu]+smp2[qv]-2*smp2[qw]+smp[qw]+2*pew[qw]+pmp[qw];
		cout << ans << "\n";
	}
}
