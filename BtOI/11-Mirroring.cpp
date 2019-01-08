/*
	- If the graph is just a line, check that n is odd
	- If the graph is just one cycle, check that n is even
	- Otherwise, we can also prove that there exists a cycle with exactly 2 nodes with degree > 2 if the answer is yes
	- We can use those 2 nodes and the symmetry of cycles to find 2 leaves on the cycle
	- We can find this cycle by doing dfs from each node with degree > 2, only passing through nodes with degree = 2, and finding which nodes can be reached
	- We then run bfs from one of the leaves
	- Other leaves are nodes that are checked twice with same distance during the bfs
	- The leaves should have degrees of exactly 2, not be connected to other leaves, and divide the graph into 2 disjoint trees
	- Fix roots on both sides (take a leaf's 2 neighbors) and calculate parents for each node
	- For each leaf, try to pair up the 2 neighbors
	- Pairing up nodes can be done recursively, in which we pair up the nodes' parents first
	- At most 2 nodes with degree 1 from different trees, we also need to try pairing them
*/

#include <bits/stdc++.h>
using namespace std;

const int mxN=1e5;
int n, m, ui, vi, cl=-1, qu[mxN], qt, d[mxN], v[mxN], p[mxN], b[mxN];
vector<int> adj[mxN];
bool lf[mxN], dg2;

void fk() {
	cout << "NO";
	exit(0);
}

array<int, 2> dfs1(int u, int p, int d=1) {
	if(adj[u].size()!=2)
		return {u, d};
	for(int v : adj[u])
		if(v!=p)
			return dfs1(v, u, d+1);
}

int dfs2(int u, int p, int d) {
	if(!d)
		return u;
	for(int v : adj[u])
		if(v!=p)
			return dfs2(v, u, d-1);
}

void dfs3(int u, int pu) {
	++v[u];
	if(lf[u])
		return;
	if(v[u]>1)
		fk();
	p[u]=pu;
	for(int v : adj[u])
		if(v!=pu)
			dfs3(v, u);
}

void tp(int u, int v) {
	if(u==cl&&v==cl)
		return;
	if(u==v||b[u]!=-1&&b[u]!=v||b[v]!=-1&&b[v]!=u)
		fk();
	if(b[u]==-1) {
		tp(p[u], p[v]);
		b[u]=v;
		b[v]=u;
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> n >> m;
	for(int i=0; i<m; ++i) {
		cin >> ui >> vi, --ui, --vi;
		adj[ui].push_back(vi);
		adj[vi].push_back(ui);
	}
	for(int i=0; i<n; ++i) {
		if(adj[i].size()<3)
			continue;
		dg2=1;
		set<int> s;
		for(int j : adj[i]) {
			array<int, 2> a=dfs1(j, i);
			if(a[0]==i)
				fk();
			if(s.find(a[0])!=s.end()) {
				if(a[1]%2)
					fk();
				cl=dfs2(j, i, a[1]/2-1);
			}
			s.insert(a[0]);
		}
	}
	if(!dg2) {
		cout << (n&1^(m<n)?"NO":"YES");
		return 0;
	}
	if(cl==-1)
		fk();
	lf[cl]=1;
	qu[qt++]=cl;
	memset(d, 0x3f, 4*n);
	d[cl]=0;
	for(int qh=0; qh<n; ++qh) {
		int u=qu[qh];
		for(int v : adj[u]) {
			if(d[v]>d[u]+1) {
				d[v]=d[u]+1;
				qu[qt++]=v;
			} else if(d[v]==d[u]+1)
				lf[v]=1;
		}
	}
	for(int i=0; i<n; ++i)
		if(lf[i]&&adj[i].size()!=2)
			fk();
	dfs3(adj[cl][0], cl);
	for(int i=0; i<n; ++i)
		if(i!=cl&&lf[i]&&v[i]!=1)
			fk();
	dfs3(adj[cl][1], cl);
	for(int i=0; i<n; ++i)
		if(i!=cl&&lf[i]&&v[i]!=2)
			fk();
	memset(b, -1, 4*n);
	for(int i=0; i<n; ++i)
		if(lf[i])
			tp(adj[i][0], adj[i][1]);
	vector<int> up;
	for(int i=0; i<n; ++i)
		if(!lf[i]&&b[i]==-1&&adj[i].size()==1)
			up.push_back(i);
	if(up.size()==2) {
		tp(up[0], up[1]);
		up.clear();
	}
	if(up.size())
		fk();
	cout << "YES";
}
