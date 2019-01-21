#include <bits/stdc++.h>
using namespace std;

const int mxN=2.5e5;
int n, m, ai, bi, p[mxN], d[mxN], hv[mxN], prt[mxN], ap[mxN], st[1<<19];
vector<int> adj[mxN];
bool lz[1<<19];

int dfs(int u) {
	int s=1, mcs=0;
	for(int v : adj[u]) {
		if(v==p[u])
			continue;
		p[v]=u;
		d[v]=d[u]+1;
		int cs=dfs(v);
		if(cs>mcs) {
			hv[u]=v;
			mcs=cs;
		}
		s+=cs;
	}
	return s;
}

void app(int i, bool b, int sl) {
	if(b)
		st[i]=sl-st[i];
	lz[i]^=b;
}

void upd(int l1, int r1, int i=1, int l2=0, int r2=n-1) {
	if(l1<=l2&&r2<=r1) {
		app(i, 1, r2-l2+1);
		return;
	}
	int m2=(l2+r2)/2;
	app(2*i, lz[i], m2-l2+1);
	app(2*i+1, lz[i], r2-m2);
	lz[i]=0;
	if(l1<=m2)
		upd(l1, r1, 2*i, l2, m2);
	if(m2<r1)
		upd(l1, r1, 2*i+1, m2+1, r2);
	st[i]=st[2*i]+st[2*i+1];
}

void pp(int u) {
	for(; u!=-1; u=p[prt[u]])
		upd(ap[prt[u]], ap[u]);
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n;
	for(int i=0; i<n-1; ++i) {
		cin >> ai >> bi, --ai, --bi;
		adj[ai].push_back(bi);
		adj[bi].push_back(ai);
	}
	memset(hv, -1, 4*n);
	p[0]=-1;
	dfs(0);
	for(int i=0, j=0; i<n; ++i) {
		if(!i||hv[p[i]]!=i) {
			for(int k=i; k!=-1; k=hv[k]) {
				prt[k]=i;
				ap[k]=j++;
			}
		}
	}
	cin >> m;
	while(m--) {
		cin >> ai >> bi, --ai, --bi;
		pp(ai);
		pp(bi);
		cout << st[1] << "\n";
	}
}
