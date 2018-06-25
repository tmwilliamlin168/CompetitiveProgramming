/*
	- When querying, nodes in connected components must be in the same group or else the query will always return 1
	- Iterate through i and separate connected components into two groups of nodes A and B according to the ith bit of the component's ID
	- Once we find i such that query(A, B) returns 1, we know that the endpoints of the edge have the same bits below i
		- Fix one bit at a time and test if the edge is still there to find the exact bits
	- Since we found A and B such that query(A, B) returns 1, we can binary search for the exact edge
*/

#include <icc.h>
#include <bits/stdc++.h>
using namespace std;

const int mxN=100;
int cci;
bool vis[mxN];
vector<int> adj[mxN], ccs[mxN], qa[2];

void dfs(int u) {
	vis[u]=1;
	ccs[cci].push_back(u);
	for(int v : adj[u])
		if(!vis[v])
			dfs(v);
}

void run(int n) {
	for(int it=0; it<n-1; ++it) {
		for(int i=0; i<n; ++i) {
			if(!vis[i]) {
				dfs(i);
				++cci;
			}
		}
		for(int i=0; ; ++i) {
			qa[0].clear();
			qa[1].clear();
			for(int j=0; j<cci; ++j)
				for(int u : ccs[j])
					qa[j>>i&1].push_back(u+1);
			int qr=query(qa[0].size(), qa[1].size(), qa[0].data(), qa[1].data());
			if(!qr)
				continue;
			int cm=0;
			for(int k=0; k<i; ++k) {
				qa[0].clear();
				qa[1].clear();
				for(int j=0; j<cci; ++j)
					if((j&((1<<(k+1))-1))==cm)
						for(int u : ccs[j])
							qa[j>>i&1].push_back(u+1);
				qr=query(qa[0].size(), qa[1].size(), qa[0].data(), qa[1].data());
				if(!qr)
					cm|=1<<k;
			}
			qa[0].clear();
			qa[1].clear();
			for(int j=0; j<cci; ++j)
				if((j&((1<<i)-1))==cm)
					for(int u : ccs[j])
						qa[j>>i&1].push_back(u+1);
			for(int j=0; j<2; ++j) {
				while(qa[j].size()>1) {
					qr=query(qa[j].size()/2, qa[j^1].size(), qa[j].data(), qa[j^1].data());
					if(qr)
						qa[j].erase(qa[j].begin()+qa[j].size()/2, qa[j].end());
					else
						qa[j].erase(qa[j].begin(), qa[j].begin()+qa[j].size()/2);
				}
			}
			int u=qa[0][0], v=qa[1][0];
			setRoad(u, v);
			adj[u-1].push_back(v-1);
			adj[v-1].push_back(u-1);
			break;
		}
		memset(vis, 0, n);
		while(cci)
			ccs[--cci].clear();
	}
}
