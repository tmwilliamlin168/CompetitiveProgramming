#include "teams.h"
#include <bits/stdc++.h>
using namespace std;

const int mxN=5e5, mxSTS=1+20*mxN;
int n, rt[mxN+1], sts=1, st[mxSTS], lc[mxSTS], rc[mxSTS];
array<int, 2> e[mxN];
vector<int> c[mxN];

void upd(int &i, int l1, int l2=0, int r2=n-1) {
	st[sts]=st[i];
	lc[sts]=lc[i];
	rc[sts]=rc[i];
	i=sts++;
	++st[i];
	if(l2==r2)
		return;
	int m2=(l2+r2)/2;
	if(l1<=m2)
		upd(lc[i], l1, l2, m2);
	else
		upd(rc[i], l1, m2+1, r2);
}

int qry(int i, int l1, int r1, int l2=0, int r2=n-1) {
	if(l1>r1)
		return 0;
	if(l1<=l2&&r2<=r1)
		return st[i];
	int m2=(l2+r2)/2;
	return (l1<=m2?qry(lc[i], l1, r1, l2, m2):0)+(m2<r1?qry(rc[i], l1, r1, m2+1, r2):0);
}

int bs(int i, int j, int x, int l2=0, int r2=n-1) {
	if(l2==r2)
		return l2;
	int m2=(l2+r2)/2;
	return st[lc[i]]-st[lc[j]]<x?bs(rc[i], rc[j], x-st[lc[i]]+st[lc[j]], m2+1, r2):bs(lc[i], lc[j], x, l2, m2);
}

void init(int N, int *a, int *b) {
	n=N;
	for(int i=0; i<n; ++i)
		e[i]={b[i], i};
	sort(e, e+n);
	for(int i=0; i<n; ++i)
		c[a[e[i][1]]-1].push_back(i);
	for(int i=0; i<n; ++i) {
		rt[i+1]=rt[i];
		for(int d : c[i])
			upd(rt[i+1], d);
	}
}

int can(int m, int *k) {
	sort(k, k+m);
	vector<array<int, 2>> s{{0, n-1}};
	for(int i=0; i<m; ++i) {
		int o=k[i], t=lower_bound(e, e+n, array<int, 2>{k[i], 0})-e;
		for(; s.size()&&s.back()[1]<t; s.pop_back());
		for(; s.size(); s.pop_back()) {
			int x=qry(rt[k[i]], t, s.back()[1])-qry(rt[s.back()[0]], t, s.back()[1]);
			if(x>=o)
				break;
			o-=x;
			t=s.back()[1]+1;
		}
		if(!s.size())
			return 0;
		s.push_back({k[i], bs(rt[k[i]], rt[s.back()[0]], o+qry(rt[k[i]], 0, t-1)-qry(rt[s.back()[0]], 0, t-1))});
	}
	return 1;
}
