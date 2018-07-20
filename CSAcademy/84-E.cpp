/*
	- The lengths of all paths are linear functions in terms of d
	- The length of the diameter is the maximum of these functions, so it's convex
	- Ternary search can be used
*/

#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int mxN=2.5e5;
int n, d, eu[mxN-1], ev[mxN-1];
vector<int> adj[mxN];
ll c[mxN-1], a[mxN-1], dia;

inline ll dfs(int u, int p, int d) {
	ll m1=0, m2=0;
	for(int e : adj[u]) {
		int v=u^eu[e]^ev[e];
		if(v==p)
			continue;
		ll m3=dfs(v, u, d)+c[e]+a[e]*d;
		if(m3>m1)
			swap(m3, m1);
		if(m3>m2)
			swap(m3, m2);
	}
	dia=max(m1+m2, dia);
	return m1;
}

inline ll chk(int d) {
	dia=0;
	dfs(0, -1, d);
	return dia;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> d;
	for(int i=0; i<n-1; ++i) {
		cin >> eu[i] >> ev[i] >> c[i] >> a[i], --eu[i], --ev[i];
		adj[eu[i]].push_back(i);
		adj[ev[i]].push_back(i);
	}
	int lb=0, rb=d-1;
	while(lb<=rb) {
		int mb=(lb+rb)/2;
		ll a=chk(mb), b=chk(mb+1);
		if(a<=b)
			rb=mb-1;
		else
			lb=mb+1;
	}
	chk(lb);
	cout << lb << "\n" << dia;
}
