/*
	- Do centroid decomposition, for a certain centroid c, update the answers according to the paths that pass through c
	- Calculate the latest possible time to start from c and reach all other nodes in the centroid subtree (lt[u])
		- dp[u][t] = latest possible time to start from c and still reach u not after time t
		- lt[u] = dp[u][m]
		- Calculate this dp from parents to children
		- dp[v][t] = dp[u][t] if there is an edge at time t and dp[v][t-1] if there isn't
		- Updated efficiently with persistent segment trees
	- Calculate for each time t, how many nodes in the centroid subtree can reach c not after t (nr[t])
		- dp[u][t] = how many nodes in u's subtree can reach u not after time t
		- nr[t]=dp[c][t]
		- Calculate this dp from children to parent
		- For each child v, calculate dp[v->u][t] = how many nodes in v's subtree can reach u not after time t
			- dp[v->u][t] = dp[v][t] if there is an edge at time t and dp[v->u][t-1] if there isn't
			- Updated efficiently with segment trees
		- dp[u][t] = 1 + sum(i=1...n, dp[vi->u][t])
		- Updated efficiently with mergeable segment trees
	- For each node u in the centroid subtree, add nr[lt[u]] to ans[u]
		- Remember to subtract paths that don't actually go through c
	- Try to optimize memory limit by not using too many segment tree operations
	- O(nlog^2n) time and O(nlogn) memory
*/

#include <bits/stdc++.h>
using namespace std;

#define pii pair<int, int>
#define fi first
#define se second

const int mxN=1e5, mxM=2e5;
int n, m, q, x[mxN-1], y[mxN-1], lb[mxN-1], ans[mxN], centP[mxN], sz[mxN], rt1, sts=2, bsts, sti[mxN], mlt[mxN], dj, ck;
vector<pii> av[mxN-1];
vector<int> adj[mxN], cn;

struct node {
	bool lz1;
	int lz2, v, lc, rc;
} st[2*18*(2*mxN+mxM/2)+2*mxM]; //2 nodes per layer * logn=18 layers * total updates + max nodes in a segtree

inline void psh(int &sti, int v=0, bool x1=0, int x2=0) {
	if(!sti||st[sti].v!=v) {
		st[sts]=st[sti];
		st[sts].v=v;
		sti=sts++;
	}
	if(x1)
		st[sti].lz1=1, st[sti].lz2=0;
	st[sti].lz2+=x2;
}

void upd(int sti, int l1, int r1, int x, int v=0, int l2=0, int r2=m) {
	if(l1>r1)
		return;
	if(l1<=l2&&r2<=r1) {
		st[sti].lz1=1, st[sti].lz2=x;
		return;
	}
	psh(st[sti].lc, v, st[sti].lz1, st[sti].lz2);
	psh(st[sti].rc, v, st[sti].lz1, st[sti].lz2);
	st[sti].lz1=st[sti].lz2=0;
	int m2=(l2+r2)/2;
	if(l1<=m2)
		upd(st[sti].lc, l1, r1, x, v, l2, m2);
	if(m2<r1)
		upd(st[sti].rc, l1, r1, x, v, m2+1, r2);
}

int qry(int sti, int l1, int l2=0, int r2=m) {
	if(!sti)
		return 0;
	if(st[sti].lz1)
		return st[sti].lz2;
	int m2=(l2+r2)/2;
	return st[sti].lz2+(l1<=m2?qry(st[sti].lc, l1, l2, m2):qry(st[sti].rc, l1, m2+1, r2));
}

void mrg(int &sti1, int sti2) {
	if(!sti1||!sti2) {
		sti1^=sti2;
		return;
	}
	st[sti1].lz2+=st[sti2].lz2;
	if(st[sti2].lz1)
		return;
	if(st[sti1].lz1) {
		st[sti1].lz1=0;
		st[sti1].lc=st[sti2].lc, st[sti1].rc=st[sti2].rc;
		return;
	}
	mrg(st[sti1].lc, st[sti2].lc);
	mrg(st[sti1].rc, st[sti2].rc);
}

inline void clst() {
	while(sts>bsts)
		st[--sts]={};
	for(int cni : cn)
		sti[cni]=0;
}

void dfs1(int u, int p) {
	sz[u]=1;
	for(int e : adj[u]) {
		int v=u^x[e]^y[e];
		if(v==p||centP[v]!=-1)
			continue;
		dfs1(v, u);
		sz[u]+=sz[v];
	}
}

int dfs2(int u, int p, int szr) {
	for(int e : adj[u]) {
		int v=u^x[e]^y[e];
		if(v!=p&&centP[v]==-1&&sz[v]>szr/2)
			return dfs2(v, u, szr);
	}
	return u;
}

void dfs3(int u, int p) {
	cn.push_back(u);
	mlt[u]=qry(sti[u], m);
	for(int e : adj[u]) {
		int v=u^x[e]^y[e];
		if(v==p||centP[v]!=-1)
			continue;
		sti[v]=sti[u];
		psh(sti[v], v);
		for(int i=0; i<av[e].size()-1; ++i)
			upd(sti[v], av[e][i].se+1, av[e][i+1].fi-1, qry(sti[v], av[e][i].se), v);
		dfs3(v, u);
	}
}

void dfs5(int u, int p) {
	ans[u]-=qry(sti[rt1], mlt[u]);
	for(int e : adj[u]) {
		int v=u^x[e]^y[e];
		if(v!=p&&centP[v]==-1)
			dfs5(v, u);
	}
}

void dfs4(int u, int p) {
	psh(sti[u]);
	upd(sti[u], 1, m, 1);
	for(int e : adj[u]) {
		int v=u^x[e]^y[e];
		if(v==p||centP[v]!=-1)
			continue;
		dfs4(v, u);
		for(int i=0; i<av[e].size()-1; ++i)
			upd(sti[v], av[e][i].se+1, av[e][i+1].fi-1, qry(sti[v], av[e][i].se));
		if(p==-1) {
			rt1=v;
			dfs5(v, u);
		}
		mrg(sti[u], sti[v]);
	}
}

void cd(int u, int p) {
	int c=dfs2(u, -1, sz[u]);
	centP[c]=p;
	dfs1(c, -1);
	sti[c]=1;
	psh(sti[c], c);
	dfs3(c, -1);
	clst();
	dfs4(c, -1);
	for(int cni : cn)
		ans[cni]+=qry(sti[c], mlt[cni]);
	ans[c]+=!mlt[c];
	clst();
	cn.clear();
	for(int e : adj[c]) {
		int v=c^x[e]^y[e];
		if(centP[v]==-1)
			cd(v, c);
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> m >> q;
	for(int i=0; i<n-1; ++i) {
		cin >> x[i] >> y[i], --x[i], --y[i];
		adj[x[i]].push_back(i);
		adj[y[i]].push_back(i);
		av[i].push_back({0, 0});
	}
	for(int i=1; i<=m; ++i) {
		cin >> dj, --dj;
		if(lb[dj]) {
			av[dj].push_back({lb[dj], i-1});
			lb[dj]=0;
		} else
			lb[dj]=i;
	}
	for(int i=0; i<n-1; ++i)
		av[i].push_back({lb[i]?lb[i]:m+1, m+1});
	for(int i=0; i<=m; ++i)
		upd(1, i, i, i, -1);
	bsts=sts;
	memset(centP, -1, 4*n);
	dfs1(0, -1);
	cd(0, -2);
	while(q--) {
		cin >> ck, --ck;
		cout << ans[ck] << "\n";
	}
}
