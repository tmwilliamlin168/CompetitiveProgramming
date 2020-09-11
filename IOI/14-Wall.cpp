#include "wall.h"
#include <bits/stdc++.h>
using namespace std;

int stl[1<<22], str[1<<22];

void app(int i, int xl, int xr) {
	stl[i]=min(max(stl[i], xl), xr);
	str[i]=min(max(str[i], xl), xr);
}

void psh(int i) {
	app(2*i, stl[i], str[i]);
	app(2*i+1, stl[i], str[i]);
	stl[i]=0;
	str[i]=1e5;
}

void upd(int l1, int r1, int xl, int xr, int i, int l2, int r2) {
	if(l1<=l2&&r2<=r1) {
		app(i, xl, xr);
		return;
	}
	int m2=(l2+r2)/2;
	psh(i);
	if(l1<=m2)
		upd(l1, r1, xl, xr, 2*i, l2, m2);
	if(m2<r1)
		upd(l1, r1, xl, xr, 2*i+1, m2+1, r2);
}

void bld(int* x, int i, int l2, int r2) {
	if(l2==r2) {
		x[l2]=stl[i];
		return;
	}
	int m2=(l2+r2)/2;
	psh(i);
	bld(x, 2*i, l2, m2);
	bld(x, 2*i+1, m2+1, r2);
}

void buildWall(int n, int k, int* op, int* left, int* right, int* height, int* finalHeight) {
	for(int i=0; i<k; ++i)
		upd(left[i], right[i], op[i]^2?height[i]:0, op[i]^1?height[i]:1e5, 1, 0, n-1);
	bld(finalHeight, 1, 0, n-1);
}
