#include <bits/stdc++.h>
using namespace std;

const int mxN=5e5;
int n, m, a[mxN], s, p, tin[mxN], low[mxN], who[mxN], dt=1, st[mxN], sth;
vector<int> adj1[mxN], adj2[mxN];
bool fin[mxN];

void dfs1(int u) {
	tin[u]=low[u]=dt++;
	st[sth++]=u;
	for(int v : adj1[u]) {
		if(!tin[v]) {
			dfs1(v);
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
			if(fin[st[sth-1]])
				fin[u]=1;
		} while(st[--sth]!=u);
	}
}

void dfs2(int u) {
	tin[u]=0;
	int b=0;
	for(int v : adj2[u]) {
		if(tin[v])
			dfs2(v);
		if(fin[v]) {
			b=max(a[v], b);
			fin[u]=1;
		}
	}
	a[u]+=b;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> m;
	for(int i=0; i<m; ++i) {
		int u, v;
		cin >> u >> v;
		adj1[u-1].push_back(v-1);
	}
	for(int i=0; i<n; ++i)
		cin >> a[i];
	cin >> s >> p, --s;
	for(int i=0; i<p; ++i) {
		int pi;
		cin >> pi;
		fin[pi-1]=1;
	}
	dfs1(s);
	for(int u=0; u<n; ++u)
		if(tin[u])
			for(int v : adj1[u])
				if(tin[v]&&who[v]!=who[u])
					adj2[who[u]].push_back(who[v]);
	dfs2(who[s]);
	cout << a[who[s]];
}
