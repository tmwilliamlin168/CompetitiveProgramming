/*
	- Binary search, answer maximum area of rectangle if some cells are blocked
	- Brute force the n possible rows to start the rectangle
	- Calculate with dp for each (i, j) the maximum number of times you can increment j before reaching a blocked cell
	- Now there is a histogram, and the maximum area of a rectangle in a histogram can be solved in O(m)
*/

#include <bits/stdc++.h>
using namespace std;

const int mxN=1000;
int n, m, k, a[mxN][mxN], lb=1, rb=1e9, mb, a2, a3, b[2][mxN], l[mxN], r[mxN];

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> m >> k;
	for(int i=0; i<n; ++i)
		for(int j=0; j<m; ++j)
			cin >> a[i][j];
	while(lb<=rb) {
		mb=(lb+rb)/2, a3=0;
		memset(b[n&1], 0, 4*m);
		for(int i=n-1; i>=0; --i) {
			for(int j=0; j<m; ++j)
				b[i&1][j]=a[i][j]<mb?0:b[i&1^1][j]+1;
			for(int j=0; j<m; ++j) {
				l[j]=j-1;
				while(l[j]>=0&&b[i&1][l[j]]>=b[i&1][j])
					l[j]=l[l[j]];
			}
			for(int j=m-1; j>=0; --j) {
				r[j]=j+1;
				while(r[j]<m&&b[i&1][r[j]]>=b[i&1][j])
					r[j]=r[r[j]];
				a3=max(b[i&1][j]*(r[j]-l[j]-1), a3);
			}
		}
		if(a3>=k) {
			lb=mb+1;
			a2=a3;
		} else
			rb=mb-1;
	}
	cout << rb << " " << a2;
}
