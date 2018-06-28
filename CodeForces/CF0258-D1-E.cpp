/*
	- Calculate dfs order to represent a subtree with an interval
	- Do another dfs maintaining a segment tree that can add / remove an interval and find the total length of the intervals' union
	- For an operation (a, b), add the interval for b when the dfs enters a and remove the interval when it exits since the interval affects all nodes in a's subtree
*/

#include <bits/stdc++.h>
using namespace std;

const int mxN=1e5;
int n, m, st[mxN], en[mxN], dt=0, c[mxN], sta[1<<18], stb[1<<19];
vector<int> adj[mxN], v1[mxN];

void upd(int l1, int r1, int x, int i=1, int l2=0, int r2=n-1) {
	if(!(l1<=l2&&r2<=r1)) {
		int m2=(l2+r2)/2;
		if(l1<=m2)
			upd(l1, r1, x, 2*i, l2, m2);
		if(m2<r1)
			upd(l1, r1, x, 2*i+1, m2+1, r2);
	} else
		sta[i]+=x;
	stb[i]=sta[i]?r2-l2+1:stb[2*i]+stb[2*i+1];
}

void dfs1(int u, int p) {
	st[u]=dt++;
	for(int v : adj[u])
		if(v!=p)
			dfs1(v, u);
	en[u]=dt;
}

void dfs2(int u, int p) {
	if(!v1[u].empty())
		upd(st[u], en[u]-1, 1);
	for(int vi : v1[u])
		upd(st[vi], en[vi]-1, 1);
	c[u]=max(stb[1]-1, 0);
	for(int v : adj[u])
		if(v!=p)
			dfs2(v, u);
	for(int vi : v1[u])
		upd(st[vi], en[vi]-1, -1);
	if(!v1[u].empty())
		upd(st[u], en[u]-1, -1);
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> m;
	for(int i=0; i<n-1; ++i) {
		int u, v;
		cin >> u >> v, --u, --v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	while(m--) {
		int a, b;
		cin >> a >> b, --a, --b;
		v1[a].push_back(b);
		v1[b].push_back(a);
	}
	dfs1(0, -1);
	dfs2(0, -1);
	for(int i=0; i<n; ++i)
		cout << c[i] << " ";
}
