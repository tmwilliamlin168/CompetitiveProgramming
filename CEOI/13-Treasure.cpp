/*
	- The query rectangles must have both sides >= n/2
*/

#include "treasure.h"
#include <bits/stdc++.h>
using namespace std;

const int mxN=100;
short a[mxN+1][mxN+1][mxN+1][mxN+1], b[mxN+1][mxN+1];

inline int qry(int r1, int c1, int r2, int c2) {
	if(!a[r1][c1][r2][c2])
		a[r1][c1][r2][c2]=countTreasure(r1, c1, r2, c2)+1;
	return a[r1][c1][r2][c2]-1;
}

void findTreasure(int n) {
	memset(a, 0, sizeof(a));
	for(int i=1; i<=n/2; ++i) {
		for(int j=1; j<=n/2; ++j)
			b[i][j]=qry(1, 1, n, n)-qry(i+1, 1, n, n)-qry(1, j+1, n, n)+qry(i+1, j+1, n, n);
		for(int j=n/2+1; j<=n; ++j)
			b[i][j]=qry(1, 1, n, j)-qry(i+1, 1, n, j);
	}
	for(int i=n/2+1; i<=n; ++i) {
		for(int j=1; j<=n/2; ++j)
			b[i][j]=qry(1, 1, i, n)-qry(1, j+1, i, n);
		for(int j=n/2+1; j<=n; ++j)
			b[i][j]=qry(1, 1, i, j);
	}
	for(int i=n; i>=1; --i) {
		for(int j=1; j<=n; ++j)
			b[i][j]-=b[i-1][j];
		for(int j=n; j>=1; --j)
			if(b[i][j]-=b[i][j-1])
				Report(i, j);
	}
}
