#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int mxN=1e3;
int n, a[mxN], b[mxN];
ll L, l[mxN], r[mxN];

ll ask(int i, ll x) {
	cout << "? " << i+1 << " " << x << endl;
	cin >> x;
	return x;
}

void dc(int l1, int r1, ll l2, ll r2) {
	if(l1==r1) {
		l[a[l1]]=l2;
		r[a[l1]]=r2;
		return;
	}
	int m1=(l1+r1)/2;
	ll x=L/n*(m1+1), m2;
	for(int l=l1, r=r1; ; ) {
		int i=rand()%(r-l+1)+l;
		ll lb=l2, rb=r2;
		while(lb<rb) {
			ll mb=(lb+rb)/2;
			if(ask(a[i], mb)<x)
				lb=mb+1;
			else
				rb=mb;
		}
		int l2=l, r2=r;
		vector<int> e;
		for(int j=l; j<=r; ++j) {
			ll y=ask(a[j], lb);
			if(y>x)
				b[l2++]=a[j];
			else if(y<x)
				b[r2--]=a[j];
			else
				e.push_back(a[j]);
		}
		for(int j=0; j<e.size(); ++j)
			b[l2+j]=e[j];
		memcpy(a+l, b+l, 4*(r-l+1));
		if(l2<=m1&&m1<=r2) {
			m2=lb;
			break;
		}
		if(l2<m1)
			l=l2+1;
		else
			r=l2-1;
	}
	dc(l1, m1, l2, m2);
	dc(m1+1, r1, m2, r2);
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> n >> L;
	iota(a, a+n, 0);
	dc(0, n-1, 0, 1e18);
	cout << "!\n";
	for(int i=0; i<n; ++i)
		cout << l[i] << " " << r[i] << "\n";
}
