/*
	- All edges on cycles can go both ways
	- Bridges are not on cycles
	- After compressing non-bridge edges with DSU, a forest is left
	- When we are given (x, y), we need to set all edges on x->lca(x, y) to 1 and all edges on lca(x, y)->y to -1
		- Don't have to worry about conflicts since problem guarantees that a solution exists
		- One way to do this is to add 1 to x->root and add -1 to y->root
	- Finally, go through the bridges. If it has value = 0, it can go both ways. If it is positive, it goes up; otherwise, it goes down.
*/

#include <bits/stdc++.h>
using namespace std;

const int mxN=1e5;
int n, m, k, a[mxN], b[mxN], d[mxN], s[mxN], p[mxN], r[mxN], dt=1, tin[mxN], low[mxN];
bool bg[mxN];
vector<int> adj1[mxN], adj2[mxN];

int find(int x) {
	return x==p[x]?x:(p[x]=find(p[x]));
}

inline void join(int x, int y) {
	if((x=find(x))==(y=find(y)))
		return;
	if(r[x]<r[y])
		p[x]=y;
	else
		p[y]=x;
	if(r[x]==r[y])
		++r[x];
}

void dfs1(int u, int p) {
	tin[u]=low[u]=dt++;
	for(int e : adj1[u]) {
		int v=u^a[e]^b[e];
		if(!tin[v]) {
			dfs1(v, e);
			low[u]=min(low[v], low[u]);
			if(low[v]>tin[u])
				bg[e]=1;
		} else if(e!=p)
			low[u]=min(tin[v], low[u]);
	}
}

void dfs2(int u, int p) {
	for(int e : adj2[u]) {
		int v=u^a[e]^b[e];
		if(v==p)
			continue;
		d[v]=d[u]+1;
		dfs2(v, u);
		s[u]+=s[v];
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> m;
	for(int i=0; i<n; ++i)
		p[i]=i;
	for(int i=0; i<m; ++i) {
		cin >> a[i] >> b[i], --a[i], --b[i];
		adj1[a[i]].push_back(i);
		adj1[b[i]].push_back(i);
	}
	for(int i=0; i<n; ++i)
		if(!tin[i])
			dfs1(i, -1);
	for(int i=0; i<m; ++i)
		if(!bg[i])
			join(a[i], b[i]);
	for(int i=0; i<m; ++i) {
		if(!bg[i])
			continue;
		a[i]=find(a[i]);
		b[i]=find(b[i]);
		adj2[a[i]].push_back(i);
		adj2[b[i]].push_back(i);
	}
	cin >> k;
	while(k--) {
		int x, y;
		cin >> x >> y, --x, --y;
		++s[find(x)], --s[find(y)];
	}
	for(int i=0; i<n; ++i) {
		if(p[i]==i&&!d[i]) {
			d[i]=1;
			dfs2(i, -1);
		}
	}
	for(int i=0; i<m; ++i) {
		if(!bg[i]) {
			cout << 'B';
			continue;
		}
		int u=d[a[i]]>d[b[i]]?a[i]:b[i];
		cout << (s[u]?((s[u]>0)==(u==a[i])?'R':'L'):'B');
	}
}
