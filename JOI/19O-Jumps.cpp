/*
	- Optimal triplet (a, b, c) must satisfy max(A[a+1..b-1]) < min(a, b)
		- 3 types of pairs (a, b) to consider
			- (i, i+1)
			- (i, r[i]) where r[i] is the next element not smaller than A[i]
			- (l[i], i) where l[i] is the previous element not smaller than A[i]
		- Total of O(n) pairs that we need to test
	- Do a sweep from left to right
		- When i first reaches 2*b-a for some pair, set B[a] to max(B[a], A[a]+A[b])
		- Next, set ans[j] to max(ans[j], B[j]+A[i]) for all j
		- Finally, answer queries with right end at i by querying max(ans[l..r])
	- The operations can be performed efficiently with a segment tree
*/

#include <bits/stdc++.h>
using namespace std;

const int mxN=5e5;
int n, q, a[mxN], r[mxN], l[mxN], ans[mxN], lz[1<<20];
vector<array<int, 2>> ta[mxN], tb[mxN];
array<int, 2> st[1<<20];

void app(int i, int x) {
	st[i][1]=max(st[i][0]+x, st[i][1]);
	lz[i]=max(x, lz[i]);
}

void psh(int i) {
	app(2*i, lz[i]);
	app(2*i+1, lz[i]);
	lz[i]=0;
}

void upd(int l1, int x, int i=1, int l2=0, int r2=n-1) {
	if(l2==r2) {
		st[i][0]=max(x, st[i][0]);
		return;
	}
	int m2=(l2+r2)/2;
	psh(i);
	if(l1<=m2)
		upd(l1, x, 2*i, l2, m2);
	else
		upd(l1, x, 2*i+1, m2+1, r2);
	st[i][0]=max(st[2*i][0], st[2*i+1][0]);
	st[i][1]=max(st[2*i][1], st[2*i+1][1]);
}

int qry(int l1, int r1, int i=1, int l2=0, int r2=n-1) {
	if(l1<=l2&&r2<=r1)
		return st[i][1];
	int m2=(l2+r2)/2;
	psh(i);
	return max(l1<=m2?qry(l1, r1, 2*i, l2, m2):0, m2<r1?qry(l1, r1, 2*i+1, m2+1, r2):0);
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	auto ap=[](int x, int y) {
		if(2*y-x<n)
			ta[2*y-x].push_back({x, a[x]+a[y]});
	};
	cin >> n;
	for(int i=0; i<n; ++i) {
		cin >> a[i];
		l[i]=i-1;
		while(~l[i]&&a[l[i]]<a[i])
			l[i]=l[l[i]];
		if(~l[i])
			ap(l[i], i);
	}
	for(int i=n-1; ~i; --i) {
		ap(i, i+1);
		r[i]=i+1;
		while(r[i]<n&&a[r[i]]<a[i])
			r[i]=r[r[i]];
		ap(i, r[i]);
	}
	cin >> q;
	for(int i=0, l, r; i<q; ++i) {
		cin >> l >> r, --l, --r;
		tb[r].push_back({l, i});
	}
	memset(st, 0xc0, sizeof(st));
	for(int i=0; i<n; ++i) {
		for(array<int, 2> a : ta[i])
			upd(a[0], a[1]);
		app(1, a[i]);
		for(array<int, 2> b : tb[i])
			ans[b[1]]=qry(b[0], n-1);
	}
	for(int i=0; i<q; ++i)
		cout << ans[i] << "\n";
}
