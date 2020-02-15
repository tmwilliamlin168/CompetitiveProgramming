#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int mxN=1e5;
int n, M, q, a[mxN], k;
ll st[1<<18], pp[9][16*mxN+1], ps[9], iv[mxN+1];

struct dat {
	ll x=1;
	int a[9];
	void rst(int b=1) {
		for(int i=0; i<k; ++i) {
			a[i]=0;
			while(b%ps[i]==0) {
				b/=ps[i];
				++a[i];
			}
		}
		x=b%M;
	}
	dat operator+(const dat &o) {
		dat r={x*o.x%M};
		for(int i=0; i<k; ++i)
			r.a[i]=a[i]+o.a[i];
		return r;
	}
} lz[1<<18];

void bld(int i=1, int l2=0, int r2=n-1) {
	if(l2==r2) {
		lz[i].rst(a[l2]);
		st[i]=a[l2]%M;
		return;
	}
	int m2=(l2+r2)/2;
	bld(2*i, l2, m2);
	bld(2*i+1, m2+1, r2);
	st[i]=(st[2*i]+st[2*i+1])%M;
}

void app(int i, dat x) {
	lz[i]=lz[i]+x;
	st[i]=st[i]*x.x%M;
	for(int j=0; j<k; ++j)
		st[i]=st[i]*pp[j][x.a[j]]%M;
}

void psh(int i) {
	app(2*i, lz[i]);
	app(2*i+1, lz[i]);
	lz[i].rst(1);
}

void upd1(int l1, int r1, dat x, int i=1, int l2=0, int r2=n-1) {
	if(l1<=l2&&r2<=r1) {
		app(i, x);
		return;
	}
	int m2=(l2+r2)/2;
	psh(i);
	if(l1<=m2)
		upd1(l1, r1, x, 2*i, l2, m2);
	if(m2<r1)
		upd1(l1, r1, x, 2*i+1, m2+1, r2);
	st[i]=(st[2*i]+st[2*i+1])%M;
}

ll modI(ll a, ll m) {
	return (a%=m)<=1?1:(1-m*modI(m%a, a))/a+m;
}

void upd2(int l1, int x, int i=1, int l2=0, int r2=n-1) {
	if(l2==r2) {
		st[i]=1;
		for(int j=0; j<k; ++j) {
			while(x%ps[j]==0) {
				x/=ps[j];
				--lz[i].a[j];
			}
			st[i]=st[i]*pp[j][lz[i].a[j]]%M;
		}
		lz[i].x=lz[i].x*modI(x, M)%M;
		st[i]=st[i]*lz[i].x%M;
		return;
	}
	int m2=(l2+r2)/2;
	psh(i);
	if(l1<=m2)
		upd2(l1, x, 2*i, l2, m2);
	else
		upd2(l1, x, 2*i+1, m2+1, r2);
	st[i]=(st[2*i]+st[2*i+1])%M;
}

ll qry(int l1, int r1, int i=1, int l2=0, int r2=n-1) {
	if(l1<=l2&&r2<=r1)
		return st[i];
	int m2=(l2+r2)/2;
	psh(i);
	return ((l1<=m2?qry(l1, r1, 2*i, l2, m2):0)+(m2<r1?qry(l1, r1, 2*i+1, m2+1, r2):0))%M;
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	
	cin >> n >> M;
	ll M2=M;
	for(ll i=2; i*i<M2; ++i) {
		if(M2%i)
			continue;
		ps[k++]=i;
		while(M2%i==0)
			M2/=i;
	}
	if(M2>1)
		ps[k++]=M2;
	for(int i=0; i<k; ++i) {
		pp[i][0]=1;
		for(int j=1; j<=mxN*16; ++j)
			pp[i][j]=pp[i][j-1]*ps[i]%M;
	}
	for(int i=0; i<n; ++i)
		cin >> a[i];
	bld();
	cin >> q;
	for(int qt, l, r, x; q--; ) {
		cin >> qt >> l, --l;
		if(qt==1) {
			cin >> r >> x, --r;
			dat d;
			d.rst(x);
			upd1(l, r, d);
		} else if(qt==2) {
			cin >> x;
			upd2(l, x);
		} else {
			cin >> r, --r;
			cout << qry(l, r) << "\n";
		}
	}
}
