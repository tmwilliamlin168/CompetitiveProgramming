#include "bits/stdc++.h"
using namespace std;

#define ll long long

const int mxN=1e5, mxK=200, M=1e9+7;
int n, k, s[mxN], ui, vi;
vector<int> adj[mxN];
ll p2[mxN+1], dp[mxN][mxK+1], ans, td[mxK+1], pa[mxK+1][mxK+1];

void dfs1(int u=0, int p=-1) {
	s[u]=1;
	dp[u][0]=2;
	for(int v : adj[u]) {
		if(v==p)
			continue;
		dfs1(v, u);
		memcpy(td, dp[u], 8*(min(s[u], k)+1));
		memset(dp[u], 0, 8*(min(s[u], k)+1));
		for(int i=0; i<=min(s[u], k); ++i) {
			for(int j=0; j<=min(s[v], k-i); ++j) {
				dp[u][i+j]=(dp[u][i+j]+td[i]*dp[v][j])%M;
				if(i&&j)
					ans=(ans+p2[n-s[u]-s[v]]*td[i]%M*dp[v][j]%M*pa[k][i+j])%M;
			}
		}
		s[u]+=s[v];
	}
	if(p!=-1) {
		ll ta=p2[s[u]]-1;
		for(int i=1; i<=min(s[u], k-1); ++i)
			ta=(ta+dp[u][i]*pa[k][i+1])%M;
		ans=(ans+ta*(p2[n-s[u]]-1))%M;
		for(int i=min(s[u], k); i>=2; --i)
			dp[u][i]=(dp[u][i]+dp[u][i-1])%M;
		dp[u][1]=(dp[u][1]+p2[s[u]]-1)%M;
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> n >> k;
	for(int i=0; i<n-1; ++i) {
		cin >> ui >> vi, --ui, --vi;
		adj[ui].push_back(vi);
		adj[vi].push_back(ui);
	}
	p2[0]=1;
	for(int i=1; i<=n; ++i)
		p2[i]=p2[i-1]*2%M;
	pa[0][0]=1;
	for(int i=1; i<=k; ++i)
		for(int j=1; j<=i; ++j)
			pa[i][j]=(pa[i-1][j-1]+pa[i-1][j])*j%M;
	dfs1();
	cout << ans;
}
