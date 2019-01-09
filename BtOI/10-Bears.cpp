/*
	- Binary search on D
	- Initially, the set of points that should not be accessible is a square with side length 2*(D-1)
	- However, if a segment intersects that set of points, we need to increase the set of points to include the segment
	- Notice that if there exists a point such that two of its neighbors are in the set, then it must also be in the set
	- So after adding a segment, the new set of points will be the minimum bounding rectangle
	- We can prove that if there are no more segments "sticking out" of the rectangle, BEARs will not be able to reach in this rectangle if it is outside
*/

#include <bits/stdc++.h>
using namespace std;

const int mxN=500;
int a, b, n, xa[mxN], ya[mxN], xb[mxN], yb[mxN];

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> a >> b >> n;
	for(int i=0; i<n; ++i)
		cin >> xa[i] >> ya[i] >> xb[i] >> yb[i];
	int lb=0, rb=1e6;
	while(lb<rb) {
		int mb=(lb+rb+1)/2, c2=mb-1, d2=c2, c1=-c2, d1=-d2;
		auto ir=[&](int x, int y) {
			return c1<=x&&x<=c2&&d1<=y&&y<=d2;
		};
		for(int it=0; it<n; ++it) {
			for(int i=0; i<n; ++i) {
				if(!ir(xa[i], ya[i])&&!ir(xb[i], yb[i])&&(min(xa[i], xb[i])>0||max(xa[i], xb[i])<0||!ir(0, ya[i]))&&(min(ya[i], yb[i])>0||max(ya[i], yb[i])<0||!ir(xa[i], 0)))
					continue;
				c1=min({xa[i], xb[i], c1});
				c2=max({xa[i], xb[i], c2});
				d1=min({ya[i], yb[i], d1});
				d2=max({ya[i], yb[i], d2});
			}
		}
		if(ir(a, b))
			rb=mb-1;
		else
			lb=mb;
	}
	cout << lb;
}
