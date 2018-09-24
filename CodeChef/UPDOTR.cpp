#include <bits/stdc++.h>
using namespace std;

const int mxN=1e6;
int t, n, a[mxN], anc[mxN][20], b[mxN][20];
vector<int> adj[mxN];

void dfs(int u, int p=-1) {
	anc[u][0]=p;
	for(int i=1; i<20; ++i)
		anc[u][i]=anc[u][i-1]==-1?-1:anc[anc[u][i-1]][i-1];
	b[u][0]=p==-1||a[u]>a[p];
	for(int i=1; i<20; ++i)
		b[u][i]=b[u][i-1]+(anc[u][i-1]==-1?0:b[anc[u][i-1]][i-1]);
	a[u]=max(a[p], a[u]);
	for(int v : adj[u])
		dfs(v, u);
}

void solve() {
	cin >> n;
	for(int i=0; i<n; ++i) {
		cin >> a[i];
		adj[i].clear();
	}
	int pi, q, ans=0, vi, wi;
	for(int i=1; i<n; ++i) {
		cin >> pi, --pi;
		adj[pi].push_back(i);
	}
	dfs(0);
	cin >> q;
	while(q--) {
		cin >> vi >> wi, vi=(vi^ans)-1, wi^=ans;
		ans=0;
		for(int i=19; i>=0; --i) {
			if(anc[vi][i]!=-1&&a[anc[vi][i]]>wi) {
				ans+=b[vi][i];
				vi=anc[vi][i];
			}
		}
		if(a[vi]>wi)
			ans+=b[vi][0];
		cout << ans << "\n";
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> t;
	while(t--)
		solve();
}
