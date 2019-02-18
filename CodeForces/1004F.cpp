#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int mxN=1e5;
int n, m, x, a[mxN];

struct dat {
	ll a=0;
	vector<array<int, 2>> l, r;
	dat() {}
	dat(int b) {
		l=r={{b, 1}};
		a=b>=x;
	}
	void mrg(const vector<array<int, 2>> &a, const vector<array<int, 2>> &b, vector<array<int, 2>> &c) const {
		c=a;
		if(!c.size())
			c.push_back({b[0][0], 0});
		for(array<int, 2> d : b) {
			if((c.back()[0]|d[0])==c.back()[0])
				c.back()[1]+=d[1];
			else
				c.push_back({c.back()[0]|d[0], d[1]});
		}
	}
	dat operator+(const dat &o) {
		dat c;
		c.a+=a+o.a;
		mrg(l, o.l, c.l);
		mrg(o.r, r, c.r);
		for(int i1=0, i2=o.l.size(), s=0; i1<r.size(); ++i1) {
			while(i2&&(r[i1][0]|o.l[i2-1][0])>=x)
				s+=o.l[--i2][1];
			c.a+=(ll)r[i1][1]*s;
		}
		return c;
	}
} st[1<<18];

void bld(int i=1, int l2=0, int r2=n-1) {
	if(l2==r2) {
		st[i]=dat(a[l2]);
		return;
	}
	int m2=(l2+r2)/2;
	bld(2*i, l2, m2);
	bld(2*i+1, m2+1, r2);
	st[i]=st[2*i]+st[2*i+1];
}

void upd(int l1, int x, int i=1, int l2=0, int r2=n-1) {
	if(l2==r2) {
		st[i]=dat(x);
		return;
	}
	int m2=(l2+r2)/2;
	if(l1<=m2)
		upd(l1, x, 2*i, l2, m2);
	else
		upd(l1, x, 2*i+1, m2+1, r2);
	st[i]=st[2*i]+st[2*i+1];
}

dat qry(int l1, int r1, int i=1, int l2=0, int r2=n-1) {
	if(l1<=l2&&r2<=r1)
		return st[i];
	int m2=(l2+r2)/2;
	return (l1<=m2?qry(l1, r1, 2*i, l2, m2):dat())+(m2<r1?qry(l1, r1, 2*i+1, m2+1, r2):dat());
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> n >> m >> x;
	for(int i=0; i<n; ++i)
		cin >> a[i];
	bld();
	for(int qt, a, b; m--; ) {
		cin >> qt >> a >> b;
		if(qt==1)
			upd(a-1, b);
		else
			cout << qry(a-1, b-1).a << "\n";
	}
}
