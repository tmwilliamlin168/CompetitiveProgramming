#include <bits/stdc++.h>
using namespace std;

const int mxN=2e4, mxM=2e5;
int n, m, eu[mxM], ev[mxM], ew[mxM], tin[mxN], low[mxN], dt=1, who[mxN], st[mxN], sth, c[mxN], d[mxN], qu[mxN], qt;
vector<int> adj1[mxN], adj2[mxN], adj3[mxN], ans;
bool in[mxN];

void dfs1(int u) {
	tin[u]=low[u]=dt++;
	st[sth++]=u;
	for(int v : adj1[u]) {
		if(!tin[v]) {
			dfs1(v);
			low[u]=min(low[v], low[u]);
		} else if(~tin[v])
			low[u]=min(tin[v], low[u]);
	}
	if(low[u]>=tin[u]) {
		do {
			tin[st[sth-1]]=-1;
			who[st[--sth]]=u;
		} while(st[sth]^u);
	}
}

void dfs2(int u, int cu) {
	c[u]=cu;
	for(int v : adj2[u])
		if(c[v]<0)
			dfs2(v, cu);
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> n >> m;
	for(int i=0; i<m; ++i) {
		cin >> eu[i] >> ev[i] >> ew[i], --eu[i], --ev[i];
		adj1[eu[i]].push_back(ev[i]);
	}
	for(int i=0; i<n; ++i)
		if(!tin[i])
			dfs1(i);
	for(int i=0; i<m; ++i) {
		eu[i]=who[eu[i]];
		ev[i]=who[ev[i]];
		if(!ew[i]&&eu[i]^ev[i]) {
			adj2[eu[i]].push_back(ev[i]);
			in[ev[i]]=1;
		}
	}
	memset(c, -1, 4*n);
	for(int i=0; i<n; ++i)
		if(who[i]==i&&!in[i])
			dfs2(i, i);
	for(int i=0; i<m; ++i) {
		eu[i]=c[eu[i]];
		ev[i]=c[ev[i]];
		if(ew[i]) {
			adj3[ev[i]].push_back(eu[i]);
			++d[eu[i]];
		} else if(eu[i]^ev[i]) {
			cout << -1;
			return 0;
		}
	}
	for(int i=0; i<n; ++i)
		if(c[i]==i&&!d[i])
			qu[qt++]=i;
	for(int qh=0; qh<qt; ++qh) {
		int u=qu[qh];
		ans.push_back(u);
		for(int v : adj3[u]) {
			--d[v];
			if(!d[v])
				qu[qt++]=v;
		}
	}
	for(int i=0; i<n; ++i)
		if(c[i]^i)
			ans.push_back(i);
	if(ans.size()<n)
		cout << -1;
	else
		for(int a : ans)
			cout << a+1 << " ";
}
