/*
	- Use DSU to easily keep track of equal coins
	- Use DP to find min and max values of each coin
*/

#include <bits/stdc++.h>
using namespace std;

const int mxN=3e5;
int n, m, v, p[mxN], r[mxN], a[mxN], b[mxN], dp[2][mxN];
vector<int> adj[2][mxN];

int root(int x) {
	return p[x]==x?x:(p[x]=root(p[x]));
}

void join(int x, int y) {
	if((x=root(x))==(y=root(y)))
		return;
	if(r[x]<r[y])
		p[x]=y;
	else
		p[y]=x;
	r[x]+=r[x]==r[y];
}

int cdp(int a, int u) {
	if(!dp[a][u]) {
		dp[a][u]=a?n:1;
		for(int v : adj[a][u])
			dp[a][u]=a?min(cdp(a, v)-1, dp[a][u]):max(cdp(a, v)+1, dp[a][u]);
	}
	return dp[a][u];
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> m >> v;
	for(int i=0; i<m; ++i)
		p[i]=i;
	for(int i=0; i<v; ++i) {
		char qt;
		cin >> a[i] >> qt >> b[i], --a[i], --b[i];
		if(qt=='=') {
			join(a[i], b[i]);
			a[i]=-1;
		}
	}
	for(int i=0; i<v; ++i) {
		if(a[i]!=-1) {
			adj[0][root(b[i])].push_back(root(a[i]));
			adj[1][root(a[i])].push_back(root(b[i]));
		}
	}
	for(int i=0; i<m; ++i)
		cout << (cdp(0, root(i))==cdp(1, root(i))?"K"+to_string(cdp(0, root(i))):"?") << "\n";
}
