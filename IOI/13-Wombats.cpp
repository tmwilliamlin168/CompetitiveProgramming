/*
	- Simple solution: we can use a segment tree
		- Each segment stores a[i][j] = min cost from top row column i to bottom row column j
	- 2 problems
		- Merging 2 segments naively is O(c^3)
			- We can prove that after fixing i, the column of the midpoint is increasing with respect to j
			- Knuth's optimization, O(c^2) for merging
		- 2*r*c*c ints uses too much memory
			- Divide the rows into blocks of 20
			- Build the segment tree on those blocks
			- Do brute force within each block
			- Also improves runtime
*/

#include "wombats.h"
#include <bits/stdc++.h>
using namespace std;

const int r=5e3, c=200, bs=10, bc=r/bs, sts=1024;
int h[r][c-1], v[r][c], st[sts][c][c], o[c+1];

void upd(int l1, int r1, int i=1, int l2=0, int r2=bc-1) {
	if(l2==r2) {
		memset(st[i], 0x3f, sizeof(st[i]));
		for(int j=0; j<c; ++j) {
			st[i][j][j]=0;
			for(int k=l2*bs; k<(l2+1)*bs; ++k) {
				for(int l=1; l<c; ++l)
					st[i][j][l]=min(st[i][j][l-1]+h[k][l-1], st[i][j][l]);
				for(int l=c-1; l; --l)
					st[i][j][l-1]=min(st[i][j][l]+h[k][l-1], st[i][j][l-1]);
				for(int l=0; l<c; ++l)
					st[i][j][l]+=v[k][l];
			}
		}
		return;
	}
	int m2=(l2+r2)/2;
	if(l1<=m2)
		upd(l1, r1, 2*i, l2, m2);
	if(m2<r1)
		upd(l1, r1, 2*i+1, m2+1, r2);
	memset(o, 0, 4*c);
	for(int j1=0; j1<c; ++j1) {
		for(int j2=c-1; ~j2; --j2) {
			array<int, 2> d{INT_MAX, 0};
			for(int k=o[j2]; k<=o[j2+1]; ++k)
				d=min(array<int, 2>{st[2*i][j1][k]+st[2*i+1][k][j2], -k}, d);
			st[i][j1][j2]=d[0];
			o[j2]=-d[1];
		}
	}
}

void init(int r, int c, int h[5000][200], int v[5000][200]) {
	memset(::h, 0x3f, sizeof(::h));
	for(int i=0; i<r; ++i)
		for(int j=0; j<c-1; ++j)
			::h[i][j]=h[i][j];
	for(int i=0; i<r-1; ++i)
		for(int j=0; j<c; ++j)
			::v[i][j]=v[i][j];
	o[::c]=::c-1;
	upd(0, bc-1);
}

void changeH(int p, int q, int w) {
	h[p][q]=w;
	upd(p/bs, p/bs);
}

void changeV(int p, int q, int w) {
	v[p][q]=w;
	upd(p/bs, p/bs);
}

int escape(int a, int b) {
	return st[1][a][b];
}
