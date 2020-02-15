#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int mxQ=1e5;
mt19937 mg(69);
int q;

template<size_t S>
struct treap {
	int rt, lc[S+1], rc[S+1], k[S+1], s[S+1], lk[S+1], rk[S+1], rs[S+1];
	ll pr[S+1], ts[S+1], ms[S+1];
	int cmb(int u) {
		lk[u]=lc[u]?lk[lc[u]]:k[u];
		rk[u]=rc[u]?rk[rc[u]]:k[u];
		rs[u]=rc[u]?rs[rc[u]]:s[u];
		ts[u]=ms[u]=0;
		if(lc[u]) {
			ts[u]=ts[lc[u]]+(ll)(k[u]-rk[lc[u]])*rs[lc[u]];
			ms[u]=min({ms[lc[u]], ts[u], 0ll});
		}
		if(rc[u]) {
			ts[u]+=(ll)(lk[rc[u]]-k[u])*s[u];
			ms[u]=min(ts[u]+ms[rc[u]], ms[u]);
			ts[u]+=ts[rc[u]];
		}
		return u;
	}
	int mrg(int u, int v) {
		if(!u||!v)
			return u^v;
		if(pr[u]>pr[v]) {
			rc[u]=mrg(rc[u], v);
			return cmb(u);
		} else {
			lc[v]=mrg(u, lc[v]);
			return cmb(v);
		}
	}
	array<int, 2> spl(int u, int x) {
		if(!u)
			return {};
		if(k[u]<x) {
			array<int, 2> a=spl(rc[u], x);
			rc[u]=a[0];
			return {cmb(u), a[1]};
		} else {
			array<int, 2> a=spl(lc[u], x);
			lc[u]=a[1];
			return {a[0], cmb(u)};
		}
	}
	int ins(int u, int v, int ki, int si) {
		k[v]=ki;
		s[v]=si;
		pr[v]=mg();
		array<int, 2> a=spl(u, ki), b=spl(a[1], ki+1);
		return mrg(a[0], mrg(cmb(v), b[1]));
	}
	int del(int u, int ki) {
		array<int, 2> a=spl(u, ki), b=spl(a[1], ki+1);
		return mrg(a[0], b[1]);
	}
	void qry(int l, int r, ll d, int v) {
		if(!d) {
			cout << l << "\n";
			return;
		}
		array<int, 2> a=spl(rt, l), b=spl(a[1], r);
		v=b[0]=ins(b[0], v, r, 0);
		if(d+ms[v]<=0) {
			while(1) {
				if(lc[v]) {
					if(d+ms[lc[v]]<=0) {
						v=lc[v];
						continue;
					}
					d+=ts[lc[v]];
					if(d+(ll)(k[v]-rk[lc[v]])*rs[lc[v]]<=0) {
						cout << rk[lc[v]]+(long double)-d/rs[lc[v]] << "\n";
						break;
					}
					d+=(ll)(k[v]-rk[lc[v]])*rs[lc[v]];
				}
				if(d+(ll)(lk[rc[v]]-k[v])*s[v]<=0) {
					cout << k[v]+(long double)-d/s[v] << "\n";
					break;
				}
				d+=(ll)(lk[rc[v]]-k[v])*s[v];
				v=rc[v];
			}
		} else
			cout << "-1\n";
		b[0]=del(b[0], r);
		rt=mrg(a[0], mrg(b[0], b[1]));
	}
};
treap<mxQ> tr;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> q;
	cout << setprecision(9);
	for(int a, b, c, d; q--; ) {
		cin >> a >> b;
		if(a==1) {
			cin >> c;
			tr.rt=tr.ins(tr.rt, q+1, b, c);
		} else if(a==3) {
			cin >> c >> d;
			tr.qry(b, c, d, q+1);
		} else
			tr.rt=tr.del(tr.rt, b);
	}
}
