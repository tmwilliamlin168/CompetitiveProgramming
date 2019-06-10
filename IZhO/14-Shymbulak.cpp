/*
	- The graph consists of a cycle with trees growing out of it
	- Calculating the answer for the trees and the height of them is standard
	- We can maintain a circular maximum sliding window of size (cycle length)/2 to calculate the answer for each endpoint on the cycle
*/

#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pil pair<int, ll>

const int mxN=2e5;
int n, qh, qt;
vector<int> adj[mxN], cyc;
pil ans, a[mxN], qu[mxN];
bool vis[mxN], ic[mxN];

pil operator+(const pil &a, const pil &b) {
	return pil(max(a.first, b.first), (a.first>=b.first?a.second:0)+(a.first<=b.first?b.second:0));
}

bool dfs1(int u=0, int p=-1) {
	if(vis[u]) {
		cyc.push_back(u);
		return 1;
	}
	vis[u]=1;
	for(int v : adj[u]) {
		if(v^p&&dfs1(v, u)) {
			if(u==cyc[0])
				return 0;
			cyc.push_back(u);
			return 1;
		}
	}
	return 0;
}

void dfs2(int u, int p=-1) {
	a[u]=pil(0, 1);
	for(int v : adj[u]) {
		if(v==p||ic[v])
			continue;
		dfs2(v, u);
		ans=ans+pil(++a[v].first+a[u].first, a[v].second*a[u].second);
		a[u]=a[u]+a[v];
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> n;
	for(int i=0, u, v; i<n; ++i) {
		cin >> u >> v, --u, --v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	dfs1();
	for(int c : cyc)
		ic[c]=1;
	for(int c : cyc)
		dfs2(c);
	for(int i=0, cs=cyc.size(); i<2*cs; ++i) {
		pil u=a[cyc[i%cs]];
		if(i>=cs)
			ans=ans+pil(qu[qh].first+u.first+i, qu[qh].second*u.second);
		while(qt>qh&&qu[qt-1].first<u.first-i)
			--qt;
		if(qt==qh||qu[qt-1].first>u.first-i)
			qu[qt++]=pil(u.first-i, 0);
		qu[qt-1].second+=u.second;
		if(i>=cs/2) {
			pil v=a[cyc[(i-cs/2)%cs]];
			if(qu[qh].first==v.first-(i-cs/2))
				qu[qh].second-=v.second;
			qh+=!qu[qh].second;
		}
	}
	cout << ans.second;
}
