/*
	- http://codeforces.com/blog/entry/58433?#comment-421295
	- For some reason, the runtime is the lowest when the block size is around 10
*/

#include <bits/stdc++.h>
using namespace std;

#define pii pair<int, int>
#define fi first
#define se second

const int mxN=1e5, bs=10;
int n, m, q, dp2[mxN], c[mxN];
vector<int> adj[mxN];
vector<pii> dp1[mxN];
priority_queue<pii, vector<pii>, greater<pii>> pq;
bool a[mxN];

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> m >> q;
	while(m--) {
		int u, v;
		cin >> u >> v, --u, --v;
		adj[v].push_back(u);
	}
	for(int i=0; i<n; ++i) {
		pq.push({0, i});
		for(int v : adj[i]) {
			for(pii p : dp1[v]) {
				pq.push({p.fi+1, p.se});
				if(pq.size()>bs)
					pq.pop();
			}
		}
		while(!pq.empty()) {
			dp1[i].push_back(pq.top());
			pq.pop();
		}
	}
	while(q--) {
		int t, y, ans=-1;
		cin >> t >> y, --t;
		for(int i=0; i<y; ++i) {
			cin >> c[i], --c[i];
			a[c[i]]=1;
		}
		if(y>bs) {
			memset(dp2, -1, 4*(t+1));
			for(int i=0; i<=t; ++i) {
				dp2[i]=a[i]?-n:0;
				for(int v : adj[i])
					dp2[i]=max(dp2[v]+1, dp2[i]);
			}
			ans=max(dp2[t], ans);
		} else {
			for(int i=dp1[t].size()-1; i>=0; --i) {
				if(a[dp1[t][i].se])
					continue;
				ans=dp1[t][i].fi;
				break;
			}
		}
		for(int i=0; i<y; ++i)
			a[c[i]]=0;
		cout << ans << "\n";
	}
}
