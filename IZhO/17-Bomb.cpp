/*
	- Some necessary conditions:
		- Minimum maximal contiguous row / column of 1s, MAXW / MAXH
		- For each 1 to the left or right of a 0, calculate the maximum height a[w] of a rectangle for a given width w
		- b[w] = min over all a[w]
	- Those are also sufficient, we can prove that we can choose wXh such that w <= MAXW, h <= MAXH, and h <= b[w] to cover any 1
	- Find column of length h [a, b] (b-a+1 = h, a <= i <= b) consisting of 1s containing the given cell (i, j), guaranteed to exist since h <= MAXH
	- If any one of the cells (i, j+[1, w]) is 0 (consider the first one)
		- wXh rectangle exists since h <= b[w] <= a[w] for that cell
	- Proceed by induction on rows, until we conclude that all cells ([a, b], j+[1, w]) are 1
*/

#include <bits/stdc++.h>
using namespace std;

const int mxN=2500;
int n, m, mxw=mxN, mxh=mxN, u[mxN][mxN], d[mxN][mxN], a[mxN], ans;
string g[mxN];

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> n >> m;
	for(int i=0; i<n; ++i) {
		cin >> g[i];
		for(int j=0, w=0; j<m; ++j) {
			w=g[i][j]&1?w+1:0;
			if(w&&(j+1>=m||g[i][j+1]&1^1))
				mxw=min(w, mxw);
		}
	}
	for(int j=0; j<m; ++j) {
		for(int i=0, h=0; i<n; ++i) {
			h=g[i][j]&1?h+1:0;
			if(h&&(i+1>=n||g[i+1][j]&1^1))
				mxh=min(h, mxh);
			u[i][j]=i&&g[i-1][j]&1?u[i-1][j]:i;
		}
		for(int i=n-1; ~i; --i)
			d[i][j]=i<n-1&&g[i+1][j]&1?d[i+1][j]:i;
	}
	for(int i=0; i<mxw; ++i)
		a[i]=mxh;
	auto c=[]() {
		for(int i=0; i<n; ++i) {
			for(int j=0; j<m; ++j) {
				if(j&&g[i][j-1]&1||g[i][j]&1^1)
					continue;
				for(int k=0, l=0, r=n; k<mxw; ++k) {
					l=max(u[i][j+k], l);
					r=min(d[i][j+k], r);
					a[k]=min(r-l+1, a[k]);
				}
			}
		}
	};
	c();
	for(int i=0; i<n; ++i) {
		reverse(g[i].begin(), g[i].end());
		reverse(u[i], u[i]+m);
		reverse(d[i], d[i]+m);
	}
	c();
	for(int i=0; i<mxw; ++i)
		ans=max((i+1)*a[i], ans);
	cout << ans;
}
