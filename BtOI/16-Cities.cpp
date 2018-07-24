/*
	- https://www.youtube.com/watch?v=BG4vAoV5kWw
*/

#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pli pair<ll, int>
#define fi first
#define se second

const int mxN=1e5, mxK=5;
int n, k, m, a[mxK];
vector<pli> adj[mxN];
ll dist[1<<mxK][mxN], ans=LLONG_MAX;
priority_queue<pli, vector<pli>, greater<pli>> pq;

inline void dijkstra(ll dist[mxN]) {
	for(int i=0; i<n; ++i)
		pq.push({dist[i], i});
	while(!pq.empty()) {
		pli p=pq.top();
		pq.pop();
		int u=p.se;
		if(p.fi>dist[u])
			continue;
		for(pli e : adj[u]) {
			int v=e.se;
			if(dist[u]+e.fi<dist[v]) {
				dist[v]=dist[u]+e.fi;
				pq.push({dist[v], v});
			}
		}
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> k >> m;
	for(int i=0; i<k; ++i)
		cin >> a[i], --a[i];
	while(m--) {
		int u, v, w;
		cin >> u >> v >> w, --u, --v;
		adj[u].push_back({w, v});
		adj[v].push_back({w, u});
	}
	for(int i=0; i<k; ++i) {
		memset(dist[1<<i], 0x3F, 8*n);
		dist[1<<i][a[i]]=0;
	}
	for(int i=1; i<1<<k; ++i) {
		if(__builtin_popcount(i)>1) {
			memset(dist[i], 0x3F, 8*n);
			for(int j=0; j<k; ++j)
				if(i>>j&1)
					for(int l=0; l<n; ++l)
						dist[i][l]=min(dist[i^1<<j][l]+dist[1<<j][l], dist[i][l]);
		}
		dijkstra(dist[i]);
	}
	for(int i=0; i<n; ++i)
		ans=min(dist[(1<<k)-1][i], ans);
	cout << ans;
}
