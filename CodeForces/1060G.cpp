#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int mxN=1e5;
int n, m;
ll a[mxN+1];
vector<array<ll, 3>> st[1<<18];

void bld(int i=1, int l=1, int r=n) {
	if(l==r) {
		st[i]={{0, (a[l]-a[l-1]+l-1)/l}};
		st[i][0][2]=st[i][0][1]*l;
		if((a[l]-a[l-1])%l) {
			st[i].push_back({(a[l]-a[l-1])%l, (a[l]-a[l-1])/l});
			st[i][1][2]=st[i][1][1]*l;
		}
		st[i].push_back({l});
		return;
	}
	int m=(l+r)/2;
	bld(2*i, l, m);
	bld(2*i+1, m+1, r);
	for(int j=0; j<st[2*i].size()-1; ++j) {
		ll lj=a[l-1]+st[2*i][j][0]+st[2*i][j][2], rj=a[l-1]+st[2*i][j+1][0]+st[2*i][j][2];
		int k=lower_bound(st[2*i+1].begin(), st[2*i+1].end(), array<ll, 3>{lj-a[m]+1})-st[2*i+1].begin()-1;
		for(; a[m]+st[2*i+1][k][0]<rj; ++k)
			st[i].push_back({st[2*i][j][0]+max(a[m]+st[2*i+1][k][0]-lj, 0ll), st[2*i][j][1]+st[2*i+1][k][1], st[2*i][j][2]+st[2*i+1][k][2]});
	}
	st[i].push_back({l});
}

void qry(int l1, ll &x, ll &k, int i=1, int l2=1, int r2=n) {
	if(!k||r2<l1)
		return;
	int j=lower_bound(st[i].begin(), st[i].end(), array<ll, 3>{x-a[l2-1]+1})-st[i].begin()-1;
	if(l1<=l2&&k>=st[i][j][1]) {
		k-=st[i][j][1];
		x+=st[i][j][2];
		return;
	}
	if(l2==r2) {
		x+=k*l2;
		k=0;
	} else {
		int m2=(l2+r2)/2;
		qry(l1, x, k, 2*i, l2, m2);
		qry(l1, x, k, 2*i+1, m2+1, r2);
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> m;
	for(int i=0; i<n; ++i)
		cin >> a[i], a[i]-=i;
	a[n]=1e15;
	bld();
	for(ll x, k; m--; ) {
		cin >> x >> k;
		int i=upper_bound(a, a+n, x)-a;
		if(i) {
			k+=(x-a[i-1])/i;
			x-=(x-a[i-1])/i*i;
			qry(i, x, k);
		}
		cout << x << "\n";
	}
}
