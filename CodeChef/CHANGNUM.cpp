/*
	- For each i, create an edge from a[i] to b[i]
		- All nodes within the connected component will be set to the same value
	- c = number of connected components, si = size of the ith connected component
	- The answer to the first part is n-c
	- The number of ways to choose a sequence for the ith connected component is di = product(2<=j<=si, j*(j-1))
	- The answer to the second part is (n-c)! * product(1<=i<=c, di/(si-1)!)
*/

#include <bits/stdc++.h>
using namespace std;
 
#define ll long long
 
const int mxN=1e5, M=1e9+7;
int t, n, k, a[mxN], b[mxN], a1;
set<int> adj[mxN];
bool vis[mxN];
ll a2;

int dfs(int u) {
	int s=1;
	vis[u]=1;
	for(int v : adj[u])
		if(!vis[v])
			s+=dfs(v);
	return s;
}

inline void solve() {
	cin >> n >> k;
	for(int i=0; i<n; ++i)
		cin >> a[i], --a[i];
	for(int i=0; i<n; ++i)
		cin >> b[i], --b[i];
	for(int i=0; i<n; ++i) {
		adj[a[i]].insert(b[i]);
		adj[b[i]].insert(a[i]);
	}
	a1=n;
	a2=1;
	memset(vis, 0, n);
	for(int i=0; i<n; ++i) {
		if(!vis[i]) {
			ll s=dfs(i);
			for(ll j=2; j<=s; ++j)
				a2=a2*j%M;
			--a1;
		}
	}
	for(int i=1; i<=a1; ++i)
		a2=a2*i%M;
	cout << a1;
	if(k>1)
		cout << " " << a2;
	cout << "\n";
	for(int i=0; i<n; ++i)
		adj[i].clear();
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> t;
	while(t--)
		solve();
}
