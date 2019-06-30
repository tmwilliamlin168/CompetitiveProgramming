#include <bits/stdc++.h>
using namespace std;

const int mxN=1e5;
int n, k, ans;
long long h[mxN];
vector<int> adj[mxN];

void dfs(int u=0, int p=-1) {
	if(~p)
		adj[u].erase(find(adj[u].begin(), adj[u].end(), p));
	for(int v : adj[u]) {
		dfs(v, u);
		h[u]+=h[v];
	}
	sort(adj[u].begin(), adj[u].end(), [](const int &i, const int &j) {
		return h[i]>h[j];
	});
	for(int i=0; i<adj[u].size()&&h[u]>k; ++i, ++ans)
		h[u]-=h[adj[u][i]];
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> n >> k;
	for(int i=0; i<n; ++i)
		cin >> h[i];
	for(int i=1, u, v; i<n; ++i) {
		cin >> u >> v, --u, --v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	dfs();
	cout << ans;
}
