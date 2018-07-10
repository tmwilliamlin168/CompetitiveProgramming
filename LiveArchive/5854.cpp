/*
	- For each gas station (and the starting point), find which cities can be reached without refilling
	- Create a second graph with edges u->v where u are the gas stations and v are the cities that can be reached
		- Edges have lengths equal to the distances in the original graph
	- Do dijkstra on the second graph for the answer
*/

#include <bits/stdc++.h>
using namespace std;

#define pii pair<int, int>
#define fi first
#define se second

const int mxN=6000, INF=1e9;
int n, m, k, c, dist[mxN];
unordered_map<string, int> mp;
vector<pii> adj1[mxN], adj2[mxN];

inline int rci() {
	string cs;
	cin >> cs;
	return mp.find(cs)==mp.end()?(mp[cs]=n++):mp[cs];
}

inline void dijkstra(vector<pii> adj[mxN], vector<pii> &r, int s, int md) {
	priority_queue<pii, vector<pii>, greater<pii>> pq;
	pq.push({0, s});
	for(int i=0; i<n; ++i)
		dist[i]=i==s?0:INF;
	while(!pq.empty()) {
		pii p=pq.top();
		pq.pop();
		int u=p.se;
		if(p.fi>dist[u]||dist[u]>md)
			continue;
		r.push_back({u, dist[u]});
		for(pii e : adj[u]) {
			int v=e.fi;
			if(dist[v]>dist[u]+e.se) {
				dist[v]=dist[u]+e.se;
				pq.push({dist[v], v});
			}
		}
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	while(1) {
		cin >> m >> k >> c;
		if(!m)
			break;
		int s=rci(), t=rci();
		while(m--) {
			int u=rci(), v=rci(), d;
			cin >> d;
			adj1[u].push_back({v, d});
			adj1[v].push_back({u, d});
		}
		dijkstra(adj1, adj2[s], s, 10*c);
		while(k--) {
			int u=rci();
			dijkstra(adj1, adj2[u], u, 10*c);
		}
		vector<pii> a1;
		dijkstra(adj2, a1, s, INF);
		int a2=-1;
		for(pii p : a1)
			if(p.fi==t)
				a2=p.se;
		cout << a2 << "\n";
		mp.clear();
		for(int i=0; i<n; ++i) {
			adj1[i].clear();
			adj2[i].clear();
		}
		n=0;
	}
}
