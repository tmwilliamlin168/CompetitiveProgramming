#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int mxN=2e5;
int n, m, p[mxN];
array<ll, 2> a[mxN], q[mxN], ft[mxN+1];
ll ans=-1e18;

array<ll, 2> operator+(array<ll, 2> a, array<ll, 2> b) {
	return {a[0]+b[0], a[1]+b[1]};
}

void upd(int i, array<ll, 2> x) {
	for(++i; i<=n; i+=i&-i)
		ft[i]=ft[i]+x;
}

ll sk(int k) {
	array<ll, 2> r{};
	for(int i=17, x=0; ~i; --i) {
		if(x+(1<<i)<=n&&(r+ft[x+(1<<i)])[1]<=k) {
			x+=1<<i;
			r=r+ft[x];
		}
	}
	return r[0];
}

void dc(int l1=0, int r1=n-m, int l2=0, int r2=n-1) {
	if(l1>r1) {
		for(int i=l2; i<=r2; ++i)
			upd(p[i], {a[i][1], 1});
		return;
	}
	int m1=(l1+r1)/2, m2;
	for(int i=l1; i<m1; ++i)
		upd(p[i], {-a[i][1], -1});
	ll ca=-1e18;
	for(int i=l2; i<=r2; ++i) {
		upd(p[i], {a[i][1], 1});
		if(i-m1+1<m)
			continue;
		ll da=sk(m)-2*a[i][0];
		if(da>ca) {
			m2=i;
			ca=da;
		}
	}
	ans=max(ca+2*a[m1][0], ans);
	for(int i=l1; i<m1; ++i)
		upd(p[i], {a[i][1], 1});
	for(int i=l2; i<=r2; ++i)
		upd(p[i], {-a[i][1], -1});
	dc(l1, m1-1, l2, m2);
	upd(p[m1], {-a[m1][1], -1});
	upd(p[m2], {-a[m2][1], -1});
	dc(m1+1, r1, m2, r2);
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> n >> m;
	for(int i=0; i<n; ++i)
		cin >> a[i][1] >> a[i][0];
	sort(a, a+n);
	for(int i=0; i<n; ++i)
		q[i]={-a[i][1], i};
	sort(q, q+n);
	for(int i=0; i<n; ++i)
		p[q[i][1]]=i;
	dc();
	cout << ans;
}
