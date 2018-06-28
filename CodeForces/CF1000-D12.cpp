/*
	- Diameter of the bridge tree
*/

#include <bits/stdc++.h>
using namespace std;

const int mxN=3e5;
int n, m, k, a[mxN], b[mxN], d[mxN], dt=1, tin[mxN], low[mxN], who[mxN], st[mxN], sth, bccI, mdu;
vector<int> adj1[mxN], adj2[mxN];

void dfs1(int u, int p) {
	tin[u]=low[u]=dt++;
	st[sth++]=u;
	for(int e : adj1[u]) {
		int v=u^a[e]^b[e];
		if(!tin[v]) {
			dfs1(v, e);
			low[u]=min(low[v], low[u]);
		} else if(e!=p)
			low[u]=min(tin[v], low[u]);
	}
	if(low[u]==tin[u]) {
		st[sth]=-1;
		while(st[sth]!=u)
			who[st[--sth]]=bccI;
		++bccI;
	}
}

void dfs2(int u, int p) {
	d[u]=p==-1?0:d[p]+1;
	if(mdu==-1||d[u]>d[mdu])
		mdu=u;
	for(int e : adj2[u]) {
		int v=u^a[e]^b[e];
		if(v==p)
			continue;
		dfs2(v, u);
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> m;
	for(int i=0; i<m; ++i) {
		cin >> a[i] >> b[i], --a[i], --b[i];
		adj1[a[i]].push_back(i);
		adj1[b[i]].push_back(i);
	}
	dfs1(0, -1);
	for(int i=0; i<m; ++i) {
		if((a[i]=who[a[i]])==(b[i]=who[b[i]]))
			continue;
		adj2[a[i]].push_back(i);
		adj2[b[i]].push_back(i);
	}
	mdu=-1;
	dfs2(0, -1);
	int u=mdu;
	mdu=-1;
	dfs2(u, -1);
	cout << d[mdu];
}
