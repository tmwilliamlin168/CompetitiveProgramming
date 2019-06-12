#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int mxN=4e5+2;
int n, m, c[mxN], p[mxN];
vector<int> adj[mxN];
vector<array<int, 3>> td[mxN];
ll ans, d[mxN];

struct linkcut {
	int p[mxN], pp[mxN], c[mxN][2];
	int s[mxN], se[mxN];
	ll s2e[mxN];
	void cmb(int u) {
		s[u]=s[c[u][0]]+1+s[c[u][1]]+se[u];
	}
	int ci(int u) {
		return c[p[u]][1]==u;
	}
	void cn(int u, int v, int i) {
		if(u)
			p[u]=v;
		if(v)
			c[v][i]=u;
	}
	void ro(int u) {
		int v=p[u], i=ci(u), w=p[v], j=ci(v);
		cn(c[u][!i], v, i);
		cn(v, u, !i);
		cn(u, w, j);
		swap(pp[u], pp[v]);
		cmb(v);
		cmb(u);
	}
	int spl(int u) {
		while(p[p[u]]) {
			ro(ci(u)^ci(p[u])?u:p[u]);
			ro(u);
		}
		if(p[u])
			ro(u);
		return u;
	}
	void dc(int u, int i) {
		p[c[u][i]]=0;
		c[u][i]=0;
	}
	void ppc(int u, int v) {
		if(!u)
			return;
		se[v]+=s[u];
		s2e[v]+=(ll)s[u]*s[u];
		pp[u]=v;
	}
	void ppd(int u) {
		se[pp[u]]-=s[u];
		s2e[pp[u]]-=(ll)s[u]*s[u];
		pp[u]=0;
	}
	int xp(int u) {
		for(int v=u, w=0; v; w=v, v=pp[v]) {
			spl(v);
			ppc(c[v][1], v);
			dc(v, 1);
			ppd(w);
			cn(w, v, 1);
			cmb(v);
		}
		return spl(u);
	}
	void lk(int u, int v) {
		ppc(spl(u), xp(v));
		cmb(v);
	}
	void ct(int u) {
		dc(xp(u), 0);
		cmb(u);
	}
	int gf(int u) {
		return c[u][0]?gf(c[u][0]):u;
	}
	int gr(int u) {
		return spl(gf(xp(u)));
	}
} lc;

void dfs(int u=1) {
	for(int v : adj[u]) {
		if(v^p[u]) {
			p[v]=u;
			dfs(v);
		}
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> n >> m;
	lc.s[1]=1;
	for(int i=1; i<=n; ++i) {
		cin >> c[i];
		td[c[i]].push_back({0, i, 0});
		lc.s[i+1]=1;
	}
	for(int i=1, u, v; i<n; ++i) {
		cin >> u >> v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	for(int i=1, u, x; i<=m; ++i) {
		cin >> u >> x;
		td[c[u]].push_back({i, u, 1});
		c[u]=x;
		td[c[u]].push_back({i, u, 0});
	}
	dfs();
	for(int i=1; i<=n; ++i)
		lc.lk(i+1, p[i]+1);
	auto gg=[](int u) {
		return lc.s2e[lc.xp(lc.gr(u+1))];
	};
	for(int i=1; i<=n; ++i) {
		for(array<int, 3> a : td[i]) {
			if(a[2]) {
				d[a[0]]+=gg(a[1])+gg(p[a[1]]);
				lc.lk(a[1]+1, p[a[1]]+1);
				d[a[0]]-=gg(a[1]);
			} else {
				d[a[0]]+=gg(a[1]);
				lc.ct(a[1]+1);
				d[a[0]]-=gg(a[1])+gg(p[a[1]]);
			}
		}
		for(array<int, 3> a : td[i]) {
			lc.ct(a[1]+1);
			lc.lk(a[1]+1, p[a[1]]+1);
		}
	}
	for(int i=0; i<=m; ++i)
		cout << (ans+=d[i]) << "\n";
}
