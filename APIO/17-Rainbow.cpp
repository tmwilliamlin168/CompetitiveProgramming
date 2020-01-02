/*
	- Use Euler's formula E-V+C to count the number of faces
	- We just need to be able to find the number of vertices and edges in a given 2d range
	- To answer 2d range sum queries online, we will use a persistent segtree
*/

#include "rainbow.h"
#include <bits/stdc++.h>
using namespace std;

const int mxN=2e5, mxSTS=(6e5+9)*19+1;
int sts=1, st[mxSTS], lc[mxSTS], rc[mxSTS];

struct dat {
	set<int> ta[mxN+1];
	int rt[mxN+2];
	void a(array<int, 2> a) {
		ta[a[0]].insert(a[1]);
	}
	void bld() {
		for(int i=0; i<=mxN; ++i) {
			rt[i+1]=rt[i];
			for(int j : ta[i])
				upd(j, rt[i+1]);
		}
	}
	void upd(int l1, int &i, int l2=0, int r2=mxN) {
		st[sts]=st[i]+1;
		lc[sts]=lc[i];
		rc[sts]=rc[i];
		i=sts++;
		if(l2==r2)
			return;
		int m2=(l2+r2)/2;
		if(l1<=m2)
			upd(l1, lc[i], l2, m2);
		else
			upd(l1, rc[i], m2+1, r2);
	}
	int qry(int l1, int r1, int l2, int r2) {
		return l2>r2?0:qry(l2, r2, rt[r1+1], 0, mxN)-qry(l2, r2, rt[l1], 0, mxN);
	}
	int qry(int l1, int r1, int i, int l2, int r2) {
		if(l1<=l2&&r2<=r1)
			return st[i];
		int m2=(l2+r2)/2;
		return (l1<=m2?qry(l1, r1, lc[i], l2, m2):0)+(m2<r1?qry(l1, r1, rc[i], m2+1, r2):0);
	}
} sv, ser, sec, ss;

void init(int r, int c, int sr, int sc, int m, char *s) {
	set<array<int, 2>> cs{{--sr, --sc}};
	for(int i=0; i<m; ++i) {
		if(s[i]=='N')
			--sr;
		else if(s[i]=='S')
			++sr;
		else if(s[i]=='E')
			++sc;
		else
			--sc;
		cs.insert({sr, sc});
	}
	for(auto a : cs) {
		sv.a(a);
		sv.a({a[0], a[1]+1});
		sv.a({a[0]+1, a[1]});
		sv.a({a[0]+1, a[1]+1});
		ser.a(a);
		ser.a({a[0]+1, a[1]});
		sec.a(a);
		sec.a({a[0], a[1]+1});
		ss.a(a);
	}
	sv.bld();
	ser.bld();
	sec.bld();
	ss.bld();
}

int colour(int ar, int ac, int br, int bc) {
	--ar, --ac, --br, --bc;
	int e=2*(br-ar+bc-ac+2)+ser.qry(ar+1, br, ac, bc)+sec.qry(ar, br, ac+1, bc);
	int v=2*(br-ar+bc-ac+2)+sv.qry(ar+1, br, ac+1, bc);
	int c=!sv.qry(ar+1, br, ac+1, bc)||ser.qry(ar+1, br, ac, bc)-ser.qry(ar+1, br, ac+1, bc-1)||sec.qry(ar, br, ac+1, bc)-sec.qry(ar+1, br-1, ac+1, bc)?1:2;
	int s=ss.qry(ar, br, ac, bc);
	return e-v+c-s;
}
