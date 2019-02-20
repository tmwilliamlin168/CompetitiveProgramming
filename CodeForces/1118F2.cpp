#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int mxN=3e5, M=998244353;
int n, k, a[mxN], c[mxN+1];
vector<int> adj[mxN];
ll ans=1, dp[mxN][2];
array<int, 2> b[mxN];

void dfs(int u=0, int p=-1) {
	for(int v : adj[u])
		if(v!=p)
			dfs(v, u);
	b[u][0]=a[u];
	if(a[u])
		b[u][1]=1;
	for(int v : adj[u]) {
		if(v==p||!b[v][0])
			continue;
		if(b[u][0]&&b[u][0]!=b[v][0])
			ans=0;
		b[u][0]=b[v][0];
		b[u][1]+=b[v][1];
	}
	if(b[u][0]) {
		dp[u][0]=1;
		for(int v : adj[u]) {
			if(v==p)
				continue;
			dp[u][0]=dp[u][0]*dp[v][!b[v][0]]%M;
		}
	} else {
		dp[u][1]=1;
		vector<ll> pd{1}, sd;
		for(int v : adj[u]) {
			if(v!=p) {
				dp[u][1]=dp[u][1]*dp[v][1]%M;
				pd.push_back(dp[v][1]);
				sd.push_back(dp[v][1]);
			} else {
				pd.push_back(1);
				sd.push_back(1);
			}
		}
		sd.push_back(1);
		for(int i=1; i<pd.size(); ++i)
			pd[i]=pd[i-1]*pd[i]%M;
		for(int i=sd.size()-2; i>=0; --i)
			sd[i]=sd[i+1]*sd[i]%M;
		for(int i=0; i<adj[u].size(); ++i) {
			if(adj[u][i]==p)
				continue;
			dp[u][0]=(dp[u][0]+pd[i]*sd[i+1]%M*dp[adj[u][i]][0])%M;
		}
	}
	if(!b[u][0]||c[b[u][0]]==b[u][1]) {
		dp[u][1]=(dp[u][1]+dp[u][0])%M;
		b[u]={};
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> n >> k;
	for(int i=0; i<n; ++i) {
		cin >> a[i];
		++c[a[i]];
	}
	for(int i=1, u, v; i<n; ++i) {
		cin >> u >> v, --u, --v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	dfs();
	cout << ans*dp[0][0];
}
