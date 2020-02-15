#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int mxN=1e5;
int t, n, m, a[mxN], qt, li, ri, xi;

struct d1 {
	ll a;
	bool b;
};

struct d2 {
	ll a;
	int b, c;
};

struct segtree {
	d2 st[1<<18], ans;
	d1 lz[1<<18];
	void bld(int i=1, int l2=0, int r2=n-1) {
		lz[i]={};
		if(l2==r2) {
			st[i]={a[l2], 1, 0};
			return;
		}
		int m2=(l2+r2)/2;
		bld(2*i, l2, m2);
		bld(2*i+1, m2+1, r2);
		st[i]=cmb(st[2*i], 2*i+1, m2+1, r2);
	}
	void app(int i, d1 x, int l2, int r2) {
		if(x.b) {
			st[i]={0, r2-l2+1, r2-(l2+r2)/2};
			lz[i]={0, 1};
		}
		st[i].a+=x.a;
		lz[i].a+=x.a;
	}
	void psh(int i, int l2, int m2, int r2) {
		app(2*i, lz[i], l2, m2);
		app(2*i+1, lz[i], m2+1, r2);
		lz[i]={};
	}
	d2 cmb(d2 a, int i, int l2, int r2) {
		a.c=0;
		ll b=st[i].a;
		while(1) {
			if(l2==r2) {
				a.b+=a.a<=st[i].a;
				a.c+=a.a<=st[i].a;
				break;
			}
			int m2=(l2+r2)/2;
			psh(i, l2, m2, r2);
			if(st[2*i].a>=a.a) {
				a.b+=st[i].c;
				a.c+=st[i].c;
				i=2*i;
				r2=m2;
			} else {
				i=2*i+1;
				l2=m2+1;
			}
		}
		a.a=max(b, a.a);
		return a;
	}
	void upd(int l1, int r1, d1 x, int i=1, int l2=0, int r2=n-1) {
		if(l1<=l2&&r2<=r1) {
			app(i, x, l2, r2);
			return;
		}
		int m2=(l2+r2)/2;
		psh(i, l2, m2, r2);
		if(l1<=m2)
			upd(l1, r1, x, 2*i, l2, m2);
		if(m2<r1)
			upd(l1, r1, x, 2*i+1, m2+1, r2);
		st[i]=cmb(st[2*i], 2*i+1, m2+1, r2);
	}
	void qry2(int l1, int r1, int i=1, int l2=0, int r2=n-1) {
		if(l1<=l2&&r2<=r1) {
			ans=cmb(ans, i, l2, r2);
			return;
		}
		int m2=(l2+r2)/2;
		psh(i, l2, m2, r2);
		if(l1<=m2)
			qry2(l1, r1, 2*i, l2, m2);
		if(m2<r1)
			qry2(l1, r1, 2*i+1, m2+1, r2);
	}
	array<int, 2> qry3(int l1, int r1, ll x, int i=1, int l2=0, int r2=n-1) {
		if(l1<=l2&&r2<=r1&&st[i].a<=x)
			return {r2-l2+1, 0};
		if(l2==r2)
			return {0, 1};
		int m2=(l2+r2)/2;
		psh(i, l2, m2, r2);
		array<int, 2> a{};
		if(l1<=m2)
			a=qry3(l1, r1, x, 2*i, l2, m2);
		if(!a[1]&&m2<r1) {
			array<int, 2> b=qry3(l1, r1, x, 2*i+1, m2+1, r2);
			a[0]+=b[0];
			a[1]=b[1];
		}
		return a;
	}
	int qry(int l, int r, int x) {
		ans.a=0;
		qry2(x, x);
		ll ax=ans.a;
		ans={};
		qry2(x, l);
		ans.b=ans.a<=ax?qry3(l, r, ax)[0]:0;
		ans.a=max(ax+1, ans.a);
		qry2(l, r);
		return ans.b;
	}
} st1, st2;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> t;
	while(t--) {
		cin >> n >> m;
		for(int i=0; i<n; ++i)
			cin >> a[i];
		st1.bld();
		for(int i=0; i<n-1-i; ++i)
			swap(a[i], a[n-1-i]);
		st2.bld();
		while(m--) {
			cin >> qt >> li >> ri >> xi, --li, --ri;
			if(qt==3) {
				--xi;
				cout << (xi<ri?st1.qry(max(li, xi+1), ri, xi):0)+(li<xi?st2.qry(max(n-1-ri, n-xi), n-1-li, n-1-xi):0)+(li<=xi&&xi<=ri) << "\n";
			} else {
				st1.upd(li, ri, {xi, qt-1});
				st2.upd(n-1-ri, n-1-li, {xi, qt-1});
			}
		}
	}
}
