- We need to set to segment a[0]*(a[1]+l)%a[2]+a[0]*(a[1]+l+1)%a[2]+..+a[0]*(a[1]+r)%a[2]
- a[0]*((a[1]+l)+(a[1]+l+1)+..+(a[1]+r))-(a[0]*(a[1]+l)/a[2]+a[0]*(a[1]+l+1)/a[2]+..+a[0]*(a[1]+r)/a[2])*a[2]
- a[0]*((a[1]+l)*(r-l+1)+(r-l)*(r-l+1)/2)-(f(a[1]+r, a[0], a[2])-f(a[1]+l-1, a[0], a[2]))*a[2]
- We can use the standard Euclidean-like algorithm for evaluating summations of the form sum(0<=i<=n, floor((a*i+b)/c))

#include <bits/stdc++.h>
using namespace std;

#define ull long long

int n, q, x[100000];
ull st[1<<18];
array<int, 3> lz[1<<18];
vector<array<int, 4>> qs;

ull f(ull n, ull a, ull b, ull c) {
	if(!a)
		return b/c*(n+1);
	if(a>=c||b>=c)
		return f(n, a%c, b%c, c)+n*(n+1)/2*(a/c)+b/c*(n+1);
	ull m=(a*n+b)/c;
	return !m?0:m*n-f(m-1, c, c-b-1, a);
}

void app(int i, array<int, 3> a, int l2, int r2) {
	if(a[0]<0)
		return;
	ull l=x[l2], r=x[r2+1]-1;
	st[i]=a[0]*((a[1]+l)*(r-l+1)+(r-l)*(r-l+1)/2)-(f(a[1]+r, a[0], 0, a[2])-f(a[1]+l-1, a[0], 0, a[2]))*a[2];
	lz[i]=a;
}

void psh(int i, int l2, int m2, int r2) {
	app(2*i, lz[i], l2, m2);
	app(2*i+1, lz[i], m2+1, r2);
	lz[i]={-1};
}

void upd(int l1, int r1, array<int, 3> a, int i=1, int l2=0, int r2=2*q-1) {
	if(l1<=l2&&r2<=r1) {
		app(i, a, l2, r2);
		return;
	}
	int m2=(l2+r2)/2;
	psh(i, l2, m2, r2);
	if(l1<=m2)
		upd(l1, r1, a, 2*i, l2, m2);
	if(m2<r1)
		upd(l1, r1, a, 2*i+1, m2+1, r2);
	st[i]=st[2*i]+st[2*i+1];
}

ull qry(int l1, int r1, int i=1, int l2=0, int r2=2*q-1) {
	if(l1<=l2&&r2<=r1)
		return st[i];
	int m2=(l2+r2)/2;
	psh(i, l2, m2, r2);
	return (l1<=m2?qry(l1, r1, 2*i, l2, m2):0)+(m2<r1?qry(l1, r1, 2*i+1, m2+1, r2):0);
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> n >> q;
	for(int i=0, qt, l, r, a, b; i<q; ++i) {
		cin >> qt >> l >> r;
		if(qt==1) {
			cin >> a >> b;
			qs.push_back({l, r+1, a, b});
		} else
			qs.push_back({l, r+1, -1});
		for(int j : {0, 1})
			x[2*i+j]=qs.back()[j];
	}
	sort(x, x+2*q);
	memset(lz, -1, sizeof(lz));
	auto fx=[](int y) {
		return lower_bound(x, x+2*q, y)-x;
	};
	for(int i=0; i<q; ++i) {
		if(~qs[i][2])
			upd(fx(qs[i][0]), fx(qs[i][1])-1, {qs[i][2], 1-qs[i][0], qs[i][3]});
		else
			cout << qry(fx(qs[i][0]), fx(qs[i][1])-1) << "\n";
	}
}
