/*
	- 2 cases: whether an element is moved to the left or to the right
	- If i is moved left to j, the overall change is a[i]*(j-i)-a[i+1...j]
	- If i is moved right to j, the overall change is a[i]*(j-i)+a[j...i-1]
	- Convex hull trick is used for O(nlogn)
*/

#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int mxN=2e5;
int n, qt;
ll a[mxN], ans1, ans2, ps[mxN+1], m[mxN], b[mxN];

inline void al(ll mi, ll bi) {
	while(qt>=2&&(b[qt-1]-b[qt-2])/(m[qt-2]-m[qt-1])>=(bi-b[qt-1])/(m[qt-1]-mi))
		--qt;
	m[qt]=mi, b[qt]=bi;
	++qt;
}

inline ll qry(ll xi) {
	int lb=0, rb=qt-2;
	while(lb<=rb) {
		int mb=(lb+rb)/2;
		if(m[mb+1]*xi+b[mb+1]<m[mb]*xi+b[mb])
			rb=mb-1;
		else
			lb=mb+1;
	}
	return m[lb]*xi+b[lb];
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n;
	for(int i=0; i<n; ++i) {
		cin >> a[i];
		ps[i+1]=a[i]+ps[i];
		ans1+=(i+1)*a[i];
		al(i, -ps[i]);
		ans2=max(qry(a[i])+ps[i]-i*a[i], ans2);
	}
	qt=0;
	for(int i=n-1; i>=0; --i) {
		al(-i, -ps[i+1]);
		ans2=max(qry(-a[i])+ps[i+1]-i*a[i], ans2);
	}
	cout << ans1+ans2;
}
