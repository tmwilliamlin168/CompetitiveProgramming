/*
	- Consider when an element at index i is the maximum
	- You can make that specific element the maximum if you include all intervals containing i
	- Simple solution: do bitset knapsack dp for each i => O(qn^2logn/32)
	- We can put the intervals on a segment tree and do a dfs from the root
	- Doing bitset knapsack dp from the root to the leaf nodes makes it O(n(n+qlogn)/32)
*/

#include <bits/stdc++.h>
using namespace std;

const int mxN=1e4;
int n, q, l, r, x;
vector<int> st[1<<15];
bitset<mxN+1> a1;

void add(int l1, int r1, int x, int i=1, int l2=0, int r2=n-1) {
	if(l1<=l2&&r2<=r1) {
		st[i].push_back(x);
		return;
	}
	int m2=(l2+r2)/2;
	if(l1<=m2)
		add(l1, r1, x, 2*i, l2, m2);
	if(m2<r1)
		add(l1, r1, x, 2*i+1, m2+1, r2);
}

void b(bitset<mxN+1> bs, int i=1, int l2=0, int r2=n-1) {
	for(int vi : st[i])
		bs|=bs<<vi;
	if(l2==r2) {
		a1|=bs;
		return;
	}
	int m2=(l2+r2)/2;
	b(bs, 2*i, l2, m2);
	b(bs, 2*i+1, m2+1, r2);
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> q;
	while(q--) {
		cin >> l >> r >> x, --l, --r;
		add(l, r, x);
	}
	b(bitset<mxN+1>(1));
	cout << a1.count() << "\n";
	for(int i=1; i<=n; ++i)
		if(a1[i])
			cout << i << " ";
}
