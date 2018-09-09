#include "doll.h"
#include <bits/stdc++.h>
using namespace std;

int n, p=1, sti=1;
vector<int> x(1<<19), y(1<<19);
bool b[1<<19];

int bld(int l, int r) {
	if(l>=r)
		return 0;
	if(r<p-n)
		return -1;
	int ts=sti++, m=(l+r)/2;
	x[ts-1]=bld(l, m);
	y[ts-1]=bld(m+1, r);
	return -ts;
}

void pt(int i, int j) {
	int &a=b[-i]?y[-i-1]:x[-i-1];
	b[-i]=!b[-i];
	if(!a)
		a=j;
	else
		pt(a, j);
}

void create_circuit(int m, vector<int> a) {
	n=a.size();
	while(p<n)
		p*=2;
	bld(0, p-1);
	for(int i=1; i<n; ++i)
		pt(-1, a[i]);
	if(n&1)
		pt(-1, -1);
	pt(-1, 0);
	vector<int> c(m+1, -1);
	c[0]=a[0];
	x.resize(sti);
	y.resize(sti);
	answer(c, x, y);
}
