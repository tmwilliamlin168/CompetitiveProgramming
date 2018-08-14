#include <bits/stdc++.h>
using namespace std;

const int mxN=2e5;
int n, x, t[mxN], ps[mxN], ft[2][mxN+1];

inline void upd(int k, int i, int x) {
	for(++i; i<=n; i+=i&-i)
		ft[k][i]=max(x, ft[k][i]);
}

inline int qry(int k, int i) {
	int r=0;
	for(; i; i-=i&-i)
		r=max(ft[k][i], r);
	return r;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> x;
	for(int i=0; i<n; ++i)
		cin >> t[i], ps[i]=t[i];
	sort(ps, ps+n);
	for(int i=0; i<n; ++i) {
		int p=lower_bound(ps, ps+n, t[i])-ps, a=qry(0, p), b=qry(0, lower_bound(ps, ps+n, t[i]+x)-ps), c=qry(1, p);
		upd(0, p, a+1);
		upd(1, p, max(b, c)+1);
	}
	cout << qry(1, n);
}
