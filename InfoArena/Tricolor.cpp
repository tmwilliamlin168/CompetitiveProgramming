#include <bits/stdc++.h>
using namespace std;

const int mxN=5e3;
int t, n, dp[mxN][mxN], td[mxN], ui, vi;
vector<int> adj[mxN];

int dfs(int u=0, int p=-1) {
	int ts=0, aa=0;
	dp[u][0]=0;
	for(int v : adj[u]) {
		if(v==p)
			continue;
		int cs=dfs(v, u), ab=0;
		memset(td, 0xc0, 4*(ts+cs+1));
		for(int i=0; i<=ts; ++i)
			for(int j=0; j<=cs; ++j)
				td[i+j]=max(dp[u][i]+dp[v][j]+i*j, td[i+j]);
		ts+=cs;
		memcpy(dp[u], td, 4*(ts+1));
		for(int j=0; j<=cs; ++j)
			ab=max(dp[v][j]+j, ab);
		aa+=ab;
	}
	dp[u][1]=max(aa, dp[u][1]);
	adj[u].clear();
	return ts+1;
}

int main() {
	ifstream cin("tricolor.in");
	ofstream cout("tricolor.out");
 
	cin >> t;
	while(t--) {
		cin >> n;
		for(int i=0; i<n-1; ++i) {
			cin >> ui >> vi, --ui, --vi;
			adj[ui].push_back(vi);
			adj[vi].push_back(ui);
		}
		memset(dp, 0xc0, n*sizeof(dp[0]));
		dfs();
		int ans=0;
		for(int i=1; i<n; ++i)
			ans=max(dp[0][i], ans);
		cout << ans << "\n";
	}
}
