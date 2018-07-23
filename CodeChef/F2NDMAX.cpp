#include <bits/stdc++.h>
using namespace std;

const int mxN=3e5;
int t, n, m, din[mxN], dout[mxN], cc;
vector<int> adj[mxN];

inline void solve() {
	cin >> n >> m;
	memset(din, 0, 4*n);
	memset(dout, 0, 4*n);
	for(int i=0; i<n; ++i)
		adj[i].clear();
	while(m--) {
		int u, v;
		cin >> u >> v, --u, --v;
		adj[u].push_back(v);
		++din[v];
	}
	for(int i=0; i<n; ++i)
		for(int j : adj[i])
			dout[i]+=din[j]==1;
	cc=0;
	priority_queue<int, vector<int>, greater<int>> pq;
	for(int i=0; i<n; ++i) {
		cc+=!din[i];
		if(!din[i])
			pq.push(dout[i]);
	}
	while(pq.size()>1) {
		int a=pq.top();
		pq.pop();
		int b=pq.top();
		pq.pop();
		pq.push(max(a, b)+1);
	}
	cout << cc+pq.top()-2 << "\n";
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> t;
	while(t--)
		solve();
}
