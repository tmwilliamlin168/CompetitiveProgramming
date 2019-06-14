#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int mxN=1e6;
int n, m, p, a[mxN];
ll s1[1<<21];
vector<ll> s2[1<<21];

void bld(int i=1, int l=0, int r=n-1) {
	if(l==r) {
		s1[i]=a[l];
		s2[i]={p-a[l], 1ll<<60};
		return;
	}
	int m=(l+r)/2;
	bld(2*i, l, m);
	bld(2*i+1, m+1, r);
	s1[i]=s1[2*i]+s1[2*i+1];
	ll cs=s1[2*i];
	for(int i1=0, i2=0; i1<s2[2*i].size()-1||i2<s2[2*i+1].size()-1; ) {
		if(s2[2*i][i1]+cs<s2[2*i+1][i2]) {
			if(s2[i].size()&&s2[i].back()>s2[2*i][i1]-p)
				s2[i].push_back(s2[i].back()+p);
			else
				s2[i].push_back(s2[2*i][i1]);
			cs-=p;
			++i1;
		} else
			s2[i].push_back(s2[2*i+1][i2++]-cs);
	}
	s2[i].push_back(1ll<<60);
}

ll qry(int l1, int r1, ll x, int i=1, int l2=0, int r2=n-1) {
	if(l1<=l2&&r2<=r1)
		return x+s1[i]-(ll)(upper_bound(s2[i].begin(), s2[i].end(), x)-s2[i].begin())*p;
	int m2=(l2+r2)/2;
	if(r1<=m2)
		return qry(l1, r1, x, 2*i, l2, m2);
	if(m2<l1)
		return qry(l1, r1, x, 2*i+1, m2+1, r2);
	return qry(l1, r1, qry(l1, r1, x, 2*i, l2, m2), 2*i+1, m2+1, r2);
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> n >> m >> p;
	for(int i=0; i<n; ++i)
		cin >> a[i];
	bld();
	for(int l, r; m--; ) {
		cin >> l >> r, --l, --r;
		cout << qry(l, r, 0) << "\n";
	}
}
