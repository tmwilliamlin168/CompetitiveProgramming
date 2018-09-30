#include <bits/stdc++.h>
using namespace std;

const int mxN=1e5, mxSTS=18*mxN+1;
int t, n, q, a[mxN], b[mxN], xi, yi, ci, st[1<<18], lz[1<<18], lc[mxSTS], rc[mxSTS], d[mxSTS], sts;
unordered_map<int, int> pos;

void bld(int i=1, int l2=0, int r2=n-1) {
	lz[i]=-1;
	if(l2==r2) {
		st[i]=a[l2]==b[l2];
		return;
	}
	int m2=(l2+r2)/2;
	bld(2*i, l2, m2);
	bld(2*i+1, m2+1, r2);
	st[i]=st[2*i]+st[2*i+1];
}

void app(int i, int x, int l2, int r2) {
	lz[i]=x;
	st[i]=d[x];
}

void upd1(int l1, int r1, int x, int i=1, int l2=0, int r2=n-1) {
	if(l1<=l2&&r2<=r1) {
		app(i, x, l2, r2);
		return;
	}
	int m2=(l2+r2)/2;
	if(lz[i]!=-1) {
		app(2*i, lc[lz[i]], l2, m2);
		app(2*i+1, rc[lz[i]], m2+1, r2);
		lz[i]=-1;
	}
	if(l1<=m2)
		upd1(l1, r1, lc[x], 2*i, l2, m2);
	if(m2<r1)
		upd1(l1, r1, rc[x], 2*i+1, m2+1, r2);
	st[i]=st[2*i]+st[2*i+1];
}

void upd2(int &i, int l1, int l2=0, int r2=n-1) {
	if(!i) {
		lc[sts]=rc[sts]=d[sts]=0;
		i=sts++;
	}
	++d[i];
	if(l2==r2)
		return;
	int m2=(l2+r2)/2;
	if(l1<=m2)
		upd2(lc[i], l1, l2, m2);
	else
		upd2(rc[i], l1, m2+1, r2);
}

void solve() {
	cin >> n >> q;
	for(int i=0; i<n; ++i)
		cin >> a[i];
	sts=1;
	for(int i=0; i<n; ++i) {
		cin >> b[i];
		upd2(pos[b[i]], i);
	}
	bld();
	while(q--) {
		cin >> xi >> yi >> ci, xi=(xi^st[1])-1, yi=(yi^st[1])-1, ci^=st[1];
		upd1(xi, yi, pos[ci]);
		cout << st[1] << "\n";
	}
	pos.clear();
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> t;
	while(t--)
		solve();
}
