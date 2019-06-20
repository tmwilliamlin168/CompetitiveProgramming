/*
	- Subtask 2
		- Binary search by answer
		- Calculate for each point (x, y), the minimum cost to remove all obstacles for a square starting at that point
		- Sliding window with a segment tree which supports range add updates and range min queries
		- O((m+plogm)logm)
	- Subtask 3
		- Notice that opt[l]<=opt[l+1], so we can use 2 pointers
		- Use a segment tree which supports range add updates and queries for maximum number of consecutive 0s
		- We increase r until r-l is the greater dimension of the rectangle
		- O(m+plogm)
*/

#include <bits/stdc++.h>
using namespace std;

const int mxP=4e5, mxM=1e6;
int m, n, b, p, ans;
vector<array<int, 3>> r1[mxM+1], r2[mxM+1];

namespace subtask2 {
	int st[1<<21], lz[1<<21];

	void app(int i, int x) {
		st[i]+=x;
		lz[i]+=x;
	}

	void psh(int i) {
		app(2*i, lz[i]);
		app(2*i+1, lz[i]);
		lz[i]=0;
	}

	void upd(int l1, int r1, int x, int i=1, int l2=0, int r2=n-1) {
		if(l1<=l2&&r2<=r1) {
			app(i, x);
			return;
		}
		int m2=(l2+r2)/2;
		psh(i);
		if(l1<=m2)
			upd(l1, r1, x, 2*i, l2, m2);
		if(m2<r1)
			upd(l1, r1, x, 2*i+1, m2+1, r2);
		st[i]=min(st[2*i], st[2*i+1]);
	}

	void solve() {
		int lb=0, rb=n;
		while(lb<rb) {
			int mb=(lb+rb+1)/2;
			bool ok=0;
			memset(st, 0, sizeof(st));
			memset(lz, 0, sizeof(lz));
			if(mb>1)
				upd(n-mb+1, n-1, 3e8);
			for(int i=0; i<mb-1; ++i)
				for(array<int, 3> a : r1[i])
					upd(a[0]-mb+1, a[1], a[2]);
			for(int i=0; i<=m-mb&&!ok; ++i) {
				for(array<int, 3> a : r1[i+mb-1])
					upd(a[0]-mb+1, a[1], a[2]);
				for(array<int, 3> a : r2[i])
					upd(a[0]-mb+1, a[1], -a[2]);
				ok=st[1]<=b;
			}
			if(ok)
				lb=mb;
			else
				rb=mb-1;
		}
		ans=lb;
	}
}

namespace subtask3 {
	array<int, 4> st[1<<21];

	void cmb(int i, int l, int m, int r) {
		int lt=st[2*i][1], ll=st[2*i][2], lr=st[2*i][3], rt=st[2*i+1][1], rl=st[2*i+1][2], rr=st[2*i+1][3];
		if(st[2*i][0])
			lt=ll=lr=0;
		if(st[2*i+1][0])
			rt=rl=rr=0;
		st[i]={st[i][0], max({lt, rt, lr+rl}), ll+(ll<m-l+1?0:rl), rr+(rr<r-m?0:lr)};
	}

	void bld(int i=1, int l=0, int r=n-1) {
		if(l==r) {
			st[i]={0, 1, 1, 1};
			return;
		}
		int m=(l+r)/2;
		bld(2*i, l, m);
		bld(2*i+1, m+1, r);
		cmb(i, l, m, r);
	}

	void upd(int l1, int r1, int x, int i=1, int l2=0, int r2=n-1) {
		if(l1<=l2&&r2<=r1) {
			st[i][0]+=x;
			return;
		}
		int m2=(l2+r2)/2;
		if(l1<=m2)
			upd(l1, r1, x, 2*i, l2, m2);
		if(m2<r1)
			upd(l1, r1, x, 2*i+1, m2+1, r2);
		cmb(i, l2, m2, r2);
	}

	void solve() {
		r1[m].push_back({0, n-1});
		bld();
		for(int i1=0, i2=0; i1<m; ++i1) {
			for(array<int, 3> a : r2[i1])
				upd(a[0], a[1], -1);
			for(; (st[1][0]?0:st[1][1])>=i2-i1; ++i2) {
				ans=max(i2-i1, ans);
				for(array<int, 3> a : r1[i2])
					upd(a[0], a[1], 1);
			}
		}
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> m >> n >> b >> p;
	for(int i=0, xa, ya, xb, yb, c; i<p; ++i) {
		cin >> xa >> ya >> xb >> yb >> c, --xa, --ya, --xb, --yb;
		r1[xa].push_back({ya, yb, c});
		r2[xb+1].push_back({ya, yb, c});
	}
	if(b)
		subtask2::solve();
	else
		subtask3::solve();
	cout << ans;
}
