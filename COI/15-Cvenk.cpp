/*
	- The given graph is a tree, finding the minimum sum of distances to a node is a standard problem
	- Create a compressed tree, kind of like a dynamic segment tree, so the number of nodes is O(nlog(1e9))
*/

#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int mxN=1e5, mxM=261*mxN;
int n, m, ri, ci, s1[mxM], d[mxM];
array<int, 2> adj[mxM][3];

void ae(int u, int v, int w) {
	adj[u][d[u]++]={v, w};
	adj[v][d[v]++]={u, w};
}

array<int, 3> bld(vector<array<int, 2>> &ps, int k=30) {
	if(!k) {
		s1[m++]+=ps.size();
		return {m-1, m-1, m-1};
	}
	if(!ps.size()) {
		m+=3;
		ae(m-3, m-2, (1<<k)-1);
		ae(m-3, m-1, (1<<k)-1);
		return {m-3, m-2, m-1};
	}
	vector<array<int, 2>> np[3];
	for(array<int, 2> a : ps)
		np[a[0]>>k-1&1|(a[1]>>k-1&1)<<1].push_back(a);
	array<int, 3> c[3];
	for(int i=0; i<3; ++i)
		c[i]=bld(np[i], k-1);
	ae(c[0][1], c[1][0], 1);
	ae(c[0][2], c[2][0], 1);
	return {c[0][0], c[1][1], c[2][2]};
}

ll dfs1(int u=0, int p=-1) {
	ll s2=0;
	for(int i=0; i<d[u]; ++i) {
		if(adj[u][i][0]==p)
			continue;
		s2+=dfs1(adj[u][i][0], u)+(ll)s1[adj[u][i][0]]*adj[u][i][1];
		s1[u]+=s1[adj[u][i][0]];
	}
	return s2;
}

void dfs2(ll s2, int u=0, int p=-1) {
	for(int i=0; i<d[u]; ++i)
		if(adj[u][i][0]!=p&&s1[adj[u][i][0]]*2>n)
			dfs2(s2+(ll)(n-2*s1[adj[u][i][0]])*adj[u][i][1], adj[u][i][0], u);
	cout << s2;
	exit(0);
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n;
	vector<array<int, 2>> ps;
	for(int i=0; i<n; ++i) {
		cin >> ri >> ci;
		ps.push_back({ri, ci});
	}
	bld(ps);
	dfs2(dfs1());
}
