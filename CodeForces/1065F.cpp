#include <bits/stdc++.h>
using namespace std;

const int mxN=1e6;
int n, k, a[mxN], tin[mxN], low[mxN], who[mxN], dt, st[mxN], sth, d[mxN];
vector<int> adj1[mxN], adj2[mxN];

void dfs1(int u, int p=-1) {
	d[u]=p==-1?0:d[p]+1;
	st[d[u]]=u;
	for(int v : adj1[u])
		dfs1(v, u);
	if(u&&!adj1[u].size())
		adj1[u].push_back(st[max(d[u]-k, 0)]);
}

void dfs2(int u) {
	tin[u]=low[u]=dt++;
	st[sth++]=u;
	for(int v : adj1[u]) {
		if(!tin[v]) {
			dfs2(v);
			low[u]=min(low[v], low[u]);
		} else if(tin[v]>0)
			low[u]=min(tin[v], low[u]);
	}
	if(low[u]==tin[u]) {
		do {
			tin[st[sth-1]]=-1;
			who[st[sth-1]]=u;
			if(st[sth-1]!=u)
				a[u]+=a[st[sth-1]];
		} while(st[--sth]!=u);
	}
}

void dfs3(int u) {
	tin[u]=0;
	int b=0;
	for(int v : adj2[u]) {
		if(tin[v])
			dfs3(v);
		b=max(a[v], b);
	}
	a[u]+=b;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> k;
	for(int i=1; i<n; ++i) {
		int pi;
		cin >> pi;
		adj1[pi-1].push_back(i);
	}
	for(int i=0; i<n; ++i)
		a[i]=!adj1[i].size();
	dfs1(0);
	dt=1;
	dfs2(0);
	for(int u=0; u<n; ++u)
		if(tin[u])
			for(int v : adj1[u])
				if(tin[v]&&who[v]!=who[u])
					adj2[who[u]].push_back(who[v]);
	dfs3(who[0]);
	cout << a[who[0]];
}
