/*
	- We can classify the archers into 3 types based on their rank relative to archer 1
	- If archer 1 has rank 1, the answer is just n
	- If archer 1 has rank > n+1, he will reach his final destination within 2n rounds and stay there forever
	- Else, after 2*n rounds, he will just keep rotating
	- Both are similar to bracket matching, and can be solved using prefix sums
	- In order to calculate efficiently for all starting positions, we can use a segment tree
	- We can also add binary search as mentioned in https://ioinformatics.org/files/ioi2009solutions.pdf
		- I suspect, when implemented properly, we can achieve O(n)
*/

#include <bits/stdc++.h>
using namespace std;

const int mxN=2e5;
int n, r, a[2*mxN], st[1<<21], lz[1<<21];
array<int, 2> ans{1<<30};

void bld(int i=1, int l=0, int r=3*n) {
	if(l==r) {
		st[i]=-l;
		return;
	}
	int m=(l+r)/2;
	bld(2*i, l, m);
	bld(2*i+1, m+1, r);
	st[i]=max(st[2*i], st[2*i+1]);
}

void app(int i, int x) {
	st[i]+=x;
	lz[i]+=x;
}

void psh(int i) {
	app(2*i, lz[i]);
	app(2*i+1, lz[i]);
	lz[i]=0;
}

void upd(int l1, int r1, int x, int i=1, int l2=0, int r2=3*n) {
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
	st[i]=max(st[2*i], st[2*i+1]);
}

void upd2(int i, int x) {
	upd(i, 3*n, x);
	upd(i+n, 3*n, x);
	upd(i+2*n, 3*n, x);
}

int qry(int l1, int r1, int i=1, int l2=0, int r2=3*n) {
	if(l1<=l2&&r2<=r1)
		return st[i];
	int m2=(l2+r2)/2;
	psh(i);
	return max(l1<=m2?qry(l1, r1, 2*i, l2, m2):-1e9, m2<r1?qry(l1, r1, 2*i+1, m2+1, r2):-1e9);
}

int bs(int l1, int r1, int x, int i=1, int l2=0, int r2=3*n) {
	if(st[i]<=x)
		return -1;
	if(l2==r2)
		return l2;
	int m2=(l2+r2)/2;
	psh(i);
	int a=m2<r1?bs(l1, r1, x, 2*i+1, m2+1, r2):-1;
	return ~a?a:bs(l1, r1, x, 2*i, l2, m2);
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> n >> r;
	for(int i=0; i<2*n; ++i)
		cin >> a[i];
	bld();
	if(a[0]>n+1) {
		upd2(1, 1);
		for(int i=1; i<2*n; ++i)
			if(a[i]>a[0])
				upd2(i/2+1, 1);
		for(int i=0; i<n; ++i) {
			if(i) {
				if(a[2*i]>a[0]) {
					upd2(i+1, -1);
					upd2(i, 1);
				}
			}
			ans=min(array<int, 2>{bs(0, i+n, qry(i+1+n, 3*n))%n, -i}, ans);
		}
	} else if(a[0]>1) {
		upd2(n, -1);
		int fg=n;
		for(int i=1; i<2*n; ++i) {
			if(a[i]<a[0]) {
				upd2(n-i/2, 1);
				fg=min(i/2, fg);
			}
		}
		for(int i=0; i<n; ++i) {
			if(i) {
				if(a[2*i]<a[0]) {
					upd2(n-i, -1);
					upd2(n-i+1, 1);
					fg=min(i-1, fg);
				}
			}
			ans=min(array<int, 2>{(i-(r-max(2*n-1-i-bs(0, 2*n-1-i, qry(2*n-i, 3*n)), fg-i))%n+n)%n, -i}, ans);
		}
	} else
		ans={0, -n+1};
	cout << -ans[1]+1;
}
