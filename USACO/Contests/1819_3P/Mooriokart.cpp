#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int mxN=1500, mxA=2500, M=1e9+7;
int n, m, x, y, c1[mxA+1], c2[mxA+1], a;
vector<array<int, 2>> adj[mxN];
vector<int> tn;
bool vis[mxN];
ll dp1[2][mxA+1], dp2[2][mxA+1], ans;

void dfs(int u, bool b=0, int d=0) {
	vis[u]=1;
	if(b)
		tn.push_back(u);
	++c1[min(d, y)];
	c2[min(d, y)]=(c2[min(d, y)]+d)%M;
	for(array<int, 2> v : adj[u])
		if(!vis[v[0]])
			dfs(v[0], b, d+v[1]);
}

int main() {
	ifstream cin("mooriokart.in");
	ofstream cout("mooriokart.out");

	cin >> n >> m >> x >> y, y=max(y-(n-m)*x, 0);
	for(int i=0, u, v, w; i<m; ++i) {
		cin >> u >> v >> w, --u, --v;
		adj[u].push_back({v, w});
		adj[v].push_back({u, w});
	}
	dp1[0][0]=1;
	for(int i=0; i<n; ++i) {
		if(vis[i])
			continue;
		tn.clear();
		dfs(i, 1);
		for(int i=1; i<tn.size(); ++i) {
			for(int ti : tn)
				vis[ti]=0;
			dfs(tn[i]);
		}
		c1[0]-=tn.size();
		for(int j=0; j<=y; ++j) {
			if(!c1[j])
				continue;
			for(int k=0; k<=y; ++k) {
				int k2=min(k+j, y);
				dp1[a^1][k2]=(dp1[a^1][k2]+dp1[a][k]*c1[j])%M;
				dp2[a^1][k2]=(dp2[a^1][k2]+c1[j]*dp2[a][k]+c2[j]*dp1[a][k])%M;
			}
		}
		memset(c1, 0, sizeof(c1));
		memset(c2, 0, sizeof(c2));
		memset(dp1[a], 0, sizeof(dp1[0]));
		memset(dp2[a], 0, sizeof(dp2[0]));
		a^=1;
	}
	ans=(dp2[a][y]+dp1[a][y]*x*(n-m))%M*500000004%M;
	for(int i=1; i<n-m; ++i)
		ans=ans*i%M;
	cout << ans;
}
