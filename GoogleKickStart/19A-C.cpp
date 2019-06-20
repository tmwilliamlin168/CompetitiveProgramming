#include <bits/stdc++.h>
using namespace std;

const int mxQ=3e4;
int t, n, q, l[mxQ], r[mxQ], c[mxQ], st[1<<17], x[2*mxQ];
bool u[mxQ];
array<int, 2> lz[1<<17];
priority_queue<array<int, 2>> pq;

void app(int i, array<int, 2> x) {
	st[i]+=x[0];
	lz[i][0]+=x[0];
	lz[i][1]+=x[1];
}

void psh(int i) {
	app(2*i, lz[i]);
	app(2*i+1, lz[i]);
	lz[i]={};
}

void upd1(int l1, int r1, int x, int i=1, int l2=0, int r2=2*q-2) {
	if(l1<=l2&&r2<=r1) {
		app(i, {1, x});
		return;
	}
	int m2=(l2+r2)/2;
	psh(i);
	if(l1<=m2)
		upd1(l1, r1, x, 2*i, l2, m2);
	if(m2<r1)
		upd1(l1, r1, x, 2*i+1, m2+1, r2);
	st[i]=min(st[2*i], st[2*i+1]);
}

void upd2(int i, int l2, int r2) {
	if(st[i]>1)
		return;
	if(l2==r2) {
		if(st[i]==1) {
			c[lz[i][1]]+=x[l2+1]-x[l2];
			pq.push({c[lz[i][1]], lz[i][1]});
		}
		return;
	}
	int m2=(l2+r2)/2;
	psh(i);
	upd2(2*i, l2, m2);
	upd2(2*i+1, m2+1, r2);
}

void upd3(int l1, int r1, int x, int i=1, int l2=0, int r2=2*q-2) {
	if(l1<=l2&&r2<=r1) {
		app(i, {-1, -x});
		upd2(i, l2, r2);
		return;
	}
	int m2=(l2+r2)/2;
	psh(i);
	if(l1<=m2)
		upd3(l1, r1, x, 2*i, l2, m2);
	if(m2<r1)
		upd3(l1, r1, x, 2*i+1, m2+1, r2);
	st[i]=min(st[2*i], st[2*i+1]);
}

void bld(int i=1, int l2=0, int r2=2*q-2) {
	if(l2==r2) {
		if(st[i]==1)
			c[lz[i][1]]+=x[l2+1]-x[l2];
		return;
	}
	int m2=(l2+r2)/2;
	psh(i);
	bld(2*i, l2, m2);
	bld(2*i+1, m2+1, r2);
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> t;
	for(int ti=1; ti<=t; ++ti) {
		cin >> n >> q;
		for(int i=0; i<q; ++i) {
			cin >> l[i] >> r[i];
			x[2*i]=l[i];
			x[2*i+1]=r[i]+1;
		}
		sort(x, x+2*q);
		for(int i=0; i<q; ++i)
			upd1(lower_bound(x, x+2*q, l[i])-x, upper_bound(x, x+2*q, r[i])-x-1, i);
		int ans=1e9;
		bld();
		for(int i=0; i<q; ++i)
			pq.push({c[i], i});
		while(!pq.empty()) {
			array<int, 2> b=pq.top();
			pq.pop();
			if(u[b[1]])
				continue;
			u[b[1]]=1;
			ans=min(b[0], ans);
			upd3(lower_bound(x, x+2*q, l[b[1]])-x, upper_bound(x, x+2*q, r[b[1]])-x-1, b[1]);
		}
		cout << "Case #" << ti << ": " << ans << "\n";
		memset(u, 0, q);
		memset(c, 0, 4*q);
		memset(st, 0, sizeof(st));
		memset(lz, 0, sizeof(lz));
	}
}
