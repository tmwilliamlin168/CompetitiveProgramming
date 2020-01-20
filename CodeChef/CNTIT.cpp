#include <bits/stdc++.h>
using namespace std;

#define ar array

const int mxN=2e5;
int t, n, k, s[mxN], ctp[mxN], ki, a[mxN+2];
vector<ar<int, 2>> adj[mxN];
vector<int> pt, pta;
long long ans;

void upd(int i, int x) {
	for(i+=mxN/2, ++i; i<=mxN+1; i+=i&-i)
		a[i]+=x;
}

int qry(int i) {
	int r=0;
	for(i+=mxN/2; i; i-=i&-i)
		r+=a[i];
	return r;
}

void dfs2(int u, int p=-1) {
	s[u]=1;
	for(ar<int, 2> e : adj[u]) {
		int v=e[0];
		if(v^p&&ctp[v]==-1) {
			dfs2(v, u);
			s[u]+=s[v];
		}
	}
}

int dfs4(int u, int n, int p=-1) {
	for(ar<int, 2> e : adj[u]) {
		int v=e[0];
		if(v^p&&ctp[v]==-1&&s[v]>n/2)
			return dfs4(v, n, u);
	}
	return u;
}

void dfs5(int u, int s, int p=-1) {
	pt.push_back(s);
	for(ar<int, 2> e : adj[u]) {
		int v=e[0];
		if(v==p||~ctp[v])
			continue;
		dfs5(v, s+(e[1]^ki?1:-1), u);
	}
}

void dfs3(int u=0, int p=-2) {
	int c=dfs4(u, s[u]);
	ctp[c]=p;
	dfs2(c);
	for(ki=0; ki<k; ++ki) {
		for(ar<int, 2> e : adj[c]) {
			int v=e[0];
			if(ctp[v]==-1) {
				dfs5(v, e[1]^ki?1:-1);
				for(int pti : pt)
					ans-=qry(-pti);
				for(int pti : pt)
					upd(pti, 1);
				pta.insert(pta.end(), pt.begin(), pt.end());
				pt.clear();
			}
		}
		for(int pti : pta)
			upd(pti, -1);
		pta.clear();
	}
	for(ar<int, 2> e : adj[c]) {
		int v=e[0];
		if(ctp[v]==-1)
			dfs3(v, c);
	}
}

void solve() {
	cin >> n >> k;
	for(int i=0; i<n; ++i)
		adj[i].clear();
	for(int i=1, u, v, c; i<n; ++i) {
		cin >> u >> v >> c, --u, --v, --c;
		adj[u].push_back({v, c});
		adj[v].push_back({u, c});
	}
	memset(ctp, -1, 4*n);
	dfs2(0);
	ans=(long long)n*(n-1)/2;
	dfs3();
	cout << ans << "\n";
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	upd(0, 1);
	cin >> t;
	while(t--)
		solve();
}
