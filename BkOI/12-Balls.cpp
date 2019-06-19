/*
	- The change in score for a right obstacle (l, r) is -s[l-1]+l*(-a[r])+r*a[r]+s[r-1]
	- We can use CHT with binary search to find the max for each r
*/

#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int mxN=3e5;
int n, qt;
ll c[mxN], s[mxN+1], a[mxN], b[mxN];

void al(ll ai, ll bi) {
	while(qt>1&&(bi-b[qt-1])/(a[qt-1]-ai)<(b[qt-1]-b[qt-2])/(a[qt-2]-a[qt-1]))
		--qt;
	a[qt]=ai;
	b[qt]=bi;
	++qt;
}

ll qry(ll x) {
	int l=0, r=qt-1;
	while(l<r) {
		int m=(l+r)/2;
		if(a[m]*x+b[m]>a[m+1]*x+b[m+1])
			r=m;
		else
			l=m+1;
	}
	return a[l]*x+b[l];
}

void gg() {
	for(int i=0; i<n; ++i)
		s[i+1]=s[i]+c[i];
	ll ans=-1e18;
	qt=0;
	for(int i=1; i<n; ++i) {
		al(i-1, s[i-1]);
		ans=max(qry(-c[i])+i*c[i]-s[i], ans);
	}
	cout << s[n]+ans << "\n";
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> n;
	for(int i=0; i<n; ++i)
		cin >> c[i];
	gg();
	reverse(c, c+n);
	gg();
}
