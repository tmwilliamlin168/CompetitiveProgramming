/*
	- Consider when we add an edge between nodes u and v that have a and b amounts of data, respectively, with c being the same
		- Both components of u and v will now have a + b - c amounts of data
	- c is just the amount of data shared between u and v the last time they were connected
	- We now need to support the following queries:
		- Add an edge
		- Delete an edge
		- Set values of all nodes in a connected component to x
		- Find the value of a node
	- Each connected component can be represented by the node that is closest to the root
	- Let's color / erase these nodes when we add / delete edges
		- Note that when we add an edge, one of its endpoints will become a representative
	- A connected component's representative can be found with binary search and path sum queries (using binary indexed tree)
	- For the set / find values queries, just process them on the representative
	- O(nlog^2n) since it's O(log^2n) for finding a representative
*/

#include <bits/stdc++.h>
using namespace std;

const int mxN=1e5;
int n, m, q, x[mxN-1], y[mxN-1], st[mxN], en[mxN], dt, ft[mxN+1], v[mxN], lc[mxN-1], anc[mxN][17], dj, ck;
vector<int> adj[mxN];

inline void upd(int i, int x) {
	for(++i; i<=n; i+=i&-i)
		ft[i]+=x;
}

inline int qry(int i) {
	int r=0;
	for(++i; i; i-=i&-i)
		r+=ft[i];
	return r;
}

void dfs(int u, int p) {
	st[u]=dt++;
	anc[u][0]=p;
	for(int i=1; i<17; ++i)
		anc[u][i]=anc[u][i-1]==-1?-1:anc[anc[u][i-1]][i-1];
	for(int v : adj[u])
		if(v!=p)
			dfs(v, u);
	en[u]=dt;
}

inline int find(int x) {
	int a=qry(st[x]), b=x;
	for(int i=16; i>=0; --i)
		if(anc[b][i]!=-1&&qry(st[anc[b][i]])==a)
			b=anc[b][i];
	return b;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> m >> q;
	for(int i=0; i<n-1; ++i) {
		cin >> x[i] >> y[i], --x[i], --y[i];
		adj[x[i]].push_back(y[i]);
		adj[y[i]].push_back(x[i]);
	}
	dfs(0, -1);
	for(int i=0; i<n; ++i) {
		v[i]=1;
		upd(st[i], 1);
		upd(en[i], -1);
	}
	for(int i=0; i<n-1; ++i)
		if(anc[x[i]][0]==y[i])
			swap(x[i], y[i]);
	while(m--) {
		cin >> dj, --dj;
		int x2=find(x[dj]);
		if(lc[dj]==-1) {
			upd(st[y[dj]], 1);
			upd(en[y[dj]], -1);
			lc[dj]=v[y[dj]]=v[x2];
		} else {
			upd(st[y[dj]], -1);
			upd(en[y[dj]], 1);
			v[x2]+=v[y[dj]]-lc[dj];
			lc[dj]=-1;
		}
	}
	while(q--) {
		cin >> ck, --ck;
		cout << v[find(ck)] << "\n";
	}
}
