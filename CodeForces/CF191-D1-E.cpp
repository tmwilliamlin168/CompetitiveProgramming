/*
	- Binary search, implement the function that returns how many subarrays have sum >= x
	- Binary indexed tree to answer how many prefix sums are <= x
*/

#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int mxN=1e5;
int n;
ll k, ps[mxN+1], sps[mxN+1], ft[mxN+2], lb=-1e14, rb=1e14, mb, k2;

inline void upd(int i) {
	for(++i; i<=n+1; i+=i&-i)
		++ft[i];
}

inline int qry(int i) {
	int r=0;
	for(; i; i-=i&-i)
		r+=ft[i];
	return r;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> k;
	for(int i=1; i<=n; ++i) {
		cin >> ps[i];
		sps[i]=ps[i]+=ps[i-1];
	}
	sort(sps, sps+n+1);
	while(lb<=rb) {
		mb=(lb+rb)/2, k2=0;
		memset(ft, 0, sizeof(ft));
		upd(lower_bound(sps, sps+n+1, 0)-sps);
		for(int i=1; i<=n; ++i) {
			k2+=qry(upper_bound(sps, sps+n+1, ps[i]-mb)-sps);
			upd(lower_bound(sps, sps+n+1, ps[i])-sps);
		}
		if(k2>=k)
			lb=mb+1;
		else
			rb=mb-1;
	}
	cout << rb;
}
