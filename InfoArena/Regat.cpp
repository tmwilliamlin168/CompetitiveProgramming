/*
	- Maintain distances in a data structure while doing dfs
	- When we get to a node, answer k queries by querying for the maximum k distances in the data structure
	- We can use segment tree with range add updates and range max queries
*/

#include <bits/stdc++.h>
using namespace std;

const int mxN=1e5;
int n, m, ds[mxN], de[mxN], dt, lz[1<<18];
vector<array<int, 2>> adj[mxN];
vector<int> ta[mxN];
array<int, 2> st[1<<18], ans[mxN];

void bld(int i=1, int l=0, int r=n-1) {
	if(l==r) {
		st[i]={0, l};
		return;
	}
	int m=(l+r)/2;
	bld(2*i, l, m);
	bld(2*i+1, m+1, r);
	st[i]=max(st[2*i], st[2*i+1]);
}

void app(int i, int x) {
	st[i][0]+=x;
	lz[i]+=x;
}

void upd(int l1, int r1, int x, int i=1, int l2=0, int r2=n-1) {
	if(l1<=l2&&r2<=r1) {
		app(i, x);
		return;
	}
	int m2=(l2+r2)/2;
	app(2*i, lz[i]);
	app(2*i+1, lz[i]);
	lz[i]=0;
	if(l1<=m2)
		upd(l1, r1, x, 2*i, l2, m2);
	if(m2<r1)
		upd(l1, r1, x, 2*i+1, m2+1, r2);
	st[i]=max(st[2*i], st[2*i+1]);
}

void dfs1(int u=0, int p=-1) {
	ds[u]=dt++;
	for(array<int, 2> v : adj[u]) {
		if(v[0]==p)
			continue;
		dfs1(v[0], u);
		upd(ds[v[0]], de[v[0]]-1, v[1]);
	}
	de[u]=dt;
}

void dfs2(int u=0, int p=-1) {
	for(int i : ta[u]) {
		ans[i]=st[1];
		upd(ans[i][1], ans[i][1], -1e9);
	}
	for(int i : ta[u])
		upd(ans[i][1], ans[i][1], 1e9);
	for(array<int, 2> v : adj[u]) {
		if(v[0]==p)
			continue;
		upd(0, n-1, v[1]);
		upd(ds[v[0]], de[v[0]]-1, -2*v[1]);
		dfs2(v[0], u);
		upd(0, n-1, -v[1]);
		upd(ds[v[0]], de[v[0]]-1, 2*v[1]);
	}
}

int main() {
	ifstream cin("regat.in");
	ofstream cout("regat.out");

	cin >> n >> m;
	for(int i=1, u, v, w; i<n; ++i) {
		cin >> u >> v >> w, --u, --v;
		adj[u].push_back({v, w});
		adj[v].push_back({u, w});
	}
	for(int i=0, u; i<m; ++i)
		cin >> u, ta[u-1].push_back(i);
	bld();
	dfs1();
	dfs2();
	for(int i=0; i<m; ++i)
		cout << ans[i][0] << "\n";
}
