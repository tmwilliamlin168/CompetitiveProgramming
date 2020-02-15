#include <bits/stdc++.h>
using namespace std;

const int mxN=1e5;
int n, m, ui, vi, p[mxN], d[mxN], pr[mxN], hv[mxN], ap[mxN], pv[2*mxN];
vector<int> adj[mxN], st[2*mxN];

#define y(x) (2*(x))
#define n(x) (2*(x)+1)
template<int SZ> struct twosat {
	int n, c[2*SZ];
	vector<int> a1[2*SZ], a2[2*SZ], st;
	bool vis[2*SZ], ans[SZ];
	void imp(int u, int v) {
		a1[u].push_back(v);
		a1[v^1].push_back(u^1);
	}
	void dfs1(int u) {
		vis[u]=1;
		for(int v : a1[u])
			if(!vis[v])
				dfs1(v);
		st.push_back(u);
	}
	void dfs2(int u, int cu) {
		vis[u]=0;
		c[u]=cu;
		for(int v : a2[u])
			if(vis[v])
				dfs2(v, cu);
	}
	bool ac() {
		for(int i=0; i<2*n; ++i)
			if(!vis[i])
				dfs1(i);
		for(int i=0; i<2*n; ++i)
			for(int j : a1[i])
				a2[j].push_back(i);
		for(int i=2*n-1; i>=0; --i)
			if(vis[st[i]])
				dfs2(st[i], i);
		for(int i=0; i<2*n; i+=2) {
			if(c[i]==c[i^1])
				return 0;
			ans[i/2]=c[i]<c[i^1];
		}
		return 1;
	}
};
twosat<(int)7e5> ts;

int dfs(int u=0, int pu=-1) {
	int s=1, mcs=0;
	p[u]=pu;
	d[u]=pu==-1?0:d[pu]+1;
	for(int v : adj[u]) {
		if(v==pu)
			continue;
		int cs=dfs(v, u);
		if(cs>mcs) {
			hv[u]=v;
			mcs=cs;
		}
		s+=cs;
	}
	return s;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> n;
	for(int i=0; i<n-1; ++i) {
		cin >> ui >> vi, --ui, --vi;
		adj[ui].push_back(vi);
		adj[vi].push_back(ui);
	}
	memset(hv, -1, 4*n);
	dfs();
	for(int i=0, j=0; i<n; ++i) {
		if(i&&hv[p[i]]==i)
			continue;
		for(int k=i; k!=-1; k=hv[k]) {
			pr[k]=i;
			ap[k]=j++;
		}
	}
	cin >> m;
	for(int i=0; i<2*m; ++i) {
		cin >> ui >> vi, --ui, --vi;
		auto upd=[&](int l, int r) {
			for(l+=n, r+=n+1; l<r; ++l/=2, r/=2) {
				if(l&1)
					st[l].push_back(i);
				if(r&1)
					st[r-1].push_back(i);
			}
		};
		for(; pr[ui]!=pr[vi]; ui=p[pr[ui]]) {
			if(d[pr[ui]]<d[pr[vi]])
				swap(ui, vi);
			upd(ap[pr[ui]], ap[ui]);
		}
		if(d[ui]>d[vi])
			swap(ui, vi);
		upd(ap[ui]+1, ap[vi]);
	}
	ts.n=m;
	for(int i=1; i<2*n; ++i) {
		for(int j : st[i]) {
			if(pv[i]) {
				ts.imp(j, n(pv[i]));
				ts.imp(y(pv[i]), y(ts.n));
			}
			ts.imp(j, y(ts.n));
			pv[i]=ts.n++;
		}
		if(i<n)
			pv[2*i]=pv[2*i+1]=pv[i];
	}
	if(!ts.ac()) {
		cout << "NO";
		return 0;
	}
	cout << "YES\n";
	for(int i=0; i<m; ++i)
		cout << 2-ts.ans[i] << "\n";
}
