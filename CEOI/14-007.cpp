/*
	- If one of them have different distances the two servers, that person will always go to the closest server first
	- Otherwise, the server to go to first may depend on the other person's actions
	- If Dr. Null has the same distance from both servers longer than 007, then 007 will have to go one time unit earlier
*/

#include <bits/stdc++.h>
using namespace std;

const int mxN=2e5;
int n, m, s, d, a, b, da[mxN], db[mxN], qu[mxN], qh, qt, dp[mxN];
vector<int> adj[mxN];

inline void bfs(int s, int dist[mxN]) {
	qh=qt=0;
	memset(dist, 0x3F, 4*n);
	qu[qt++]=s;
	dist[s]=0;
	while(qh<qt) {
		int u=qu[qh++];
		for(int v : adj[u]) {
			if(dist[v]>n) {
				qu[qt++]=v;
				dist[v]=dist[u]+1;
			}
		}
	}
}

int cdp(int u) {
	if(!dp[u]) {
		dp[u]=da[u];
		for(int v : adj[u])
			if(da[v]==da[u]-1&&da[v]==db[v])
				dp[u]=min(cdp(v), dp[u]);
	}
	return dp[u];
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> m >> s >> d >> a >> b, --s, --d, --a, --b;
	while(m--) {
		int u, v;
		cin >> u >> v, --u, --v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	bfs(a, da);
	bfs(b, db);
	if(da[s]!=db[s]||da[d]!=db[d])
		cout << max(min(da[d]-da[s], db[d]-db[s]), -1);
	else
		cout << max(da[d]-da[s]-(cdp(d)<cdp(s)), -1);
}
