/*
	- If m < n
		- Use a permutation composition segment tree
		- O(qmlogn), where m < ~450
		- Permutation composition is invertible, so only prefix of permutations were required
	- Else
		- Calculate answer in O(m) for each of the possible O(n^2) queries
		- O(n^2m), where n < ~450 and n*m < 2e5
*/

#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int mxN=1e5, bs=450;
int n, m, q;
vector<int> p[mxN], st[1<<18];
ll qa2[mxN/bs][mxN/bs];

inline void mrg(vector<int> &a, vector<int> &b, vector<int> &c) {
	c.resize(m);
	for(int i=0; i<m; ++i)
		c[i]=b[a[i]];
}

void bld(int i=1, int l2=0, int r2=n-1) {
	if(l2==r2) {
		st[i]=p[l2];
		return;
	}
	int m2=(l2+r2)/2;
	bld(2*i, l2, m2);
	bld(2*i+1, m2+1, r2);
	mrg(st[2*i], st[2*i+1], st[i]);
}

void qry(vector<int> &a, int l1, int r1, int i=1, int l2=0, int r2=n-1) {
	if(l1<=l2&&r2<=r1) {
		a=st[i];
		return;
	}
	int m2=(l2+r2)/2;
	if(l1<=m2&&m2<r1) {
		vector<int> b, c;
		qry(b, l1, r1, 2*i, l2, m2);
		qry(c, l1, r1, 2*i+1, m2+1, r2);
		mrg(b, c, a);
	} else if(l1<=m2)
		qry(a, l1, r1, 2*i, l2, m2);
	else
		qry(a, l1, r1, 2*i+1, m2+1, r2);
}

inline void solve() {
	cin >> n >> m;
	for(int i=0; i<n; ++i) {
		p[i].resize(m);
		for(int j=0; j<m; ++j)
			cin >> p[i][j], --p[i][j];
	}
	cin >> q;
	if(m<bs) {
		bld();
		for(int i=0; i<q; ++i) {
			int ql, qr;
			cin >> ql >> qr, --ql, --qr;
			ll qa1=0;
			vector<int> a;
			qry(a, ql, qr);
			for(int j=0; j<m; ++j)
				qa1+=(ll)(j+1)*(a[j]+1);
			cout << qa1 << "\n";
		}
	} else {
		for(int i=0; i<n; ++i) {
			vector<int> a(m), b;
			for(int j=0; j<m; ++j)
				a[j]=j;
			for(int j=i; j<n; ++j) {
				mrg(a, p[j], b);
				a=b;
				qa2[i][j]=0;
				for(int k=0; k<m; ++k)
					qa2[i][j]+=(ll)(k+1)*(a[k]+1);
			}
		}
		for(int i=0; i<q; ++i) {
			int ql, qr;
			cin >> ql >> qr, --ql, --qr;
			cout << qa2[ql][qr] << "\n";
		}
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int t;
	cin >> t;
	while(t--)
		solve();
}
