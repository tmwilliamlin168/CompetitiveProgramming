#include <bits/stdc++.h>
using namespace std;

const int mxN=1e5;
int n, q, rt, nl, p[mxN], hv[mxN], prt[mxN], ap[mxN], st[1<<18];
vector<int> adj[mxN];
bool il[mxN], lz[1<<18];

int dfs(int u, int pu=-1) {
	p[u]=pu;
	int s=0;
	for(int v : adj[u]) {
		if(v==pu)
			continue;
		int cs=dfs(v, u);
		if(s<cs)
			hv[u]=v;
		s+=cs;
	}
	return s+1;
}

void app(int i, int x, int l2, int r2) {
	if(!x)
		return;
	st[i]=r2-l2+1-st[i];
	lz[i]^=1;
}

void upd(int l1, int r1, int i=1, int l2=0, int r2=n-1) {
	if(l1<=l2&&r2<=r1) {
		app(i, 1, l2, r2);
		return;
	}
	int m2=(l2+r2)/2;
	app(2*i, lz[i], l2, m2);
	app(2*i+1, lz[i], m2+1, r2);
	lz[i]=0;
	if(l1<=m2)
		upd(l1, r1, 2*i, l2, m2);
	if(m2<r1)
		upd(l1, r1, 2*i+1, m2+1, r2);
	st[i]=st[2*i]+st[2*i+1];
}

void lu(int u) {
	for(; ~u; u=p[prt[u]])
		upd(ap[prt[u]], ap[u]);
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> q;
	for(int i=1, u, v; i<n; ++i) {
		cin >> u >> v, --u, --v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	for(int i=0; i<n; ++i) {
		il[i]=adj[i].size()<2;
		nl+=il[i];
	}
	for(; il[rt]; ++rt);
	memset(hv, -1, 4*n);
	dfs(rt);
	for(int i=0, k=0; i<n; ++i) {
		if(~p[i]&&hv[p[i]]==i)
			continue;
		for(int j=i; ~j; j=hv[j]) {
			prt[j]=i;
			ap[j]=k++;
		}
	}
	lz[1]=1;
	for(int i=0; i<n; ++i)
		if(il[i])
			lu(i);
	for(int d; q--; ) {
		cin >> d;
		vector<int> v1, v2;
		for(int i=0, a; i<d; ++i) {
			cin >> a, --a;
			if(il[a]) {
				il[a]=0;
				v2.push_back(a);
			} else {
				lu(a);
				v1.push_back(a);
			}
		}
		cout << (nl+v1.size()&1?-1:n-2+d+st[1]) << "\n";
		for(int a : v1)
			lu(a);
		for(int a : v2)
			il[a]=1;
	}
}
