#include <bits/stdc++.h>
using namespace std;

const int mxN=2e5;
int n, q, ui, vi, dt, ds[mxN], de[mxN], lz[1<<19], cm;
vector<int> adj[mxN];
array<int, 2> st[1<<19];
map<array<int, 2>, int> mp;

void dfs(int u, int p=-1) {
	ds[u]=dt++;
	for(int i=0; i<adj[u].size()-1; ++i) {
		if(adj[u][i]==p)
			swap(adj[u][i], adj[u].back());
		dfs(adj[u][i], u);
	}
	de[u]=dt;
}

void cmb(int i) {
	st[i]=st[2*i];
	if(st[2*i+1][0]>st[i][0])
		st[i]=st[2*i+1];
	else if(st[2*i+1][0]==st[i][0])
		st[i][1]+=st[2*i+1][1];
}

void bld(int i=1, int l=0, int r=n-1) {
	if(l==r) {
		st[i]={0, 1};
		return;
	}
	int m=(l+r)/2;
	bld(2*i, l, m);
	bld(2*i+1, m+1, r);
	cmb(i);
}

void app(int i, int x) {
	st[i][0]+=x;
	lz[i]+=x;
}

void psh(int i) {
	app(2*i, lz[i]);
	app(2*i+1, lz[i]);
	lz[i]=0;
}

void upd(int l1, int r1, int x, int i=1, int l2=0, int r2=n-1) {
	if(l1<=l2&&r2<=r1) {
		app(i, x);
		return;
	}
	psh(i);
	int m2=(l2+r2)/2;
	if(l1<=m2)
		upd(l1, r1, x, 2*i, l2, m2);
	if(m2<r1)
		upd(l1, r1, x, 2*i+1, m2+1, r2);
	cmb(i);
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> q;
	for(int i=0; i<n-1; ++i) {
		cin >> ui >> vi, --ui, --vi;
		adj[ui].push_back(vi);
		adj[vi].push_back(ui);
	}
	adj[0].push_back(-1);
	dfs(0);
	bld();
	while(q--) {
		cin >> ui >> vi, --ui, --vi;
		if(ds[ui]>ds[vi])
			swap(ui, vi);
		int d=mp[{ui, vi}]?-1:1;
		if(ds[vi]<de[ui]) {
			upd(0, n-1, d);
			int lb=0, rb=adj[ui].size()-2;
			while(lb<=rb) {
				int mb=(lb+rb)/2;
				if(ds[adj[ui][mb]]<ds[vi])
					lb=mb+1;
				else
					rb=mb-1;
			}
			upd(ds[adj[ui][rb]], de[adj[ui][rb]]-1, -d);
		} else
			upd(ds[ui], de[ui]-1, d);
		upd(ds[vi], de[vi]-1, d);
		cm+=d;
		cout << (st[1][0]==cm?st[1][1]:0) << "\n";
		mp[{ui, vi}]^=1;
	}
}
