/*
	- https://github.com/mostafa-saad/MyCompetitiveProgramming/blob/master/Olympiad/IOI/official/2018/meetings-review.pdf
	- Just use a segment tree instead of the combination of data structures mentioned in the editorial
*/

#include "meetings.h"
#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int mxN=7.5e5;
int n, q;
array<int, 2> a[20][mxN];
vector<ll> ans;
vector<int> ta[mxN], ql, qr;
array<ll, 2> st[1<<21], lz[1<<21];

array<int, 2> lca(int l, int r) {
	int k=31-__builtin_clz(r-l+1);
	return max(a[k][l], a[k][r-(1<<k)+1]);
}

void app(int i, array<ll, 2> x, int l2, int r2) {
	if(x[0]) {
		st[i]={l2*x[0], r2*x[0]};
		lz[i]={x[0], 0};
	}
	st[i][0]+=x[1];
	st[i][1]+=x[1];
	lz[i][1]+=x[1];
}

void psh(int i, int l2, int m2, int r2) {
	app(2*i, lz[i], l2, m2);
	app(2*i+1, lz[i], m2+1, r2);
	lz[i]={};
}

void upd(int l1, int r1, array<ll, 2> x, bool f, int i=1, int l2=0, int r2=n-1) {
	if(l1<=l2&&r2<=r1) {
		if(f||r2*x[0]+x[1]<st[i][1]) {
			app(i, x, l2, r2);
			return;
		} else if(l2*x[0]+x[1]>=st[i][0])
			return;
	}
	int m2=(l2+r2)/2;
	psh(i, l2, m2, r2);
	if(l1<=m2)
		upd(l1, r1, x, f, 2*i, l2, m2);
	if(m2<r1)
		upd(l1, r1, x, f, 2*i+1, m2+1, r2);
	st[i]={st[2*i][0], st[2*i+1][1]};
}

ll qry(int l1, int i=1, int l2=0, int r2=n-1) {
	if(l2==r2)
		return st[i][0];
	int m2=(l2+r2)/2;
	psh(i, l2, m2, r2);
	return l1<=m2?qry(l1, 2*i, l2, m2):qry(l1, 2*i+1, m2+1, r2);
}

int dfs(int l=0, int r=n-1) {
	if(l>r)
		return -1;
	int u=abs(lca(l, r)[1]), lc=dfs(l, u-1), rc=dfs(u+1, r);
	upd(u, u, {1, -u}, 1);
	for(int i : ta[u])
		ans[i]=min(qry(qr[i])+(u-ql[i]+1ll)*a[0][u][0], ans[i]);
	upd(u, r, {0, (u-l+1ll)*a[0][u][0]}, 1);
	upd(u, r, {a[0][u][0], (~lc?qry(u-1):0)-(u-1ll)*a[0][u][0]}, 0);
	return u;
}

vector<ll> minimum_costs(vector<int> h, vector<int> l, vector<int> r) {
	n=h.size(), q=l.size();
	for(int i=0; i<n; ++i)
		a[0][i]={h[i], i};
	for(int k=1; k<20; ++k)
		for(int i=0; i<=n-(1<<k); ++i)
			a[k][i]=max(a[k-1][i], a[k-1][i+(1<<k-1)]);
	ql=l, qr=r;
	ans=vector<ll>(q, 1e18);
	for(int i=0; i<q; ++i) {
		int w=lca(l[i], r[i])[1];
		ta[w].push_back(i);
	}
	dfs();
	reverse(ta, ta+n);
	for(int i=0; i<q; ++i)
		tie(ql[i], qr[i])=make_pair(n-1-qr[i], n-1-ql[i]);
	for(int i=0; i<n; ++i)
		a[0][i]={h[n-1-i], -i};
	for(int k=1; k<20; ++k)
		for(int i=0; i<=n-(1<<k); ++i)
			a[k][i]=max(a[k-1][i], a[k-1][i+(1<<k-1)]);
	dfs();
	return ans;
}
