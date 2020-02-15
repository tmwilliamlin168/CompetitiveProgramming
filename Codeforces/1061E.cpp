#include <bits/stdc++.h>
using namespace std;

const int mxN=500;
int n, x, y, a[mxN], ui, vi, q1, q2, k1[mxN], k2[mxN], r1[mxN], r2[mxN], b1[mxN], b2[mxN], m, d[2*mxN+2], p[2*mxN+2], tf, ans;
vector<int> adj1[mxN], adj2[mxN];
vector<array<int, 4>> e;

void fk() {
	cout << -1;
	exit(0);
}

int dfs(int u, vector<int> adj[mxN], int r[mxN], int b[mxN], int p=-1) {
	b[u]=r[u]?m++:b[p];
	int s=0;
	for(int v : adj[u])
		if(v!=p)
			s+=dfs(v, adj, r, b, u);
	if(r[u]) {
		r[u]-=s;
		s+=r[u];
	}
	if(r[u]<0)
		fk();
	return s;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> x >> y, --x, --y;
	for(int i=0; i<n; ++i)
		cin >> a[i];
	auto rg=[&](vector<int> adj[mxN]) {
		for(int i=0; i<n-1; ++i) {
			cin >> ui >> vi, --ui, --vi;
			adj[ui].push_back(vi);
			adj[vi].push_back(ui);
		}
	};
	rg(adj1);
	rg(adj2);
	auto rr=[&](int &q, int k[mxN], int r[mxN]) {
		cin >> q;
		for(int i=0; i<q; ++i) {
			cin >> k[i] >> ui, --k[i];
			r[k[i]]=ui;
		}
	};
	rr(q1, k1, r1);
	rr(q2, k2, r2);
	if(r1[x]!=r2[y])
		fk();
	tf=r1[x];
	dfs(x, adj1, r1, b1);
	dfs(y, adj2, r2, b2);
	auto ae=[&](int u, int v, int c1, int c2) {
		e.push_back({u, v, c1, c2});
		e.push_back({v, u, 0, -c2});
	};
	for(int i=0; i<q1; ++i)
		ae(0, b1[k1[i]]+1, r1[k1[i]], 0);
	for(int i=0; i<q2; ++i)
		ae(1+b2[k2[i]], 1+q1+q2, r2[k2[i]], 0);
	for(int i=0; i<n; ++i)
		ae(1+b1[i], 1+b2[i], 1, a[i]);
	for(int it1=0; it1<tf; ++it1) {
		memset(p, -1, 4*(q1+q2+2));
		d[0]=0;
		p[0]=-2;
		for(int it2=0; it2<q1+q2+1; ++it2) {
			for(int i=0; i<e.size(); ++i) {
				if(p[e[i][0]]!=-1&&e[i][2]>0&&(p[e[i][1]]==-1||d[e[i][1]]<d[e[i][0]]+e[i][3])) {
					d[e[i][1]]=d[e[i][0]]+e[i][3];
					p[e[i][1]]=i;
				}
			}
		}
		if(p[1+q1+q2]==-1)
			fk();
		ans+=d[1+q1+q2];
		for(int i=1+q1+q2; i; i=e[p[i]][0]) {
			--e[p[i]][2];
			++e[p[i]^1][2];
		}
	}
	cout << ans;
}
