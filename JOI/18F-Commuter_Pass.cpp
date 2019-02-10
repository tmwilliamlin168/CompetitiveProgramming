/*
	- 3 cases: u -> v, u -> s2 -> t2 -> v, u -> t2 -> s2 -> v, where s -> s2 -> t2 -> t is a shortest path
		- 1st case is trivial, 2nd is same as 3rd
	- Precompute distances from u, v, s, and t
	- The edges on all shortest paths on s -> t form a DAG
	- Do a DP on the DAG, dp[i] = minimum cost to node v from node i
*/

#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pli pair<ll, int>
#define fi first
#define se second

const int mxN=1e5;
int n, m, s, t, u, v;
vector<pli> adj[mxN];
ll du[mxN], dv[mxN], ds[mxN], dt[mxN], dp[mxN], ans;
priority_queue<pli, vector<pli>, greater<pli>> pq;

void dijkstra(int s, ll dist[mxN]) {
	memset(dist, 0x3F, 8*n);
	dist[s]=0;
	pq.push({0, s});
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

ll cdp(int u, bool a) {
	if(dp[u]==-1) {
		if(ds[u]+dt[u]==ds[t]) {
			dp[u]=dv[u];
			for(pli e : adj[u])
				if(a?ds[u]+e.fi==ds[e.se]:dt[u]+e.fi==dt[e.se])
					dp[u]=min(cdp(e.se, a), dp[u]);
			ans=min(du[u]+dp[u], ans);
		} else
			dp[u]=1e18;
	}
	return dp[u];
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> m >> s >> t >> u >> v, --s, --t, --u, --v;
	while(m--) {
		int ui, vi, wi;
		cin >> ui >> vi >> wi, --ui, --vi;
		adj[ui].push_back({wi, vi});
		adj[vi].push_back({wi, ui});
	}
	dijkstra(u, du);
	dijkstra(v, dv);
	dijkstra(s, ds);
	dijkstra(t, dt);
	ans=du[v];
	memset(dp, -1, 8*n);
	cdp(t, 0);
	memset(dp, -1, 8*n);
	cdp(s, 1);
	cout << ans;
}
