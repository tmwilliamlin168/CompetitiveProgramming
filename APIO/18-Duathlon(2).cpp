/*
	- Complementary counting
	- Consider an articulation point u on a BCC
	- If s & f are in the u's subtree, then c cannot be on the BCC (except for u)
*/

#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int mxN=1e5;
int n, m, dt=1, tin[mxN], low[mxN], st[mxN], sth, bccI;
vector<int> adj1[mxN], adj2[2*mxN];
ll sz[2*mxN], n2, ans;

void dfs1(int u, int p) {
	tin[u]=low[u]=dt++;
	st[sth++]=u;
	++n2;
	for(int v : adj1[u]) {
		if(!tin[v]) {
			dfs1(v, u);
			low[u]=min(low[v], low[u]);
			if(low[v]>=tin[u]) {
				adj2[u].push_back(bccI+n);
				while(adj2[bccI+n].empty()||adj2[bccI+n].back()!=v)
					adj2[bccI+n].push_back(st[--sth]);
				++bccI;
			}
		} else if(v!=p)
			low[u]=min(tin[v], low[u]);
	}
}

void dfs2(int u, int p) {
	sz[u]=u<n;
	for(int v : adj2[u]) {
		dfs2(v, u);
		sz[u]+=sz[v];
		if(u>=n)
			ans-=(adj2[u].size()-(p==-1))*sz[v]*(sz[v]-1);
	}
	if(u>=n)
		ans-=adj2[u].size()*(n2-sz[u])*(n2-sz[u]-1);
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> m;
	while(m--) {
		int u, v;
		cin >> u >> v, --u, --v;
		adj1[u].push_back(v);
		adj1[v].push_back(u);
	}
	for(int i=0; i<n; ++i) {
		if(tin[i])
			continue;
		dfs1(i, -1);
		ans+=n2*(n2-1)*(n2-2);
		dfs2(i, -1);
		n2=0;
	}
	cout << ans;
}
