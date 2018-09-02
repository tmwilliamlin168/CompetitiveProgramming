/*
	- Create a graph
		- Nodes are the containers
		- Edges between two nodes if the two containers intersect
	- Answer is 2^(number of connected components) if the graph is bipartite and 0 if the graph isn't
	- Use two segment trees to find the a container with the maximum r given a<=l<=b and a container with the minimum l given a<=r<=b
	- Use these two segment trees to efficiently find unvisited neighbors of a node during DFS
*/

#include <bits/stdc++.h>
using namespace std;

const int mxN=1e6, M=1e9+7;
int n, a[mxN], b[mxN], c[mxN], d[2*mxN], ans=1, st[2][mxN], sth[2];

struct segtree {
	array<int, 2> a[4*mxN];
	void bld() {
		for(int i=2*n-1; i; --i)
			a[i]=max(a[2*i], a[2*i+1]);
	}
	void upd(int i, array<int, 2> x) {
		for(a[i+=2*n]=x; i/=2; )
			a[i]=max(a[2*i], a[2*i+1]);
	}
	array<int, 2> qry(int l, int r) {
		array<int, 2> b={INT_MIN, -1};
		for(l+=2*n, r+=2*n; l<r; ++l/=2, r/=2) {
			if(l&1)
				b=max(a[l], b);
			if(r&1)
				b=max(a[r-1], b);
		}
		return b;
	}
} st1, st2;

void dfs(int u) {
	st1.upd(a[u], {-1, -1});
	st2.upd(b[u], {-2*n, -1});
	array<int, 2> v;
	while((v=st1.qry(a[u], b[u]))[1]!=-1) {
		if(v[0]<b[u])
			break;
		c[v[1]]=c[u]^1;
		dfs(v[1]);
	}
	while((v=st2.qry(a[u], b[u]))[1]!=-1) {
		if(-v[0]>a[u])
			break;
		c[v[1]]=c[u]^1;
		dfs(v[1]);
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n;
	for(int i=2*n; i<4*n; ++i) {
		st1.a[i]={-1, -1};
		st2.a[i]={-2*n, -1};
	}
	for(int i=0; i<n; ++i) {
		cin >> a[i] >> b[i], --a[i], --b[i];
		st1.a[a[i]+2*n]={b[i], i};
		st2.a[b[i]+2*n]={-a[i], i};
	}
	st1.bld();
	st2.bld();
	memset(c, -1, 4*n);
	for(int i=0; i<n; ++i) {
		if(c[i]==-1) {
			c[i]=0;
			dfs(i);
			ans=ans*2%M;
		}
	}
	memset(d, -1, 4*2*n);
	for(int i=0; i<n; ++i)
		d[a[i]]=d[b[i]]=i;
	for(int i=0; i<2*n; ++i) {
		if(sth[c[d[i]]]&&st[c[d[i]]][sth[c[d[i]]]-1]==d[i])
			--sth[c[d[i]]];
		else
			st[c[d[i]]][sth[c[d[i]]]++]=d[i];
	}
	cout << (!sth[0]&&!sth[1]?ans:0);
}
