#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int mxN=1e5, mxM=300, M=1e9+7;
int n, q, dt;
vector<int> adj[mxN], oc[mxN];
array<int, 2> is[mxN];
ll dp[2][mxM+1];

void dfs(int u, int p=-1) {
	oc[u].push_back(dt++);
	for(int v : adj[u]) {
		if(v==p)
			continue;
		dfs(v, u);
		oc[u].push_back(dt++);
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> n >> q;
	for(int i=1, u, v; i<n; ++i) {
		cin >> u >> v, --u, --v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	dfs(0);
	oc[0].pop_back();
	for(int i=0; i<n; ++i)
		for(int j=0; oc[i][j]<2*n-2; ++j)
			oc[i].push_back(oc[i][j]+2*n-2);
	for(int k, m, r; q--; ) {
		cin >> k >> m >> r, --r;
		for(int i=0, u; i<k; ++i) {
			cin >> u, --u;
			is[i]={*lower_bound(oc[u].begin(), oc[u].end(), oc[r][0]), *--upper_bound(oc[u].begin(), oc[u].end(), oc[r][0]+2*n-2)};
		}
		sort(is, is+k);
		priority_queue<int, vector<int>, greater<int>> pq;
		memset(dp, 0, 8*(m+1));
		dp[0][0]=1;
		for(int i=0; i<k; ++i) {
			while(pq.size()&&pq.top()<is[i][0])
				pq.pop();
			dp[i&1^1][0]=0;
			for(int j=1; j<=m; ++j)
				dp[i&1^1][j]=(dp[i&1][j-1]+dp[i&1][j]*max(j-(int)pq.size(), 0))%M;
			pq.push(is[i][1]);
		}
		ll ans=0;
		for(int i=1; i<=m; ++i)
			ans+=dp[k&1][i];
		cout << ans%M << "\n";
	}
}
