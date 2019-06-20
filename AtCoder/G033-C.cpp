#include <bits/stdc++.h>
using namespace std;

int n;
vector<int> adj[200000];

array<int, 2> dfs(int u, int p=-1, int d=1) {
	array<int, 2> r={d, u};
	for(int v : adj[u])
		if(v^p)
			r=max(dfs(v, u, d+1), r);
	return r;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> n;
	for(int i=1, a, b; i<n; ++i) {
		cin >> a >> b, --a, --b;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
	cout << (dfs(dfs(0)[1])[0]%3==2?"Second":"First");
}
