#include <bits/stdc++.h>
using namespace std;

const int mxN=3e5;
int n, m, ui, vi, dp[mxN+2], pi[mxN+2], sp[mxN+2], a1[mxN+2], a2;
vector<int> adj[mxN+2], adj2[mxN+2], lp, vv;
bool vis[mxN+2];

int cdp(int u) {
	if(!dp[u]) {
		for(int v : adj[u])
			dp[u]=max(cdp(v), dp[u]);
		++dp[u];
	}
	return dp[u];
}

int dfs(int u, vector<int> adj[mxN+2]) {
	int s=1;
	vis[u]=1;
	vv.push_back(u);
	for(int v : adj[u])
		if(!vis[v])
			s+=dfs(v, adj);
	return s;
}

void cr(vector<int> adj[mxN+2]) {
	int ca=0;
	for(int i=0; i<lp.size(); ++i) {
		if(sp[i]) {
			int aa=dfs(sp[i], adj);
			a1[sp[i]]+=ca+aa;
			for(int j=0; j<aa; ++j)
				vis[vv[vv.size()-1-j]]=0;
		}
		ca+=dfs(lp[i], adj);
		a1[lp[i]]+=ca;
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> m;
	while(m--) {
		cin >> ui >> vi;
		adj[ui].push_back(vi);
		adj2[vi].push_back(ui);
	}
	for(int i=1; i<=n; ++i) {
		adj[0].push_back(i);
		adj2[i].push_back(0);
		adj[i].push_back(n+1);
		adj2[n+1].push_back(i);
	}
	cdp(0);
	for(int u=0; ; ) {
		lp.push_back(u);
		pi[u]=lp.size();
		if(dp[u]<=1)
			break;
		for(int v : adj[u]) {
			if(dp[v]>=dp[u]-1) {
				u=v;
				break;
			}
		}
	}
	for(int i=1; i<=n; ++i) {
		if(pi[i])
			continue;
		int m1=0, m2=n+3;
		for(int j : adj[i])
			if(pi[j])
				m2=min(pi[j], m2);
		for(int j : adj2[i])
			m1=max(pi[j], m1);
		if(m1+2==m2)
			sp[m1]=i;
	}
	cr(adj2);
	memset(vis, 0, n+2);
	reverse(lp.begin(), lp.end());
	for(int i=0; i<lp.size()-1-i; ++i)
		swap(sp[i], sp[lp.size()-1-i]);
	cr(adj);
	for(int i=1; i<=n; ++i)
		a2+=a1[i]==n+2||a1[i]==n+3;
	cout << a2;
}
