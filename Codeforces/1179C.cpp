#include <bits/stdc++.h>
using namespace std;

const int mxN=3e5, mxA=1e6;
int n, m, a[mxN], b[mxN], st[1<<21], lz[1<<21], q;

void app(int i, int x) {
	st[i]+=x;
	lz[i]+=x;
}

void psh(int i) {
	app(2*i, lz[i]);
	app(2*i+1, lz[i]);
	lz[i]=0;
}

void upd(int l1, int r1, int x, int i=1, int l2=0, int r2=mxA-1) {
	if(l1<=l2&&r2<=r1) {
		app(i, x);
		return;
	}
	int m2=(l2+r2)/2;
	psh(i);
	if(l1<=m2)
		upd(l1, r1, x, 2*i, l2, m2);
	if(m2<r1)
		upd(l1, r1, x, 2*i+1, m2+1, r2);
	st[i]=min(st[2*i], st[2*i+1]);
}

int qry(int i=1, int l2=0, int r2=mxA-1) {
	if(st[i]>=0)
		return -1;
	if(l2==r2)
		return l2+1;
	int m2=(l2+r2)/2;
	psh(i);
	int a=qry(2*i+1, m2+1, r2);
	if(~a)
		return a;
	else
		return qry(2*i, l2, m2);
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> n >> m;
	for(int i=0; i<n; ++i) {
		cin >> a[i], --a[i];
		upd(0, a[i], -1);
	}
	for(int i=0; i<m; ++i) {
		cin >> b[i], --b[i];
		upd(0, b[i], 1);
	}
	cin >> q;
	while(q--) {
		int qt, i, x;
		cin >> qt >> i >> x, --i, --x;
		if(qt==1) {
			upd(0, a[i], 1);
			a[i]=x;
			upd(0, a[i], -1);
		} else {
			upd(0, b[i], -1);
			b[i]=x;
			upd(0, b[i], 1);
		}
		cout << qry() << "\n";
	}
}
