/*
	- Use binary indexed tree for order statistics
	- Each element can only be removed once so when Dima hits the table just remove them one by one
*/

#include <bits/stdc++.h>
using namespace std;

const int mxN=1e6;
int n, m, n2, a[mxN], b[mxN], ft[mxN+1], c;

inline void upd(int i, int x) {
	for(++i; i<=mxN; i+=i&-i)
		ft[i]+=x;
}

inline int qry(int i) {
	int r=0;
	for(; i; i-=i&-i)
		r+=ft[i];
	return r;
}

inline int bs(int x) {
	int r=0, s=0;
	for(int i=19; i>=0; --i) {
		if(r+(1<<i)<=mxN&&s+ft[r+(1<<i)]<x) {
			r^=1<<i;
			s+=ft[r];
		}
	}
	return r;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> m;
	for(int i=0; i<m; ++i)
		cin >> a[i];
	while(n--) {
		cin >> c;
		if(c==-1) {
			int i=-1, n3=qry(mxN);
			while(i+1<m&&a[i+1]<=n3)
				++i;
			for(; i>=0; --i)
				upd(bs(a[i]), -1);
		} else {
			upd(n2, 1);
			b[n2++]=c;
		}
	}
	if(qry(mxN)) {
		for(int i=1; i<=mxN; ++i) {
			ft[i]+=ft[i-(i&-i)];
			if(ft[i]>ft[i-1])
				cout << b[i-1];
		}
	} else
		cout << "Poor stack!";
}
