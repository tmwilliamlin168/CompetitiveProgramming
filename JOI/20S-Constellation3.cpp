#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define ar array

const int mxN=2e5;
int n, m, a[mxN];
ar<int, 3> b[mxN];
ll s, dp2[mxN];

struct ds1 {
	ar<int, 2> st[2*mxN];
	void init() {
		for(int i=0; i<n; ++i)
			st[i+n]={a[i], i};
		for(int i=n-1; i; --i)
			st[i]=max(st[2*i], st[2*i+1]);
	}
	ar<int, 2> qry(int l, int r) {
		ar<int, 2> b{};
		for(l+=n, r+=n+1; l<r; ++l/=2, r/=2) {
			if(l&1)
				b=max(st[l], b);
			if(r&1)
				b=max(st[r-1], b);
		}
		return b;
	}
} ds1;

struct ds2 {
	ar<int, 3> st[2*mxN];
	void init() {
		for(int i=0; i<m; ++i)
			st[i+m]={b[i][1], b[i][0], b[i][2]};
		for(int i=m-1; i; --i)
			st[i]=min(st[2*i], st[2*i+1]);
	}
	ar<int, 3> qry(int l, int r) {
		ar<int, 3> b{n+1};
		for(l+=m, r+=m+1; l<r; ++l/=2, r/=2) {
			if(l&1)
				b=min(st[l], b);
			if(r&1)
				b=min(st[r-1], b);
		}
		return b;
	}
	void upd(int i, ar<int, 3> x) {
		for(st[i+=m]=x; i/=2; )
			st[i]=min(st[2*i], st[2*i+1]);
	}
} ds2;

struct ds3 {
	ll ft[mxN+1];
	void upd(int i, ll x) {
		for(++i; i<=n; i+=i&-i)
			ft[i]+=x;
	}
	void upd(int l, int r, ll x) {
		upd(l, x);
		upd(r+1, -x);
	}
	ll qry(int i) {
		ll r=0;
		for(++i; i; i-=i&-i)
			r+=ft[i];
		return r;
	}
} ds3;

int dfs(int l, int r, int mx) {
	if(l>r)
		return -1;
	int m2=ds1.qry(l, r)[1], lc=dfs(l, m2-1, a[m2]), rc=dfs(m2+1, r, a[m2]);
	dp2[m2]=(~lc?dp2[lc]:0)+(~rc?dp2[rc]:0);
	int l2=lower_bound(b, b+m, ar<int, 3>{l})-b, r2=lower_bound(b, b+m, ar<int, 3>{r+1})-b-1;
	while(1) {
		ar<int, 3> d=ds2.qry(l2, r2);
		if(d[0]>mx)
			break;
		if(d[1]<m2)
			dp2[m2]=max(d[2]+(~lc?ds3.qry(d[1]):0)+(~rc?dp2[rc]:0), dp2[m2]);
		else if(d[1]>m2)
			dp2[m2]=max(d[2]+(~lc?dp2[lc]:0)+(~rc?ds3.qry(d[1]):0), dp2[m2]);
		else
			dp2[m2]=max(d[2]+(~lc?dp2[lc]:0)+(~rc?dp2[rc]:0), dp2[m2]);
		ds2.upd(lower_bound(b, b+m, ar<int, 3>{d[1], d[0], d[2]})-b, {n+1});
	}
	ds3.upd(l, m2, ~rc?dp2[rc]:0);
	ds3.upd(m2, r, ~lc?dp2[lc]:0);
	return m2;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n;
	for(int i=0; i<n; ++i)
		cin >> a[i];
	ds1.init();
	cin >> m;
	for(int i=0; i<m; ++i) {
		cin >> b[i][0] >> b[i][1] >> b[i][2], --b[i][0];
		s+=b[i][2];
	}
	sort(b, b+m);
	ds2.init();
	cout << s-dp2[dfs(0, n-1, n)];
}
