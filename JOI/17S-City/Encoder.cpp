/*
	- Let S be the set of all subtrees with sizes < 2^8 which are not contained by other subtrees
	- If a node has multiple children in S, we also try to merge the subtrees, as long as the sizes of the final subtrees < 2^8
	- S has < around 2^11 subtrees
		- If a node has multiple children such that no pair is mergeable, it means that the average size of those children >= 2^8/2
		- At most n/(2^8/2) of those subtrees
	- We basically get 28 bits, we actually only need 27
	- 1 bit to identify if a node is in S
	- S nodes
		- 11 bits for the ID of the subtree
		- 15 bits for the range of nodes covered
	- Other nodes
		- 5 bits for the depth
		- 21 bits for the range of subtrees covered in S
	- In general, log_2(16dn^4)/3 bits are required
	- Actually, 2 weeks later, I found that this solution is actually wrong (S can have like d*2^11 subtrees)
	- But the limit on d makes this work well, and this solution is guaranteed to work with 32 bits (or even 31)
*/

#include "Encoder.h"
#include <bits/stdc++.h>
using namespace std;

const int mxN=2.5e5, B=1<<8;
vector<int> adj[mxN];
int s[mxN], dt1, dt2;

int encrange(int a, int b) {
	return b*(b-1)/2+a;
}

void dfs2(int u) {
	int ds=dt2++;
	for(int v : adj[u])
		dfs2(v);
	Code(u, 1<<26|dt1<<15|encrange(ds, dt2));
}

void dfs1(int u=0, int p=-1, int d=0) {
	int ds=dt1;
	s[u]=1;
	if(~p)
		adj[u].erase(find(adj[u].begin(), adj[u].end(), p));
	for(int v : adj[u]) {
		dfs1(v, u, d+1);
		s[u]+=s[v];
	}
	if(u&&s[u]<B)
		return;
	sort(adj[u].begin(), adj[u].end(), [](const int &a, const int &b) {
		return s[a]<s[b];
	});
	for(int i=0, cs; i<adj[u].size()&&s[adj[u][i]]<B; ++dt1) {
		dt2=0, cs=0;
		while(i<adj[u].size()&&cs+s[adj[u][i]]<B) {
			cs+=s[adj[u][i]];
			dfs2(adj[u][i++]);
		}
	}
	Code(u, d<<21|encrange(ds, dt1));
}

void Encode(int n, int a[], int b[]) {
	for(int i=0; i<n-1; ++i) {
		adj[a[i]].push_back(b[i]);
		adj[b[i]].push_back(a[i]);
	}
	dfs1();
}
