#include <bits/stdc++.h>
using namespace std;

const int mxN=1e3, M=998244353;
string s;
int n, ans, ca, c[2*mxN];
vector<array<int, 2>> adj[2*mxN];

void dfs(int u, int cu) {
	if(~c[u]) {
		if(cu^c[u])
			ca=0;
		return;
	}
	c[u]=cu;
	for(array<int, 2> v : adj[u])
		dfs(v[0], cu^v[1]);
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> s, n=s.size(), reverse(s.begin(), s.end());
	auto ae=[](int i, int j, int k=0) {
		adj[i].push_back({j, k});
		adj[j].push_back({i, k});
	};
	for(int i=0; i<n; ++i)
		if(s[i]^'?')
			ae(i, n+i, s[i]&1);
	for(int i=0; i<n-1-i; ++i)
		ae(i, n-1-i);
	for(int i=n-1; i; --i) {
		ca=1;
		for(int j=0; j<i; ++j)
			adj[n+j].push_back({n+i-1-j});
		ae(n+i-1, n+i, 1);
		for(int j=i; j+1<n; ++j)
			ae(n+j, n+j+1);
		memset(c, -1, 8*n);
		for(int j=2*n-1; ~j; --j) {
			if(~c[j])
				continue;
			dfs(j, 0);
			ca=ca*(1+(j<2*n-1))%M;
		}
		ans=(ans+ca)%M;
		for(int j=0; j<i; ++j)
			adj[n+j].pop_back();
		for(int j=i-1; j+1<n; ++j) {
			adj[n+j].pop_back();
			adj[n+j+1].pop_back();
		}
	}
	cout << ans;
}
