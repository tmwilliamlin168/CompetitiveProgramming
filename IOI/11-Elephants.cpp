/*
	- Use sqrt decomposition
	- For each block, maintain elephants in the block
	- For each elephant, maintain the minimum number of segments when using greedy covering to get outside the block, and also the position of the last segment
*/

#include "elephants.h"
#include <bits/stdc++.h>
using namespace std;

const int mxN=1.5e5, B=550, mxBC=(mxN-1)/B+1;
int n, l, *x, uc, bc, r[mxBC];
map<int, int> mp;
vector<int> v[mxBC];
vector<array<int, 2>> w[mxBC];

void init(int N, int L, int X[]) {
	n=N, l=L, x=X;
	for(int i=0; i<n; ++i)
		++mp[x[i]];
}

void bb(int i) {
	w[i]=vector<array<int, 2>>(v[i].size());
	for(int j1=(int)v[i].size()-1, j2=v[i].size(); ~j1; --j1) {
		while(v[i][j2-1]>v[i][j1]+l)
			--j2;
		w[i][j1]=j2<v[i].size()?array<int, 2>{w[i][j2][0]+1, w[i][j2][1]}:array<int, 2>{1, v[i][j1]+l};
	}
}
void bld() {
	bc=0;
	for(pair<int, int> p : mp) {
		if(!bc||v[bc-1].size()>=B)
			v[bc++].clear();
		v[bc-1].push_back(p.first);
	}
	for(int i=0; i<bc; ++i) {
		r[i]=i+1<bc?v[i+1][0]-1:1e9;
		bb(i);
	}
}

void upd(int x, bool a) {
	int c=-1;
	while(x>r[++c]);
	int p=lower_bound(v[c].begin(), v[c].end(), x)-v[c].begin();
	if(a)
		v[c].insert(v[c].begin()+p, x);
	else
		v[c].erase(v[c].begin()+p);
	bb(c);
}

int update(int i, int y) {
	if(uc++%B==0)
		bld();
	--mp[x[i]];
	if(!mp[x[i]]) {
		upd(x[i], 0);
		mp.erase(x[i]);
	}
	if(!mp[y])
		upd(y, 1);
	++mp[y];
	x[i]=y;
	int a=0;
	for(int i=0, c=-1; i<bc; ++i) {
		int p=upper_bound(v[i].begin(), v[i].end(), c)-v[i].begin();
		if(p<v[i].size()) {
			a+=w[i][p][0];
			c=w[i][p][1];
		}
	}
	return a;
}
