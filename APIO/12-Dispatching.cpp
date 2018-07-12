#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pii pair<int, int>
#define fi first
#define se second

const int mxN=1e5;
int n, st[mxN], ist[mxN], en[mxN], dt;
ll m, c[mxN], l[mxN], ans;
vector<int> adj[mxN];

struct node {
	ll s1;
	int s2;
	pii m;
} sg[1<<18];

void dfs1(int u) {
	ist[st[u]=dt++]=u;
	for(int v : adj[u])
		dfs1(v);
	en[u]=dt;
}

inline void mrg(node &lc, node &rc, node &u) {
	u.s1=lc.s1+rc.s1, u.s2=lc.s2+rc.s2;
	u.m=max(lc.m, rc.m);
}

void bld(int i=1, int l=0, int r=n-1) {
	if(l<r) {
		int m=(l+r)/2;
		bld(2*i, l, m);
		bld(2*i+1, m+1, r);
		mrg(sg[2*i], sg[2*i+1], sg[i]);
	} else {
		sg[i].s1=c[ist[l]], sg[i].s2=1;
		sg[i].m={c[ist[l]], l};
	}
}

void upd(int l1, int x, int i=1, int l2=0, int r2=n-1) {
	if(l2<r2) {
		int m2=(l2+r2)/2;
		if(l1<=m2)
			upd(l1, x, 2*i, l2, m2);
		else
			upd(l1, x, 2*i+1, m2+1, r2);
		mrg(sg[2*i], sg[2*i+1], sg[i]);
	} else {
		sg[i].s1=sg[i].s2=x;
		sg[i].m.fi=x;
	}
}

node qry(int l1, int r1, int i=1, int l2=0, int r2=n-1) {
	if(l1<=l2&&r2<=r1)
		return sg[i];
	int m=(l2+r2)/2;
	if(l1<=m&&m<r1) {
		node lc=qry(l1, r1, 2*i, l2, m), rc=qry(l1, r1, 2*i+1, m+1, r2), rn;
		mrg(lc, rc, rn);
		return rn;
	}
	return l1<=m?qry(l1, r1, 2*i, l2, m):qry(l1, r1, 2*i+1, m+1, r2);
}

void dfs2(int u) {
	for(int v : adj[u])
		dfs2(v);
	node a=qry(st[u], en[u]-1);
	while(a.s1>m) {
		upd(a.m.se, 0);
		a=qry(st[u], en[u]-1);
	}
	ans=max(l[u]*a.s2, ans);
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> m;
	for(int i=0; i<n; ++i) {
		int bi;
		cin >> bi >> c[i] >> l[i];
		if(bi)
			adj[bi-1].push_back(i);
	}
	dfs1(0);
	bld();
	dfs2(0);
	cout << ans;
}
