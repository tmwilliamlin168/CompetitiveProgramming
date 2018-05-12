/*
	- http://codeforces.com/blog/entry/11543?#comment-168169
*/

#include <bits/stdc++.h>
using namespace std;

#define pii pair<int, int>
#define fi first
#define se second

const int mxN=2e5;
int n, dp[mxN][4];
vector<pii> adj[mxN];

void dfs1(int u, int p, int a) {
	int m1=0, m2=0, m3=0, mi1=-1, mi2, mi3=-1, mi4;
	for(pii e : adj[u]) {
		int v=e.fi;
		if(v==p)
			continue;
		dfs1(v, u, e.se);
		dp[u][0]+=dp[v][0];
		m1=max(dp[v][2]-dp[v][0]+a, m1);
		m2=max(dp[v][1]-dp[v][0], m2);
		m3=max(dp[v][3]-dp[v][0]+a, m3);
		if(mi1==-1||dp[v][2]-dp[v][0]>dp[mi1][2]-dp[mi1][0]) {
			mi2=mi1;
			mi1=v;
		} else if(mi2==-1||dp[v][2]-dp[v][0]>dp[mi2][2]-dp[mi2][0])
			mi2=v;
		if(mi3==-1||dp[v][3]-dp[v][0]>dp[mi3][3]-dp[mi3][0]) {
			mi4=mi3;
			mi3=v;
		} else if(mi4==-1||dp[v][3]-dp[v][0]>dp[mi4][3]-dp[mi4][0])
			mi4=v;
	}
	dp[u][2]=dp[u][0]+a;
	dp[u][1]=dp[u][0]+m2;
	if(mi1!=-1&&mi3!=-1)
		dp[u][1]=max(dp[u][0]+(mi1!=mi3?dp[mi1][2]-dp[mi1][0]+dp[mi3][3]-dp[mi3][0]:max(mi2==-1?0:dp[mi2][2]-dp[mi2][0]+dp[mi3][3]-dp[mi3][0], mi4==-1?0:dp[mi1][2]-dp[mi1][0]+dp[mi4][3]-dp[mi4][0])), dp[u][1]);
	dp[u][3]=dp[u][1]+a;
	dp[u][1]=max(dp[u][0]+m3, dp[u][1]);
	dp[u][0]+=m1;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n;
	for(int i=0; i<n-1; ++i) {
		int u, v, c;
		cin >> u >> v >> c, --u, --v;
		adj[u].push_back({v, c});
		adj[v].push_back({u, c});
	}
	dfs1(0, -1, -2e9);
	cout << dp[0][1];
}
