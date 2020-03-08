#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int mxN=1e3, M=1e9+7;
int n;
ll dp[mxN][8], ndp[8];
vector<int> adj[mxN];

void ad(ll &a, ll b) {
	a+=b;
	if(a>=M)
		a-=M;
}

class RestrictedLeaves {
public:
	void dfs(int u=0) {
		if(adj[u].size()) {
			dfs(adj[u][0]);
			for(int i=0; i<8; ++i) {
				ad(dp[u][i&3], dp[adj[u][0]][i]);
				if(i<4)
					ad(dp[u][4|i], dp[adj[u][0]][i]);
			}
			adj[u].erase(adj[u].begin());
			for(int v : adj[u]) {
				dfs(v);
				memset(ndp, 0, sizeof(ndp));
				for(int i=0; i<8; ++i)
					for(int j=0; j<8; ++j)
						if(!(i&4&&j&4)&&!(i&1&&j&2))
							ad(ndp[(i&4)|(i&2)|(j&1)], dp[u][i]*dp[v][j]%M);
				memcpy(dp[u], ndp, sizeof(dp[0]));
			}
		} else
			dp[u][0]=dp[u][7]=1;
	}
	int count(vector<int> p) {
		n=p.size();
		for(int i=0; i<n; ++i)
			adj[i].clear();
		for(int i=1; i<n; ++i)
			adj[p[i]].push_back(i);
		dfs();
		return (dp[0][0]+dp[0][1]+dp[0][2]+dp[0][4]+dp[0][5]+dp[0][6])%M;
	}
};
