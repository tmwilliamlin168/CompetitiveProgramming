/*
	- Trick to compare angles with high precision (not sure if it is actually required)
		- https://stackoverflow.com/questions/16542042/fastest-way-to-sort-vectors-by-angle-without-actually-computing-that-angle
	- For each tree A
		- For each tree B such that B != A
			- Let B' be the reflection of B over A
			- The ray AB' cannot be crossed
		- The union of all rays from A divides the plane into n-1 sectors
		- Mark all camps that are not in the same sector as the starting position as impossible
	- O(n(n+c))
*/

#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pll pair<ll, ll>
#define fi first
#define se second

const int mxC=1e4, mxN=2e3;
int c, n, m;
ll w, h, sx, sy, cx[mxC], cy[mxC], tx[mxN], ty[mxN];
bool a1[mxC];

inline bool fc(pll a, pll b) {
	return a.fi*b.se<b.fi*a.se;
}

inline pll af(ll dx, ll dy) {
	return dy<0?pll(dx-abs(dx)+dy, abs(dx)-dy):pll(abs(dx)-dx+dy, abs(dx)+dy);
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> w >> h >> sx >> sy >> c;
	for(int i=0; i<c; ++i)
		cin >> cx[i] >> cy[i];
	cin >> n;
	for(int i=0; i<n; ++i)
		cin >> tx[i] >> ty[i];
	memset(a1, 1, c);
	for(int i=0; i<n; ++i) {
		pll pa=af(sx-tx[i], sy-ty[i]), pb={-3, 1}, pc={3, 1};
		for(int j=0; j<n; ++j) {
			if(j==i)
				continue;
			pll pd=af(tx[i]-tx[j], ty[i]-ty[j]);
			if(fc(pa, pd)&&fc(pd, pc))
				pc=pd;
			else if(fc(pd, pa)&&fc(pb, pd))
				pb=pd;
		}
		if(pb==pll(-3, 1)||pc==pll(3, 1)) {
			if(pb.fi==-3) {
				for(int j=0; j<n; ++j) {
					if(j==i)
						continue;
					pll pd=af(tx[i]-tx[j], ty[i]-ty[j]);
					if(fc(pb, pd))
						pb=pd;
				}
			} else {
				for(int j=0; j<n; ++j) {
					if(j==i)
						continue;
					pll pd=af(tx[i]-tx[j], ty[i]-ty[j]);
					if(fc(pd, pc))
						pc=pd;
				}
			}
			for(int j=0; j<c; ++j) {
				pll pd=af(cx[j]-tx[i], cy[j]-ty[i]);
				a1[j]&=fc(pb, pd)||fc(pd, pc);
			}
		} else {
			for(int j=0; j<c; ++j) {
				pll pd=af(cx[j]-tx[i], cy[j]-ty[i]);
				a1[j]&=fc(pb, pd)&&fc(pd, pc);
			}
		}
	}
	for(int i=0; i<c; ++i)
		m+=a1[i];
	cout << m << "\n";
	for(int i=0; i<c; ++i)
		if(a1[i])
			cout << i+1 << " ";
}
