#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pii pair<int, int>
#define fi first
#define se second

const int mxN=5e5;
int n, k, m;
vector<int> adj[mxN];
priority_queue<pii, vector<pii>, greater<pii>> pq[mxN];
ll ans;

struct dsu {
	int p[mxN], r[mxN];
	void init(int n) {
		for(int i=0; i<n; ++i)
			p[i]=i;
	}
	int find(int x) {
		return x==p[x]?x:(p[x]=find(p[x]));
	}
	bool join(int x, int y) {
		if((x=find(x))==(y=find(y)))
			return 0;
		if(r[x]<r[y])
			p[x]=y;
		else
			p[y]=x;
		r[x]+=r[x]==r[y];
		return 1;
	}
} d1;

void dfs(int u, int p=-1) {
	for(int v : adj[u]) {
		if(v==p)
			continue;
		dfs(v, u);
		if(pq[v].size()>pq[u].size())
			swap(pq[v], pq[u]);
		while(!pq[v].empty()) {
			pq[u].push(pq[v].top());
			pq[v].pop();
		}
	}
	while(pq[u].size()>1) {
		pii a=pq[u].top();
		pq[u].pop();
		if(a!=pq[u].top()) {
			pq[u].push(a);
			break;
		}
		pq[u].pop();
	}
	if(p!=-1) {
		if(pq[u].empty()) {
			cout << -1;
			exit(0);
		}
		ans+=pq[u].top().fi;
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0); 
	
	cin >> n >> k >> m;
	d1.init(n);
	for(int i=0; i<k; ++i) {
		int ga, gb;
		cin >> ga >> gb, --ga, --gb;
		d1.join(ga, gb);
		adj[ga].push_back(gb);
		adj[gb].push_back(ga);
	}
	for(int i=0; i<m; ++i) {
		int fa, fb, fw;
		cin >> fa >> fb >> fw, --fa, --fb;
		if(d1.join(fa, fb)) {
			adj[fa].push_back(fb);
			adj[fb].push_back(fa);
			fw=0;
		}
		pq[fa].push({fw, i});
		pq[fb].push({fw, i});
	}
	dfs(0);
	cout << ans;
}
