/*
	- A perfect matching can be changed into another perfect matching by flipping an alternating cycle
	- Notice that you won't need to flip an edge more than once to get from a perfect matching to another perfect matching
		- If we do, two cycles that flip that edge can be "merged" into a cycle that doesn't flip that edge
	- Use recursion to iterate through edges from the start and fix their states
		- Note that when you try to flip edge i, the obtained cycle shouldn't contain any edges with index < i
	- Theoretically O(n*m*k) but much faster in practice
*/

#include <bits/stdc++.h>
using namespace std;

const int mxN=100, mxM=600;
int n, m, k, a[mxM], b[mxM], rm[mxN], lm[mxN];
vector<int> adj[mxN];
bool vis1[mxN], used[mxM];

bool dfs1(int u) {
	vis1[u]=1;
	for(int e : adj[u]) {
		int v=b[e];
		if(lm[v]==-1||!vis1[a[lm[v]]]&&dfs1(a[lm[v]])) {
			used[e]^=1;
			if(lm[v]!=-1)
				used[lm[v]]^=1;
			rm[u]=e;
			lm[v]=e;
			return 1;
		}
	}
	return 0;
}

bool dfs3(int u, int t, int mei) {
	vis1[u]=1;
	for(int e : adj[u]) {
		int v=b[e];
		if(e<mei||lm[v]<mei||used[e])
			continue;
		if(v==t||!vis1[a[lm[v]]]&&dfs3(a[lm[v]], t, mei)) {
			used[e]^=1;
			used[lm[v]]^=1;
			rm[u]=e;
			lm[v]=e;
			return 1;
		}
	}
	return 0;
}

void dfs2(int si) {
	--k;
	if(k<0) {
		cout << "Yes";
		exit(0);
	}
	for(int i=m-1; i>=si; --i) {
		if(lm[b[i]]<i||rm[a[i]]<i)
			continue;
		memset(vis1, 0, n);
		int s=lm[b[i]], t=rm[a[i]];
		if(dfs3(a[s], b[t], i)) {
			used[i]^=1;
			used[s]^=1;
			if(used[i]) {
				rm[a[i]]=i;
				lm[b[i]]=i;
			}
			dfs2(i+1);
		}
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> m >> k;
	for(int i=0; i<m; ++i) {
		cin >> a[i] >> b[i], --a[i], b[i]-=n+1;
		adj[a[i]].push_back(i);
	}
	memset(lm, -1, 4*n);
	int cm=0;
	for(int i=0; i<n; ++i) {
		memset(vis1, 0, n);
		if(dfs1(i))
			++cm;
	}
	if(cm<n) {
		cout << "No";
		return 0;
	}
	dfs2(0);
	cout << "No";
}
