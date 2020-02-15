/*
	- All nodes that have edges need to be in one connected component
	- Any combination of 2 self-loops work
	- Any combination of a self-loop and a non-self-loop works
	- A combination of 2 edges works iff they share a common node
*/

#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int mxN=1e6;
int n, m, nv;
ll sls, ans;
vector<int> adj[mxN];
bool sl[mxN], vis[mxN];

void dfs(int u) {
	vis[u]=1;
	++nv;
	for(int v : adj[u])
		if(!vis[v])
			dfs(v);
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> m;
	for(int i=0; i<m; ++i) {
		int u, v;
		cin >> u >> v, --u, --v;
		adj[u].push_back(v);
		if(u==v) {
			sl[u]=1;
			++sls;
		} else
			adj[v].push_back(u);
	}
	for(int i=0; i<n; ++i)
		nv+=!adj[i].size();
	for(int i=0; i<n&&!(i&&vis[i-1]); ++i)
		if(adj[i].size())
			dfs(i);
	if(nv<n) {
		cout << 0;
		return 0;
	}
	for(int i=0; i<n; ++i)
		ans+=(ll)(adj[i].size()-sl[i])*(adj[i].size()-sl[i]-1)/2;
	cout << ans+sls*(sls-1)/2+sls*(m-sls);
}
