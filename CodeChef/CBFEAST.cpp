#include <bits/stdc++.h>
using namespace std;

const int mxN=2e5, mxSTS=2*31*mxN+1;
int n, k, ans, qt, c, d, rt=1, sts=2, lc[mxSTS], rc[mxSTS];

struct dat {
	int t, mp, ms, m;
	__attribute__((always_inline)) dat operator +(const dat &o) const {
		return {t+o.t, max(mp, t+o.mp), max(o.ms, o.t+ms), max({m, o.m, ms+o.mp})};
	}
} lz1[mxSTS], lz2[mxSTS];

void app(int &i, dat a, bool b) {
	if(!i)
		i=sts++;
	if(b)
		lz1[i]=a+lz1[i];
	else
		lz2[i]=lz2[i]+a;
}

void psh(int i, bool b) {
	if(b) {
		app(lc[i], lz1[i], 1);
		app(rc[i], lz1[i], 1);
		lz1[i]={};
	} else {
		app(lc[i], lz2[i], 0);
		app(rc[i], lz2[i], 0);
		lz2[i]={};
	}
}

void upd(int l1, int r1, dat a, bool b, int i=rt, int l2=1, int r2=1e9) {
	if(l1<=l2&&r2<=r1) {
		app(i, a, b);
		return;
	}
	psh(i, b);
	int m2=(l2+r2)/2;
	if(l1<=m2)
		upd(l1, r1, a, b, lc[i], l2, m2);
	if(m2<r1)
		upd(l1, r1, a, b, rc[i], m2+1, r2);
}

int qry(int l1, int i=rt, int l2=1, int r2=1e9) {
	if(l2==r2)
		return (lz1[i]+lz2[i]).m;
	psh(i, 0);
	psh(i, 1);
	int m2=(l2+r2)/2;
	return l1<=m2?qry(l1, lc[i], l2, m2):qry(l1, rc[i], m2+1, r2);
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> k;
	while(n--) {
		cin >> qt >> c, c^=ans;
		if(qt==1) {
			cin >> d;
			upd(c-k, c+k, {d, d, d, d}, 0);
		} else if(qt==2) {
			cin >> d;
			upd(c-k, c+k, {d, d, d, d}, 1);
		} else
			cout << (ans=qry(c)) << "\n";
	}
}
