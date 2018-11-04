#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int mxN=2e3, M=998244353;
int n, ui, vi, s[mxN];
vector<int> adj[mxN];
ll dp[mxN][mxN+1][3], ans;

ll modI(ll a, ll m) {
	return (a%=m)<=1?1:(1-modI(m%a, a)*m)/a+m;
}

void dfs(int u, int p=-1) {
	dp[u][0][0]=1;
	for(int v : adj[u]) {
		if(v==p)
			continue;
		dfs(v, u);
		for(int i=s[u]+=s[v]; i>=0; --i) {
			for(int j=max(i-s[u]+s[v], 0); j<=min(i, s[v]); ++j) {
				dp[u][i][1]=(dp[u][i][1]+dp[u][i-j][0]*dp[v][j][1])%M;
				if(j) {
					dp[u][i][0]=(dp[u][i][0]+dp[u][i-j][0]*dp[v][j][0])%M;
					dp[u][i][1]=(dp[u][i][1]+dp[u][i-j][1]*dp[v][j][0])%M;
					dp[u][i][2]=(dp[u][i][2]+dp[u][i-j][1]*dp[v][j-1][1]+dp[u][i-j][2]*dp[v][j][0])%M;
				}
			}
		}
	}
	for(int i=++s[u]; i; --i) {
		dp[u][i-1][1]=(dp[u][i-1][1]+dp[u][i-1][0])%M;
		dp[u][i][0]=(dp[u][i][0]+dp[u][i-1][1]+dp[u][i][2])%M;
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n;
	for(int i=0; i<n-1; ++i) {
		cin >> ui >> vi, --ui, --vi;
		adj[ui].push_back(vi);
		adj[vi].push_back(ui);
	}
	dfs(0);
	ll b=modI((ll)n*(n+1)/2, M), p=b;
	for(int i=1; i<=n; ++i, p=p*b%M*i%M)
		ans+=p*dp[0][i][0]%M;
	cout << ans%M;
}
