/*
	- http://codeforces.com/blog/entry/60701?#comment-446462
*/

#include <bits/stdc++.h>
using namespace std;

const int mxN=100;
int n, m, a[mxN];
bool adj[2][mxN][mxN], vis[mxN];

int dfs(int u) {
	int s=1;
	vis[u]=1;
	for(int v=0; v<n; ++v)
		if(adj[a[u]][u][v]&&!vis[v])
			s+=dfs(v);
	return s;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> m;
	while(m--) {
		int u, v;
		cin >> u >> v, --u, --v;
		adj[0][u][v]=adj[0][v][u]=1;
	}
	for(int i=0; i<n; ++i)
		for(int j=0; j<n; ++j)
			if(adj[0][i][j])
				for(int k=0; k<n; ++k)
					adj[1][i][k]|=adj[0][j][k];
	for(int i=0; i<n; ++i) {
		bool ok=1;
		for(int j=0; j<n&&ok; ++j)
			ok=!adj[0][i][j]||!adj[1][i][j];
		if(!ok)
			continue;
		for(int j=0; j<n; ++j)
			a[j]=adj[0][i][j];
		ok=0;
		for(int j=0; j<n&&!ok; ++j) {
			memset(vis, 0, n);
			ok=dfs(j)<n;
		}
		if(!ok)
			continue;
		cout << "YES\n";
		for(int j=0; j<n; ++j)
			cout << a[j]+1 << " ";
		return 0;
	}
	cout << "NO";
}
