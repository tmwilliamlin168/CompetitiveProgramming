/*
	- This is an O(nlogn) solution, unfortunately much more complicated than O(nlog^2n) ones :(
*/

#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int mxN=1e5;
int n, st[mxN], ist[mxN], en[mxN], dt;
ll m, c[mxN], l[mxN], ans;
vector<int> adj[mxN];

struct node {
	ll s1;
	int s2, m1, m2;
} sg[1<<18];

void dfs1(int u) {
	ist[st[u]=dt++]=u;
	for(int v : adj[u])
		dfs1(v);
	en[u]=dt;
}

inline void mrg(node &lc, node &rc, node &u) {
	u.s1=lc.s1+rc.s1;
	u.s2=lc.s2+rc.s2;
	u.m1=max(lc.m1, rc.m1);
}

void bld(int i=1, int l=0, int r=n-1) {
	if(l<r) {
		int m=(l+r)/2;
		bld(2*i, l, m);
		bld(2*i+1, m+1, r);
		mrg(sg[2*i], sg[2*i+1], sg[i]);
	} else {
		sg[i].s1=sg[i].m1=c[ist[l]];
		sg[i].s2=1;
	}
}

void dmx1(int l1, int r1, int i=1, int l2=0, int r2=n-1) {
	if(l1<=l2&&r2<=r1) {
		sg[i].m2=sg[i].m1;
		return;
	}
	int m=(l2+r2)/2;
	if(l1<=m)
		dmx1(l1, r1, 2*i, l2, m);
	else
		sg[2*i].m2=0;
	if(m<r1)
		dmx1(l1, r1, 2*i+1, m+1, r2);
	else
		sg[2*i+1].m2=0;
	sg[i].m2=max(sg[2*i].m2, sg[2*i+1].m2);
}

void dmx2(int l1, int r1, int i=1, int l2=0, int r2=n-1) {
	if(l2==r2) {
		sg[i].s1=sg[i].s2=sg[i].m1=0;
		return;
	}
	int m=(l2+r2)/2;
	if(l1<=l2&&r2<=r1?sg[2*i].m1>sg[2*i+1].m1:sg[2*i].m2>sg[2*i+1].m2)
		dmx2(l1, r1, 2*i, l2, m);
	else
		dmx2(l1, r1, 2*i+1, m+1, r2);
	mrg(sg[2*i], sg[2*i+1], sg[i]);
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
	while(qry(st[u], en[u]-1).s1>m)
		dmx1(st[u], en[u]-1), dmx2(st[u], en[u]-1);
	ans=max(l[u]*qry(st[u], en[u]-1).s2, ans);
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
