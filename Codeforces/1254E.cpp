#include <bits/stdc++.h>
using namespace std;

const int mxN=5e5, M=1e9+7;
int n, p[mxN], d[mxN], a[mxN], b[mxN], g1[mxN], g2[mxN], vis[mxN];
vector<int> adj[mxN], adj2[mxN];
vector<array<int, 2>> e[mxN];
bool c1[mxN], c2[mxN];
long long ans=1;

void fk() {
	cout << 0;
	exit(0);
}

void dfs(int u=0, int pu=-1) {
	p[u]=pu;
	d[u]=~pu?d[pu]+1:0;
	for(int v : adj[u])
		if(v^pu)
			dfs(v, u);
}

void pr(int u, int v) {
	vector<int> w1, w2;
	while(u^v) {
		if(d[u]>d[v]) {
			if(c1[u])
				fk();
			c1[u]=1;
			w1.push_back(u);
			++b[u];
			u=p[u];
		} else {
			if(c2[v])
				fk();
			c2[v]=1;
			w2.push_back(v);
			++b[v];
			v=p[v];
		}
	}
	++b[u];
	w1.push_back(u);
	w1.insert(w1.end(), w2.rbegin(), w2.rend());
	g1[w1[0]]=w1[1];
	for(int i=0; i+2<w1.size(); ++i)
		e[w1[i+1]].push_back({w1[i], w1[i+2]});
	g2[w1.back()]=w1[w1.size()-2];
}

int dfs2(int u, int r) {
	if(vis[u]==r)
		fk();
	if(vis[u])
		return 0;
	vis[u]=r;
	int s=1;
	for(int v : adj2[u])
		s+=dfs2(v, r);
	return s;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> n;
	for(int i=1, u, v; i<n; ++i) {
		cin >> u >> v, --u, --v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	dfs();
	memset(g1, -1, 4*n);
	memset(g2, -1, 4*n);
	for(int i=0; i<n; ++i) {
		cin >> a[i], --a[i];
		if(i==a[i])
			fk();
		if(~a[i])
			pr(i, a[i]);
	}
	for(int i=0; i<n; ++i) {
		vector<int> v;
		for(array<int, 2> f : e[i]) {
			adj2[f[0]].push_back(f[1]);
			v.push_back(f[0]);
			v.push_back(f[1]);
		}
		if(~g1[i])
			v.push_back(g1[i]);
		if(~g1[i]&&~g2[i]&&dfs2(g1[i], g1[i]+1)<adj[i].size()&&vis[g2[i]])
			fk();
		for(int w : v)
			if(!vis[w])
				dfs2(w, w+1);
		for(int w : v) {
			vis[w]=0;
			adj2[w].clear();
		}
		for(int j=2; j<=(int)adj[i].size()-b[i]; ++j)
			ans=ans*j%M;
	}
	cout << ans;
}
