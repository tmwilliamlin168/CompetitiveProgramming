/*
	- http://agc005.contest.atcoder.jp/data/agc/005/editorial.pdf
*/

#include <bits/stdc++.h>
using namespace std;

const int mxN=2e5;
int n, r[2], d[2][mxN], p[mxN], ans;
vector<int> adj[2][mxN];

void dfs(int u, int k, int pu=-1) {
	if(k)
		p[u]=pu;
	if(!k&&d[0][u]>=d[1][u])
		return;
	for(int v : adj[k][u]) {
		if(v^pu) {
			d[k][v]=d[k][u]+1;
			dfs(v, k, u);
		}
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> n >> r[0] >> r[1], --r[0], --r[1];
	for(int k : {0, 1}) {
		for(int i=1, a, b; i<n; ++i) {
			cin >> a >> b, --a, --b;
			adj[k][a].push_back(b);
			adj[k][b].push_back(a);
		}
	}
	memset(d, 0x3f, 4*n);
	d[0][r[0]]=0;
	for(int k : {1, 0})
		dfs(r[k], k);
	for(int i=0; i<n; ++i) {
		if(d[0][i]<=d[1][i])
			ans=max(2*d[1][i], ans);
		if(d[0][i]>=d[1][i])
			continue;
		for(int j : adj[0][i]) {
			if(p[i]^j&&p[j]^i&&p[i]^p[j]&&(p[i]<0||p[p[i]]^j)&&(p[j]<0||p[p[j]]^i)) {
				cout << -1;
				return 0;
			}
		}
	}
	cout << ans;
}
