#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int mxN=1e5;
int n, q, dt, ds[mxN], de[mxN];
vector<int> adj[mxN];
set<array<int, 2>> rg[mxN];
ll st[1<<18], lz[1<<18];

void app(int i, int l1, int r1, ll x) {
	st[i]+=x*(r1-l1+1);
	lz[i]+=x;
}

void psh(int i, int l2, int m2, int r2) {
	app(2*i, l2, m2, lz[i]);
	app(2*i+1, m2+1, r2, lz[i]);
	lz[i]=0;
}

void upd(int l1, int r1, ll x, int i=1, int l2=0, int r2=n-1) {
	if(l1<=l2&&r2<=r1) {
		app(i, l2, r2, x);
		return;
	}
	int m2=(l2+r2)/2;
	psh(i, l2, m2, r2);
	if(l1<=m2)
		upd(l1, r1, x, 2*i, l2, m2);
	if(m2<r1)
		upd(l1, r1, x, 2*i+1, m2+1, r2);
	st[i]=st[2*i]+st[2*i+1];
}

ll qry(int l1, int r1, int i=1, int l2=0, int r2=n-1) {
	if(l1<=l2&&r2<=r1)
		return st[i];
	int m2=(l2+r2)/2;
	psh(i, l2, m2, r2);
	return (l1<=m2?qry(l1, r1, 2*i, l2, m2):0)+(m2<r1?qry(l1, r1, 2*i+1, m2+1, r2):0);
}

void dfs(int u=0, int p=-1) {
	ds[u]=dt++;
	for(int v : adj[u])
		if(v^p)
			dfs(v, u);
	de[u]=dt;
}

int main() {
	ifstream cin("snowcow.in");
	ofstream cout("snowcow.out");
	
	cin >> n >> q;
	for(int i=1, u, v; i<n; ++i) {
		cin >> u >> v, --u, --v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	dfs();
	for(int qt, x, c; q--; ) {
		cin >> qt >> x, --x;
		if(qt<2) {
			cin >> c, --c;
			auto it=rg[c].upper_bound({ds[x], 0});
			if(it!=rg[c].begin()) {
				--it;
				if((*it)[1]>ds[x])
					continue;
			}
			it=rg[c].lower_bound({ds[x], 0});
			while(it!=rg[c].end()&&(*it)[0]<de[x]) {
				upd((*it)[0], (*it)[1]-1, -1);
				it=rg[c].erase(it);
			}
			rg[c].insert({ds[x], de[x]});
			upd(ds[x], de[x]-1, 1);
		} else
			cout << qry(ds[x], de[x]-1) << "\n";
	}
}
