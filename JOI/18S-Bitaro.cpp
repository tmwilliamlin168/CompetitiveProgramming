/*
	- http://codeforces.com/blog/entry/58433?#comment-421295
*/

#include <bits/stdc++.h>
using namespace std;
 
const int mxN=1e5, bs=60;
int n, m, q, dp2[mxN], c[mxN];
vector<int> adj[mxN];
vector<array<int, 2>> dp1[mxN];
bool a[mxN];
 
int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> m >> q;
	for(int i=0, u, v; i<m; ++i)
		cin >> u >> v, --u, --v, adj[v].push_back(u);
	for(int i=0; i<n; ++i) {
		vector<int> w={i};
		for(int v : adj[i]) {
			for(array<int, 2> p : dp1[v]) {
				if(!c[p[1]])
					w.push_back(p[1]);
				c[p[1]]=max(p[0]+1, c[p[1]]);
			}
		}
		nth_element(w.begin(), w.begin()+min(bs, (int)w.size()), w.end(), [&](int a, int b) {
			return c[a]>c[b];
		});
		for(int j=0; j<min(bs, (int)w.size()); ++j)
			dp1[i].push_back({c[w[j]], w[j]});
		for(int wi : w)
			c[wi]=0;
	}
	while(q--) {
		int t, y, ans=-1;
		cin >> t >> y, --t;
		for(int i=0; i<y; ++i) {
			cin >> c[i], --c[i];
			a[c[i]]=1;
		}
		if(y>=bs) {
			for(int i=0; i<=t; ++i) {
				dp2[i]=a[i]?-n:0;
				for(int v : adj[i])
					dp2[i]=max(dp2[v]+1, dp2[i]);
			}
			ans=max(dp2[t], ans);
		} else 
			for(array<int, 2> p : dp1[t])
				if(!a[p[1]])
					ans=max(p[0], ans);
		for(int i=0; i<y; ++i)
			a[c[i]]=0;
		cout << ans << "\n";
	}
}
