/*
	- Add the new roads first, then add the old roads from smallest to largest without forming cycles
	- Those old roads will always be added regardless of which new roads are required
		- Find those first
		- We can compress the original graph into at most k+1 nodes
	- There will also be at most k old roads that will connect all towns if 0 new roads are chosen
		- Find these first
	- Then test all 2^k combinations
	- For each old road (u, v) that isn't used, the path from u to v cannot have edge weights greater than that old road
	- We can run dfs from u to v and update the weights of the new roads, which will be O(k^2) per combination
	- This will pass with optimizations
	- We can sort the new roads by weight, and when we update the weight from u to its parent, we can merge them so we never update the edge again
	- O(k*a(k)) per combination
	- Union by rank is removed as it actually makes the program slower
*/

#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int mxN=1e5, mxK=20, mxM=3e5;
int n, k, m, r[mxN], p[mxK+1], d[mxK+1], rs, w[mxK+1];
array<int, 3> e[mxM];
array<int, 2> a[mxK];
vector<int> adj[mxN], b;
ll s[mxK+1], ans;

template<size_t S>
struct dsu {
	int p[S];
	int find(int x) {
		return x==p[x]?x:(p[x]=find(p[x]));
	}
	bool join(int x, int y) {
		p[y=find(y)]=x=find(x);
		return x^y;
	}
};
dsu<mxN> d1, d2, d3;
dsu<mxK+1> d4;
dsu<mxK+1> d5;

void dfs1(int u, int pu=-1) {
	p[u]=pu;
	d[u]=pu^-1?d[pu]+1:0;
	for(int v : adj[u])
		if(v!=pu)
			dfs1(v, u);
}

ll dfs2(int u, ll d=0) {
	ll r=d*s[u];
	for(int v : adj[u])
		if(v!=p[u])
			r+=dfs2(v, d+w[v]);
	return r;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> n >> m >> k;
	for(int i=0; i<m; ++i)
		cin >> e[i][1] >> e[i][2] >> e[i][0], --e[i][1], --e[i][2];
	sort(e, e+m);
	iota(d1.p, d1.p+n, 0);
	for(int i=0; i<k; ++i) {
		cin >> a[i][0] >> a[i][1], --a[i][0], --a[i][1];
		d1.join(a[i][0], a[i][1]);
	}
	iota(d2.p, d2.p+n, 0);
	iota(d3.p, d3.p+n, 0);
	for(int i=0; i<m; ++i) {
		if(!d2.join(e[i][1], e[i][2]))
			continue;
		if(d1.join(e[i][1], e[i][2]))
			d3.join(e[i][1], e[i][2]);
		else
			b.push_back(i);
	}
	for(int i=0; i<n; ++i)
		if(d3.find(i)==i)
			r[i]=rs++;
	for(int i=0, si; i<n; ++i) {
		cin >> si;
		s[r[d3.find(i)]]+=si;
	}
	for(int bi : b) {
		e[bi][1]=r[d3.find(e[bi][1])];
		e[bi][2]=r[d3.find(e[bi][2])];
	}
	for(int i=0; i<k; ++i) {
		a[i][0]=r[d3.find(a[i][0])];
		a[i][1]=r[d3.find(a[i][1])];
	}
	for(int i=0; i<1<<k; ++i) {
		for(int j=0; j<rs; ++j)
			adj[j].clear();
		iota(d4.p, d4.p+rs, 0);
		iota(d5.p, d5.p+rs, 0);
		for(int j=0; j<k; ++j) {
			if(i>>j&1&&d4.join(a[j][0], a[j][1])) {
				adj[a[j][0]].push_back(a[j][1]);
				adj[a[j][1]].push_back(a[j][0]);
			}
		}
		deque<array<int, 3>> c;
		for(int bi : b) {
			if(d4.join(e[bi][1], e[bi][2])) {
				adj[e[bi][1]].push_back(e[bi][2]);
				adj[e[bi][2]].push_back(e[bi][1]);
				c.push_front({0, e[bi][1], e[bi][2]});
			} else
				c.push_back(e[bi]);
		}
		dfs1(r[d3.find(0)]);
		for(array<int, 3> ci : c) {
			int u=d5.find(ci[1]), v=d5.find(ci[2]);
			while(u^v) {
				if(d[u]<d[v])
					swap(u, v);
				w[u]=ci[0];
				d5.join(p[u], u);
				u=d5.find(u);
			}
		}
		ans=max(dfs2(r[d3.find(0)]), ans);
	}
	cout << ans;
}
