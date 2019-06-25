#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int mxN=5e5;
int n, s[mxN];
vector<int> adj[mxN];
ll a[mxN], ans;

struct cht {
	ll a[mxN], b[mxN];
	int qt;
	void al(ll ai, ll bi) {
		if(qt&&ai==a[qt-1]) {
			if(bi>b[qt-1])
				return;
			--qt;
		}
		while(qt>1&&(bi-b[qt-1])/(a[qt-1]-ai)>(b[qt-1]-b[qt-2])/(a[qt-2]-a[qt-1]))
			--qt;
		a[qt]=ai;
		b[qt]=bi;
		++qt;
	}
	ll qry(ll x) {
		while(qt>1&&a[qt-2]*x+b[qt-2]<a[qt-1]*x+b[qt-1])
			--qt;
		return a[qt-1]*x+b[qt-1];
	}
} cht;

void dfs(int u=0, int p=-1) {
	if(~p)
		adj[u].erase(find(adj[u].begin(), adj[u].end(), p));
	s[u]=1;
	for(int v : adj[u]) {
		dfs(v, u);
		s[u]+=s[v];
	}
	a[u]=2ll*s[u]*s[u];
	sort(adj[u].begin(), adj[u].end(), [](const int &i, const int &j) {
		return s[i]<s[j];
	});
	cht.qt=1;
	for(int v : adj[u]) {
		a[u]=min(a[v]+2ll*s[u]*(s[u]-s[v]), a[u]);
		ans=min(cht.qry(s[v])+a[v]-2ll*n*s[v], ans);
		cht.al(2*s[v], a[v]-2ll*n*s[v]);
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> n;
	for(int i=1, u, v; i<n; ++i) {
		cin >> u >> v, --u, --v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	dfs();
	cout << ((ll)n*(n-1)-ans)/2;
}
