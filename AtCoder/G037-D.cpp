#include <bits/stdc++.h>
using namespace std;

const int mxN=100;
int n, m, mt[mxN];
array<int, 2> a[mxN][mxN];
vector<array<int, 2>> adj[mxN];
bool vis[mxN];

bool dfs(int u1) {
	if(!vis[u1]) {
		vis[u1]=1;
		for(array<int, 2> u2 : adj[u1]) {
			if(mt[u2[0]]<0||dfs(a[u2[0]][mt[u2[0]]][0])) {
				mt[u2[0]]=u2[1];
				return 1;
			}
		}
	}
	return 0;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> n >> m;
	for(int i=0; i<n; ++i)
		for(int j=0; j<m; ++j)
			cin >> a[i][j][1], a[i][j][0]=(a[i][j][1]-1)/m;
	for(int i=0; i<m; ++i) {
		for(int j=i; j<m; ++j)
			for(int k=0; k<n; ++k)
				adj[a[k][j][0]].push_back({k, j});
		memset(mt, -1, 4*n);
		for(int j=0; j<n; ++j) {
			memset(vis, 0, n);
			dfs(j);
		}
		for(int j=0; j<n; ++j) {
			swap(a[j][mt[j]], a[j][i]);
			adj[j].clear();
		}
	}
	for(int k : {0, 1}) {
		for(int i=0; i<n; ++i) {
			for(int j=0; j<m; ++j)
				cout << a[i][j][1] << " ";
			cout << "\n";
		}
		for(int i=0; i<m; ++i)
			for(int j=0; j<n-1; ++j)
				for(int k=0; k<n-1; ++k)
					if(a[k][i][0]>a[k+1][i][0])
						swap(a[k][i], a[k+1][i]);
	}
}
