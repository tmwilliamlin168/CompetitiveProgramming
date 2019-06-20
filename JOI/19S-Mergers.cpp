#include <bits/stdc++.h>
using namespace std;

const int mxN=5e5;
int n, k, tin[mxN], low[mxN], dt, ci, d[mxN], ans, who[mxN], st[2*mxN], sth;
vector<array<int, 2>> adj[mxN];
vector<int> bs[mxN];

void dfs1(int u=0, int p=-1) {
	tin[u]=dt++;
	for(array<int, 2> v : adj[u])
		if(v[1]^p)
			dfs1(v[0], v[1]);
}

void dfs2(int u=0, int p=-1) {
	tin[u]=low[u]=dt++;
	st[sth++]=u;
	for(array<int, 2> v : adj[u]) {
		if(v[1]==p)
			continue;
		if(!tin[v[0]]) {
			dfs2(v[0], v[1]);
			low[u]=min(low[v[0]], low[u]);
		} else
			low[u]=min(tin[v[0]], low[u]);
	}
	if(low[u]==tin[u]) {
		do
			who[st[sth-1]]=ci;
		while(st[--sth]^u);
		++ci;
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> n >> k;
	for(int i=1, u, v; i<n; ++i) {
		cin >> u >> v, --u, --v;
		adj[u].push_back({v, i});
		adj[v].push_back({u, i});
	}
	for(int i=0, si; i<n; ++i)
		cin >> si, bs[si-1].push_back(i);
	dfs1();
	for(int i=0; i<k; ++i) {
		sort(bs[i].begin(), bs[i].end(), [](int i, int j) {
			return tin[i]<tin[j];
		});
		for(int j=0; j+1<bs[i].size(); ++j) {
			adj[bs[i][j]].push_back({bs[i][j+1], dt});
			adj[bs[i][j+1]].push_back({bs[i][j], dt++});
		}
	}
	memset(tin, 0, 4*n);
	dfs2();
	for(int i=0; i<n; ++i)
		for(array<int, 2> j : adj[i])
			if(who[i]^who[j[0]])
				++d[who[i]];
	for(int i=0; i<ci; ++i)
		ans+=d[i]==1;
	cout << (ans+1)/2;
}
