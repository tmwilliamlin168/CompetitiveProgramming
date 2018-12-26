/*
	- If b>=a, we can use bfs to solve the problem
	- Consider dijkstra for this problem, in which we search 2 edges deep instead of 1 (and ignore the triangle restriction)
	- The cost for traveling 2 edges deep is constant, so we can ignore the 2nd edge in the future for all 2-edge-deep searches which results in a fast and correct solution
	- Sometimes we may come upon a triangle and we can't use the 2nd edge
	- There are at most O(msqrtm) triangles in a graph, so we only skip O(msqrtm) times
*/

#include <bits/stdc++.h>
using namespace std;

const int mxN=1e5;
int n, m, k, a, b, eu[mxN], ev[mxN], qu[mxN], qt, d[mxN];
vector<int> adj[mxN], ts[mxN], adj2[mxN];
bool c[mxN];
priority_queue<array<int, 2>, vector<array<int, 2>>, greater<array<int, 2>>> pq;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin >> n >> m >> k >> a >> b, --k;
	for(int i=0; i<m; ++i) {
		cin >> eu[i] >> ev[i], --eu[i], --ev[i];
		adj[eu[i]].push_back(i);
		adj[ev[i]].push_back(i);
	}
	memset(d, 0x3f, 4*n);
	if(b>=a) {
		qu[qt++]=k;
		d[k]=0;
		for(int qh=0; qh<n; ++qh) {
			int u=qu[qh];
			for(int e : adj[u]) {
				int v=u^eu[e]^ev[e];
				if(d[v]>d[u]+1) {
					qu[qt++]=v;
					d[v]=d[u]+1;
				}
			}
		}
		for(int i=0; i<n; ++i)
			cout << d[i]/2*min(2*a, b)+d[i]%2*a << "\n";
		return 0;
	}
	for(int i=0; i<n; ++i) {
		for(int e : adj[i])
			c[i^eu[e]^ev[e]]=1;
		for(int e1 : adj[i]) {
			int v=i^eu[e1]^ev[e1];
			if(array<int, 2>{adj[i].size(), i}<array<int, 2>{adj[v].size(), v})
				continue;
			for(int e2 : adj[v])
				if(c[v^eu[e2]^ev[e2]])
					ts[e1].push_back(v^eu[e2]^ev[e2]);
		}
		for(int e : adj[i])
			c[i^eu[e]^ev[e]]=0;
		adj2[i]=adj[i];
	}
	d[k]=0;
	pq.push({0, k});
	while(pq.size()) {
		array<int, 2> u=pq.top();
		pq.pop();
		if(d[u[1]]<u[0])
			continue;
		for(int e1 : adj[u[1]]) {
			int v=u[1]^eu[e1]^ev[e1];
			if(d[v]>u[0]+a) {
				d[v]=u[0]+a;
				pq.push({d[v], v});
			}
			c[u[1]]=1;
			for(int t : ts[e1])
				c[t]=1;
			vector<int> na;
			for(int e2 : adj2[v]) {
				int w=v^eu[e2]^ev[e2];
				if(c[w]) {
					na.push_back(e2);
					continue;
				}
				if(d[w]>u[0]+b) {
					d[w]=u[0]+b;
					pq.push({d[w], w});
				}
			}
			adj2[v]=na;
			c[u[1]]=0;
			for(int t : ts[e1])
				c[t]=0;
		}
	}
	for(int i=0; i<n; ++i)
		cout << d[i] << "\n";
}
