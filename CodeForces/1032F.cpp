#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int mxN=3e5, M=998244353;
int n, ui, vi;
vector<int> adj[mxN];
ll dp[mxN][3];

void dfs(int u=0, int p=-1) {
	for(int i=0; i<adj[u].size()-1; ++i) {
		if(adj[u][i]==p)
			swap(adj[u][i], adj[u].back());
		dfs(adj[u][i], u);
	}
	adj[u].pop_back();
	vector<ll> pp, sp;
	pp.push_back(1);
	for(int i=0; i<adj[u].size(); ++i)
		pp.push_back(pp.back()*(2*dp[adj[u][i]][1]+dp[adj[u][i]][2])%M);
	sp.push_back(1);
	for(int i=(int)adj[u].size()-1; i>=0; --i)
		sp.push_back(sp.back()*(2*dp[adj[u][i]][1]+dp[adj[u][i]][2])%M);
	reverse(sp.begin(), sp.end());
	dp[u][0]=pp.back();
	for(int i=0; i<adj[u].size(); ++i)
		dp[u][1]=(dp[u][1]+pp[i]*sp[i+1]%M*dp[adj[u][i]][0])%M;
	dp[u][2]=1;
	for(int i=0; i<adj[u].size(); ++i)
		dp[u][2]=dp[u][2]*(dp[adj[u][i]][1]+dp[adj[u][i]][2])%M;
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
	adj[0].push_back(-1);
	dfs();
	cout << (dp[0][1]+dp[0][2])%M;
}
