#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define ar array

const int mxN=1e5, M=1e9+7;
int n, dp1[mxN];
ar<int, 2> dp2[mxN];
ll d;
vector<int> adj[mxN];
ar<ll, 2> r;
ar<ar<ll, 2>, 2> b;

void dfs1(int u=0, int p=-1) {
	if(u)
		adj[u].erase(find(adj[u].begin(), adj[u].end(), p));
	for(int v : adj[u]) {
		dfs1(v, u);
		dp1[u]+=!dp1[v];
	}
	dp2[u][1]=1;
	for(int v : adj[u])
		for(int k : {0, 1})
			dp2[u][dp1[u]-!dp1[v]+!k>0]=(dp2[u][dp1[u]-!dp1[v]+!k>0]+dp2[v][k])%M;
}

void dfs2(int u=0, int pd1=1, ar<int, 2> pd2={}) {
	dp1[u]+=!pd1;
	++r[dp1[u]>0];
	b[1][dp1[u]>0]=(b[1][dp1[u]>0]+n)%M;
	ar<int, 3> dp3{0, 0, 1};
	for(int v : adj[u])
		for(int k : {0, 1})
			dp3[min(dp1[u]-!dp1[v]+!k, 2)]=(dp3[min(dp1[u]-!dp1[v]+!k, 2)]+dp2[v][k])%M;
	for(int k : {0, 1})
		dp3[min(dp1[u]-!pd1+!k, 2)]=(dp3[min(dp1[u]-!pd1+!k, 2)]+pd2[k])%M;
	b[0][0]=(b[0][0]+dp3[0])%M;
	b[0][1]=(b[0][1]+dp3[1]+dp3[2])%M;
	for(int v : adj[u]) {
		ar<int, 3> ndp3=dp3;
		for(int k : {0, 1})
			ndp3[min(dp1[u]-!dp1[v]+!k, 2)]=(ndp3[min(dp1[u]-!dp1[v]+!k, 2)]+M-dp2[v][k])%M;
		if(!dp1[v]) {
			ndp3[0]=(ndp3[0]+ndp3[1])%M;
			ndp3[1]=0;
		}
		ndp3[1]=(ndp3[1]+ndp3[2])%M;
		dfs2(v, dp1[u]-!dp1[v], {ndp3[0], ndp3[1]});
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> d, --d;
	for(int i=1, u, v; i<n; ++i) {
		cin >> u >> v, --u, --v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	dfs1();
	dfs2();
	while(d) {
		if(d&1)
			r={(r[0]*b[0][0]+r[1]*b[1][0])%M, (r[0]*b[0][1]+r[1]*b[1][1])%M};
		b={{{(b[0][0]*b[0][0]+b[0][1]*b[1][0])%M, (b[0][0]*b[0][1]+b[0][1]*b[1][1])%M}, {(b[1][0]*b[0][0]+b[1][1]*b[1][0])%M, (b[1][0]*b[0][1]+b[1][1]*b[1][1])%M}}};
		d/=2;
	}
	cout << (dp2[0][1]*r[0]+(dp1[0]?n*r[1]:0))%M;
}
