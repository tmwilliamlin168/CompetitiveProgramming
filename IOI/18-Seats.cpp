#include "seats.h"
#include <bits/stdc++.h>
using namespace std;

#define ar array

int h, w, lz[1<<21], b[1000001];
vector<int> r, c;
vector<vector<int>> a;
ar<int, 2> st[1<<21];

void cmb(int i) {
	st[i]={min(st[2*i][0], st[2*i+1][0])};
	st[i][1]=(st[2*i][0]>st[i][0]?0:st[2*i][1])+(st[2*i+1][0]>st[i][0]?0:st[2*i+1][1]);
}

void bld(int i=1, int l2=0, int r2=h*w-1) {
	if(l2==r2) {
		st[i]={b[l2], 1};
		return;
	}
	int m2=(l2+r2)/2;
	bld(2*i, l2, m2);
	bld(2*i+1, m2+1, r2);
	cmb(i);
}

void app(int i, int x) {
	st[i][0]+=x;
	lz[i]+=x;
}

void upd(int l1, int r1, int x, int i=1, int l2=0, int r2=h*w-1) {
	if(!st[1][1]) {
		b[l1]+=x;
		b[r1+1]-=x;
		return;
	}
	if(l1<=l2&&r2<=r1) {
		app(i, x);
		return;
	}
	int m2=(l2+r2)/2;
	app(2*i, lz[i]);
	app(2*i+1, lz[i]);
	lz[i]=0;
	if(l1<=m2)
		upd(l1, r1, x, 2*i, l2, m2);
	if(m2<r1)
		upd(l1, r1, x, 2*i+1, m2+1, r2);
	cmb(i);
}

void cs(int x, int y, int z) {
	vector<int> v;
	for(int d=!x-1; d<(x<h); ++d)
		for(int e=!y-1; e<(y<w); ++e)
			v.push_back(a[x+d][y+e]);
	sort(v.begin(), v.end());
	upd(v[0], (v.size()>1?v[1]:h*w)-1, z);
	if(v.size()>2)
		upd(v[2], v[3]-1, z);
}

void give_initial_chart(int h, int w, vector<int> r, vector<int> c) {
	::h=h;
	::w=w;
	::r=r;
	::c=c;
	a=vector<vector<int>>(h, vector<int>(w));
	for(int i=0; i<h*w; ++i)
		a[r[i]][c[i]]=i;
	for(int i=0; i<=h; ++i)
		for(int j=0; j<=w; ++j)
			cs(i, j, 1);
	for(int i=0; i<h*w; ++i)
		b[i+1]+=b[i];
	bld();
}

int swap_seats(int x, int y) {
	vector<ar<int, 2>> v;
	for(int i : {x, y})
		for(int d : {0, 1})
			for(int e : {0, 1})
				v.push_back({r[i]+d, c[i]+e});
	sort(v.begin(), v.end());
	v.resize(unique(v.begin(), v.end())-v.begin());
	for(auto a : v)
		cs(a[0], a[1], -1);
	swap(a[r[x]][c[x]], a[r[y]][c[y]]);
	swap(r[x], r[y]);
	swap(c[x], c[y]);
	for(auto a : v)
		cs(a[0], a[1], 1);
	return st[1][1];
}
