#include <bits/stdc++.h>
using namespace std;

const int mxN=2e5, oo=1<<30;
int n, q, h[mxN], a[mxN], b[mxN], ans[mxN], ql[mxN], qr[mxN], lz[1<<19];
vector<int> ta[mxN], tu1[2*mxN], tu2[2*mxN];
array<int, 2> st[1<<19];

void app(int i, int x) {
	st[i][1]=max(st[i][0]+x, st[i][1]);
	lz[i]=max(x, lz[i]);
}

void psh(int i) {
	app(2*i, lz[i]);
	app(2*i+1, lz[i]);
	lz[i]=-oo;
}

void upd1(int l1, int x, int i=1, int l2=0, int r2=n-1) {
	if(l2==r2) {
		st[i][0]=x;
		return;
	}
	psh(i);
	int m2=(l2+r2)/2;
	if(l1<=m2)
		upd1(l1, x, 2*i, l2, m2);
	else
		upd1(l1, x, 2*i+1, m2+1, r2);
	st[i][0]=max(st[2*i][0], st[2*i+1][0]);
	st[i][1]=max(st[2*i][1], st[2*i+1][1]);
}

void upd2(int l1, int r1, int x, int i=1, int l2=0, int r2=n-1) {
	if(l1<=l2&&r2<=r1) {
		app(i, x);
		return;
	}
	int m2=(l2+r2)/2;
	psh(i);
	if(l1<=m2)
		upd2(l1, r1, x, 2*i, l2, m2);
	if(m2<r1)
		upd2(l1, r1, x, 2*i+1, m2+1, r2);
	st[i][0]=max(st[2*i][0], st[2*i+1][0]);
	st[i][1]=max(st[2*i][1], st[2*i+1][1]);
}

int qry(int l1, int i=1, int l2=0, int r2=n-1) {
	if(l1<=l2)
		return st[i][1];
	int m2=(l2+r2)/2;
	psh(i);
	return max(l1<=m2?qry(l1, 2*i, l2, m2):-oo, qry(l1, 2*i+1, m2+1, r2));
}

void solve() {
	memset(st, 0xc0, sizeof(st));
	memset(lz, 0xc0, sizeof(lz));
	for(int i=0; i<n; ++i) {
		for(int j : tu1[i])
			upd1(j, -h[j]);
		if(i-a[i]>=0)
			upd2(max(i-b[i], 0), i-a[i], h[i]);
		for(int j : ta[i])
			ans[j]=max(qry(ql[j]), ans[j]);
		for(int j : tu2[i])
			upd1(j, -oo);
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> n;
	for(int i=0; i<n; ++i) {
		cin >> h[i] >> a[i] >> b[i];
		tu1[i+a[i]].push_back(i);
		tu2[i+b[i]].push_back(i);
	}
	cin >> q;
	memset(ans, -1, 4*q);
	for(int i=0; i<q; ++i) {
		cin >> ql[i] >> qr[i], --ql[i], --qr[i];
		ta[qr[i]].push_back(i);
	}
	solve();
	for(int i=0; i<n; ++i)
		h[i]=-h[i];
	solve();
	for(int i=0; i<q; ++i)
		cout << ans[i] << "\n";
}
