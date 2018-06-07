/*
	- bs = BCC size, ss = subtree size
	- Create BCC tree
		- Note that a node can be part of different BCCs
		- It is a bipartite tree, where every other node represents a BCC
	- Case 1: s, c, and f are in the same BCC
		- Iterate through all BCCs and add bs*(bs-1)*(bs-2)
	- Case 2: 2 of s, c, and f are in the same BCC
		- Those 2 can't be s & f, WLOG those 2 are s & c
		- Choose a node outside for f ((n-bs) ways)
		- Choose a node in BCC as s ((bs-1) ways as you can't choose the articulation point that separates c and f)
		- Choose a node in BCC as c ((bs-1) nodes left)
		- Subtract overcounted triples where c & f are in the same BCC
	- Case 3: All 3 are in different BCCs
		- Calculated in dfs3
		- Basically iterating through all c and adding (number of s)*(number of f) to ans
		- Be careful to not count paths where 2 nodes are in the same BCC
		- Path type 1
			- For each BCC node, count this for its children (not for its parent to avoid overcounting, as the grandparent will count the parent)
			- A normal path on the BCC tree that goes through the child and the BCC node
		- Path type 2
			- Count this for each BCC node
			- (1)-[BCC]-(2)-[BCC]-(3)-[BCC]-(4)-[BCC]-(5)-[BCC]-(6)
			                            |
			                           (7)
			- 1->7->6 is not a path on the BCC tree but it is a path in the original graph
		- Path type 3
			- Count this for each non-BCC node
			- A normal path on the BCC tree that goes through a node but not its BCC parent, so it wasn't counted as path type 1
*/

#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pii pair<int, int>
#define fi first
#define se second

const int mxN=1e5;
int n, m, dt=1, tin[mxN], low[mxN], sth, bccI, rt[2*mxN];
pii st[2*mxN];
ll sz1[2*mxN], sz2[mxN], ans;
vector<int> adj1[mxN], adj2[2*mxN];
set<int> bccs[mxN];
bool vis[2*mxN];

void dfs1(int u, int p) {
	tin[u]=low[u]=dt++;
	for(int v : adj1[u]) {
		if(!tin[v]) {
			int lsth=sth;
			st[sth++]={u, v};
			dfs1(v, u);
			low[u]=min(low[v], low[u]);
			if(low[v]>=tin[u]) {
				while(sth>lsth) {
					--sth;
					bccs[bccI].insert(st[sth].fi);
					bccs[bccI].insert(st[sth].se);
				}
				++bccI;
			}
		} else if(v!=p)
			low[u]=min(tin[v], low[u]);
	}
}

void dfs2(int u, int p) {
	sz1[u]=u<n;
	for(int v : adj2[u]) {
		if(v==p)
			continue;
		rt[v]=rt[u];
		dfs2(v, u);
		sz1[u]+=sz1[v];
	}
}

void dfs3(int u, int p) {
	vis[u]=1;
	ll n2=sz1[rt[u]]-adj2[u].size();
	for(int v : adj2[u]) {
		if(v==p)
			continue;
		dfs3(v, u);
		n2-=sz1[v]-1;
		if(u>=n)
			ans+=2*(sz1[v]-sz2[v]+adj2[u].size()-2)*(sz1[rt[u]]-adj2[u].size()-sz1[v]+1)+2*(adj2[u].size()-2)*(sz1[v]-1)*n2;
	}
	if(u<n) {
		n2=sz1[u]-sz2[u]+adj2[p].size()-2;
		for(int v : adj2[u]) {
			if(v==p)
				continue;
			n2-=sz1[v]-adj2[v].size()+1;
			ans+=2*(sz1[v]-adj2[v].size()+1)*n2;
		}
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> m;
	while(m--) {
		int u, v;
		cin >> u >> v, --u, --v;
		adj1[u].push_back(v);
		adj1[v].push_back(u);
	}
	for(int i=0; i<n; ++i)
		if(!tin[i])
			dfs1(i, -1);
	for(int i=0; i<bccI; ++i) {
		for(int j : bccs[i]) {
			adj2[j].push_back(i+n);
			adj2[i+n].push_back(j);
			sz2[j]+=bccs[i].size()-1;
		}
	}
	for(int i=0; i<bccI; ++i) {
		ll bs=bccs[i].size();
		if(!rt[i+n]) {
			rt[i+n]=i+n;
			dfs2(i+n, -1);
		}
		ans+=bs*(bs-1)*(bs-2)+2*(bs-1)*(bs-1)*(sz1[rt[i+n]]-bs)+bs*(bs-1)*(bs-1);
	}
	for(int i=0; i<n; ++i)
		ans-=sz2[i]*sz2[i];
	for(int i=0; i<bccI; ++i)
		if(!vis[i+n])
			dfs3(i+n, -1);
	cout << ans;
}
