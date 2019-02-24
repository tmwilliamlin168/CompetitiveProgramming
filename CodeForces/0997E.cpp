#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int mxN=1.2e5;
int n, a[mxN], la[mxN], lb[mxN], q, mn[1<<18], mc[1<<18], lz1[1<<18], lz2[1<<18];
ll s[1<<18], ans[mxN];
vector<array<int, 2>> qs[mxN];

void cmb(int i) {
	mn[i]=mn[2*i];
	mc[i]=mc[2*i];
	if(mn[i]>mn[2*i+1]) {
		mn[i]=mn[2*i+1];
		mc[i]=0;
	}
	if(mn[i]==mn[2*i+1])
		mc[i]+=mc[2*i+1];
	s[i]=s[2*i]+s[2*i+1];
}

void bld(int i=1, int l2=0, int r2=n-1) {
	if(l2==r2) {
		mn[i]=l2;
		mc[i]=1;
		return;
	}
	int m2=(l2+r2)/2;
	bld(2*i, l2, m2);
	bld(2*i+1, m2+1, r2);
	cmb(i);
}

void app(int i, int x1, int x2) {
	mn[i]+=x1;
	s[i]+=(ll)mc[i]*x2;
	lz1[i]+=x1;
	lz2[i]+=x2;
}

void psh(int i) {
	app(2*i, lz1[i], (mn[i]==mn[2*i]+lz1[i])*lz2[i]);
	app(2*i+1, lz1[i], (mn[i]==mn[2*i+1]+lz1[i])*lz2[i]);
	lz1[i]=lz2[i]=0;
}

void upd(int l1, int r1, int x, int i=1, int l2=0, int r2=n-1) {
	if(l1<=l2&&r2<=r1) {
		app(i, x, 0);
		return;
	}
	int m2=(l2+r2)/2;
	psh(i);
	if(l1<=m2)
		upd(l1, r1, x, 2*i, l2, m2);
	if(m2<r1)
		upd(l1, r1, x, 2*i+1, m2+1, r2);
	cmb(i);
}

ll qry(int l1, int r1, int i=1, int l2=0, int r2=n-1) {
	if(l1<=l2&&r2<=r1)
		return s[i];
	int m2=(l2+r2)/2;
	psh(i);
	return (l1<=m2?qry(l1, r1, 2*i, l2, m2):0)+(m2<r1?qry(l1, r1, 2*i+1, m2+1, r2):0);
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> n;
	for(int i=0; i<n; ++i)
		cin >> a[i];
	bld();
	cin >> q;
	for(int i=0, l, r; i<q; ++i)
		cin >> l >> r, --l, --r, qs[r].push_back({l, i});
	for(int i=0; i<n; ++i) {
		la[i]=lb[i]=i-1;
		while(la[i]>=0&&a[la[i]]<a[i]) {
			upd(la[la[i]]+1, la[i], a[i]-a[la[i]]);
			la[i]=la[la[i]];
		}
		while(lb[i]>=0&&a[lb[i]]>a[i]) {
			upd(lb[lb[i]]+1, lb[i], a[lb[i]]-a[i]);
			lb[i]=lb[lb[i]];
		}
		app(1, 0, 1);
		for(array<int, 2> a : qs[i])
			ans[a[1]]=qry(a[0], n);
	}
	for(int i=0; i<q; ++i)
		cout << ans[i] << "\n";
}
