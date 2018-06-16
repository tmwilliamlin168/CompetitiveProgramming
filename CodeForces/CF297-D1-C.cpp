/*
	- http://codeforces.com/blog/entry/7437
*/

#include <bits/stdc++.h>
using namespace std;

#define fi first
#define se second

const int mxN=1e5;
int n, a[mxN], b[mxN];
pair<int, int> ps[mxN];

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n;
	for(int i=0; i<n; ++i)
		cin >> ps[i].fi, ps[i].se=i;
	sort(ps, ps+n);
	for(int i=0; i<(n+2)/3; ++i) {
		a[ps[i].se]=i;
		b[ps[i].se]=ps[i].fi-i;
	}
	for(int i=(n+2)/3; i<(2*n+2)/3; ++i) {
		b[ps[i].se]=i;
		a[ps[i].se]=ps[i].fi-i;
	}
	for(int i=(2*n+2)/3; i<n; ++i) {
		b[ps[i].se]=(n+2)/3-i+(2*n-1)/3;
		a[ps[i].se]=ps[i].fi-b[ps[i].se];
	}
	cout << "YES\n";
	for(int i=0; i<n; ++i)
		cout << a[i] << " ";
	cout << "\n";
	for(int i=0; i<n; ++i)
		cout << b[i] << " ";
}
