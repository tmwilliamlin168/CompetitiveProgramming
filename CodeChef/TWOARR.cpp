#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int mxN=2e5;
int n, q;
mt19937 mg(69);

template<size_t S>
struct treap {
	int n=1, lc[S+1], rc[S+1], a[S+1], s0[S+1], rt[2];
	ll s1[S+1];
	int nn(int b) {
		a[n]=b;
		return cmb(n++);
	}
	int cpy(int u) {
		a[n]=a[u];
		lc[n]=lc[u];
		rc[n]=rc[u];
		return cmb(n++);
	}
	int cmb(int u) {
		s0[u]=s0[lc[u]]+1+s0[rc[u]];
		s1[u]=s1[lc[u]]+a[u]+s1[rc[u]];
		return u;
	}
	int mrg(int u, int v) {
		if(!u||!v)
			return u^v;
		if(mg()%(s0[u]+s0[v])<s0[u]) {
			u=cpy(u);
			rc[u]=mrg(rc[u], v);
			return cmb(u);
		} else {
			v=cpy(v);
			lc[v]=mrg(u, lc[v]);
			return cmb(v);
		}
	}
	array<int, 2> spl(int u, int k) {
		if(!u)
			return {};
		u=cpy(u);
		if(k<=s0[lc[u]]) {
			array<int, 2> a=spl(lc[u], k);
			lc[u]=a[1];
			return {a[0], cmb(u)};
		} else {
			array<int, 2> a=spl(rc[u], k-s0[lc[u]]-1);
			rc[u]=a[0];
			return {cmb(u), a[1]};
		}
	}
	void upd1(int k, int x) {
		array<int, 2> l=spl(rt[1], k), r=spl(l[1], 1);
		r[0]=cpy(r[0]);
		a[r[0]]=x;
		rt[1]=mrg(l[0], mrg(cmb(r[0]), r[1]));
	}
	void upd2(int l, int r, int x) {
		array<int, 2> l1=spl(rt[0], l), r1=spl(l1[1], r-l), l2=spl(rt[1], x), r2=spl(l2[1], r-l);
		rt[0]=mrg(l1[0], mrg(r2[0], r1[1]));
	}
	ll qry(int l, int r) {
		return s1[spl(spl(rt[0], l)[1], r-l)[0]];
	}
};
treap<40000000> tr;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> n >> q;
	for(int j : {0, 1})
		for(int i=0, a; i<n; ++i)
			cin >> a, tr.rt[j]=tr.mrg(tr.rt[j], tr.nn(a));
	for(int a, b, c, d; q--; ) {
		cin >> a >> b >> c;
		if(a==1)
			tr.upd1(b-1, c);
		else if(a==2) {
			cin >> d;
			tr.upd2(b-1, c, d-1);
		} else
			cout << tr.qry(b-1, c) << "\n";
	}
}
