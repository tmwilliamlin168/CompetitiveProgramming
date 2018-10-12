/*
	- After subtracting i for the ith village, the range updates are trivial
*/

#include <bits/stdc++.h>
using namespace std;

const int mxN=3e5;
int n, m, st[2*mxN], l, r, x;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> m;
	while(m--) {
		cin >> l >> r >> x, --l, x+=n-l;
		for(l+=n, r+=n; l<r; ++l/=2, r/=2) {
			if(l&1)
				st[l]=max(x, st[l]);
			if(r&1)
				st[r-1]=max(x, st[r-1]);
		}
	}
	for(int i=1; i<n; ++i) {
		st[2*i]=max(st[i], st[2*i]);
		st[2*i+1]=max(st[i], st[2*i+1]);
	}
	for(int i=0; i<n; ++i)
		cout << max(st[n+i]-n+i, 0) << " ";
}
