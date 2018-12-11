#include <bits/stdc++.h>
using namespace std;

#define ar array

const int mxN=2e5;
int n, a[mxN], p[mxN], ds[mxN], de[mxN], dti, q, qt, qi, qj;
vector<int> adj[mxN];
ar<int, 2> dt[19][2*mxN-1], st[1<<19];

void dfs(int u=0, int d=0) {
	ds[u]=dti;
	dt[0][dti++]={d, u};
	for(int v : adj[u]) {
		dfs(v, d+1);
		dt[0][dti++]={d, u};
	}
	de[u]=dti;
}

void cmb(ar<int, 2> &a, ar<int, 2> b) {
	auto lca=[&](int u, int v) {
		if((u=ds[u])>(v=ds[v]))
			swap(u, v);
		int k=31-__builtin_clz(v-u+1);
		return min(dt[k][u], dt[k][v-(1<<k)+1])[1];
	};
	auto d=[&](int u, int v, int w) {
		int l=lca(u, v);
		return ds[l]<=ds[w]&&ds[w]<de[l]&&(ds[w]<=ds[u]&&ds[u]<de[w]||ds[w]<=ds[v]&&ds[v]<de[w]);
	};
	auto c=[&](int b) {
		if(b==-1||a[0]==-1)
			a[0]=a[1]=-1;
		else if(d(a[0], b, a[1]))
			a[1]=b;
		else if(d(a[1], b, a[0]))
			a[0]=b;
		else if(!d(a[0], a[1], b))
			a[0]=a[1]=-1;
	};
	c(b[0]);
	c(b[1]);
}

void upd(int l1, ar<int, 2> x, int i=1, int l2=0, int r2=n-1) {
	if(l2==r2) {
		st[i]=x;
		return;
	}
	int m2=(l2+r2)/2;
	if(l1<=m2)
		upd(l1, x, 2*i, l2, m2);
	else
		upd(l1, x, 2*i+1, m2+1, r2);
	st[i]=st[2*i];
	cmb(st[i], st[2*i+1]);
}

int qry(int i=1, int l2=0, int r2=n-1, ar<int, 2> p={}) {
	ar<int, 2> a=st[i];
	if(l2)
		cmb(a, p);
	if(a[0]!=-1)
		return r2+1;
	if(l2==r2)
		return l2;
	int m2=(l2+r2)/2;
	a=st[2*i];
	if(l2)
		cmb(a, p);
	return a[0]==-1?qry(2*i, l2, m2, p):qry(2*i+1, m2+1, r2, a);
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n;
	for(int i=0; i<n; ++i)
		cin >> a[i];
	for(int i=1; i<n; ++i) {
		cin >> p[i], --p[i];
		adj[p[i]].push_back(i);
	}
	dfs();
	for(int i=1; i<19; ++i)
		for(int j=0; j<2*n-(1<<i); ++j)
			dt[i][j]=min(dt[i-1][j], dt[i-1][j+(1<<i-1)]);
	for(int i=0; i<n; ++i)
		upd(a[i], {i, i});
	cin >> q;
	while(q--) {
		cin >> qt;
		if(qt==1) {
			cin >> qi >> qj, --qi, --qj;
			swap(a[qi], a[qj]);
			upd(a[qi], {qi, qi});
			upd(a[qj], {qj, qj});
		} else
			cout << qry() << "\n";
	}
}
