#include <bits/stdc++.h>
using namespace std;

const int mxN=1e3;
int n, s[mxN], c, m, s1;
vector<int> adj[mxN];

void dfs1(int u, int p=-1) {
	s[u]=1;
	for(int v : adj[u]) {
		if(v^p) {
			dfs1(v, u);
			s[u]+=s[v];
		}
	}
}

int dfs2(int u, int p=-1) {
	for(int v : adj[u])
		if(v^p&&s[v]>n/2)
			return dfs2(v, u);
	return u;
}

void dfs3(int u, int w, int l, int r) {
	for(int i=0, ss=0; i<adj[u].size(); ++i) {
		if(l<=i&&i<=r)
			continue;
		int v=adj[u][i], k=find(adj[v].begin(), adj[v].end(), u)-adj[v].begin();
		cout << u+1 << " " << v+1 << " " << w*(ss+1) << "\n";
		dfs3(v, w, k, k);
		ss+=s[v];
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> n;
	for(int i=1, u, v; i<n; ++i) {
		cin >> u >> v, --u, --v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	dfs1(0);
	c=dfs2(0);
	dfs1(c);
	sort(adj[c].begin(), adj[c].end(), [](const int &i, const int &j) {
		return s[i]>s[j];
	});
	while(s1<(n+1)/3)
		s1+=s[adj[c][m++]];
	dfs3(c, 1, m, adj[c].size());
	dfs3(c, s1+1, 0, m-1);
}
