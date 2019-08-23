/*
	- We can rewrite the condition as 2*a-b >= 0 and 2*b-a >= 0
	- First find the product of all paths
	- Divide by the paths with 2*a-b < 0 or 2*b-a < 0
	- We can find the product of these paths with centroid decomposition
*/

#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pli pair<ll, int>

const int mxN=1e5, M=1e9+7;
int n, eu[mxN], ev[mxN], ew[mxN], ec[mxN], s[mxN], ctp[mxN];
vector<int> adj[mxN];
ll ans=1;
vector<pli> v1, v2;
pli ft[3*mxN];

pli operator+(const pli &a, const pli &b) {
	return pli(a.first*b.first%M, a.second+b.second);
}

void upd(int i, pli x) {
	for(; i<3*n; i+=i&-i)
		ft[i]=ft[i]+x;
}

pli qry(int i) {
	pli r(1, 0);
	for(; i>0; i-=i&-i)
		r=r+ft[i];
	return r;
}

ll pm(ll b, ll p) {
	ll r=1;
	for(; p; b=b*b%M, p/=2)
		if(p&1)
			r=r*b%M;
	return r;
}

void dfs1(int u, int pe, bool a=0) {
	s[u]=1;
	for(int e : adj[u]) {
		int v=eu[e]^ev[e]^u;
		if(e==pe||~ctp[v])
			continue;
		dfs1(v, e, a);
		s[u]+=s[v];
	}
	if(a)
		ans=ans*pm(ew[pe], (ll)s[u]*(n-s[u]))%M;
}

int dfs2(int u, int pe, int n) {
	for(int e : adj[u]) {
		int v=eu[e]^ev[e]^u;
		if(e^pe&&ctp[v]==-1&&s[v]>n/2)
			return dfs2(v, e, n);
	}
	return u;
}

void dfs3(int u, int pe, ll pw, int pd) {
	v1.push_back(pli(pw, pd));
	for(int e : adj[u]) {
		int v=eu[e]^ev[e]^u;
		if(e^pe&&ctp[v]==-1)
			dfs3(v, e, pw*ew[e]%M, pd+(ec[e]?2:-1));
	}
}

void cd(int u=0, int p=-2) {
	u=dfs2(u, 0, s[u]);
	ctp[u]=p;
	dfs1(u, 0);
	for(int e : adj[u]) {
		int v=eu[e]^ev[e]^u;
		if(~ctp[v])
			continue;
		dfs3(v, 0, ew[e], n+(ec[e]?2:-1));
		for(pli a : v1) {
			pli b=qry(2*n-a.second-1);
			ans=ans*b.first%M*pm(a.first, b.second)%M;
		}
		for(; v1.size(); v2.push_back(v1.back()), v1.pop_back())
			upd(v1.back().second, pli(v1.back().first, 1));
	}
	for(; v2.size(); v2.pop_back())
		upd(v2.back().second, pli(pm(v2.back().first, M-2), -1));
	for(int e : adj[u]) {
		int v=eu[e]^ev[e]^u;
		if(ctp[v]==-1)
			cd(v, u);
	}
}

void solve() {
	dfs1(0, 0);
	cd();
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> n;
	for(int i=1; i<n; ++i) {
		cin >> eu[i] >> ev[i] >> ew[i] >> ec[i], --eu[i], --ev[i];
		adj[eu[i]].push_back(i);
		adj[ev[i]].push_back(i);
	}
	memset(ctp, -1, 4*n);
	dfs1(0, 0, 1);
	for(int i=1; i<n; ++i)
		ew[i]=pm(ew[i], M-2);
	fill(ft, ft+3*n, pli(1, 0));
	upd(n, pli(1, 1));
	solve();
	memset(ctp, -1, 4*n);
	for(int i=1; i<n; ++i)
		ec[i]^=1;
	solve();
	cout << ans;
}
