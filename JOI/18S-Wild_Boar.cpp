/*
	- For each 2 adjacent food stations, we only care about a combination of 5 paths
	- Precompute those paths with dijkstra
	- Use a segment tree for fast updates
*/

#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define a array

const int mxN=2e3, mxL=1e5;
const ll INF=1e18;
int n, m, t, l, x[mxL], ai, bi, ci;
vector<a<int, 2>> adj[mxN];
a<ll, 3> d[mxN][mxN][5], st[1<<18][5];
priority_queue<a<ll, 4>, vector<a<ll, 4>>, greater<a<ll, 4>>> pq;

bool ad(a<ll, 3> b[5], a<ll, 3> c, int d) {
	int i=0, c1=0, c2=0, c3=0;
	while(i<d&&b[i][0]<INF) {
		c1+=b[i][1]==c[1]&&b[i][2]==c[2];
		c2+=b[i][1]==c[1];
		c3+=b[i][2]==c[2];
		++i;
	}
	if(i<5&&!c1&&c2<2&&c3<2) {
		b[i]=min(c, b[i]);
		return 1;
	}
	return 0;
}

void dij(int s, a<ll, 3> d[mxN][5]) {
	for(int i=0; i<n; ++i)
		for(int j=0; j<5; ++j)
			d[i][j]={INF};
	for(a<int, 2> e : adj[s])
		pq.push({e[0], e[1], e[1], s});
	while(pq.size()) {
		a<ll, 4> u=pq.top();
		pq.pop();
		if(!ad(d[u[1]], {u[0], u[2], u[3]}, 5))
			continue;
		for(a<int, 2> e : adj[u[1]])
			if(e[1]!=u[3])
				pq.push({u[0]+e[0], e[1], u[2], u[1]});
	}
}

void upd(int l1, int i=1, int l2=0, int r2=l-2) {
	if(l2==r2) {
		for(int j=0; j<5; ++j)
			st[i][j]=d[x[l1]][x[l1+1]][j];
		return;
	}
	int m2=(l2+r2)/2;
	if(l1<=m2)
		upd(l1, 2*i, l2, m2);
	else
		upd(l1, 2*i+1, m2+1, r2);
	for(int j=0; j<5; ++j) {
		st[i][j]={INF};
		for(int k=0; k<5; ++k)
			for(int l=0; l<5; ++l)
				if(st[2*i][k][2]!=st[2*i+1][l][1])
					ad(st[i], {st[2*i][k][0]+st[2*i+1][l][0], st[2*i][k][1], st[2*i+1][l][2]}, j);
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> m >> t >> l;
	while(m--) {
		cin >> ai >> bi >> ci, --ai, --bi;
		adj[ai].push_back({ci, bi});
		adj[bi].push_back({ci, ai});
	}
	for(int i=0; i<n; ++i)
		dij(i, d[i]);
	for(int i=0; i<l; ++i) {
		cin >> x[i], --x[i];
		if(i)
			upd(i-1);
	}
	while(t--) {
		int pk, qk;
		cin >> pk >> qk, --pk, --qk;
		x[pk]=qk;
		if(pk)
			upd(pk-1);
		if(pk<l-1)
			upd(pk);
		ll ans=min({st[1][0][0], st[1][1][0], st[1][2][0], st[1][3][0], st[1][4][0]});
		cout << (ans>=INF?-1:ans) << "\n";
	}
}
