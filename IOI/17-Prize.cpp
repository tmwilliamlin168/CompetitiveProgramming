#include "prize.h"
#include <bits/stdc++.h>
using namespace std;

const int mxN=2e5;
int n, a, ft[mxN+1];
vector<int> v;

void upd(int i) {
	for(++i; i<=n; i+=i&-i)
		++ft[i];
}

int qry(int i) {
	int r=0;
	for(; i; i-=i&-i)
		r+=ft[i];
	return r;
}

int dc(int l=0, int r=n-1, int sl=0, int sr=a) {
	if(l>r)
		return -1;
	int ml=(l+r)/2, mr=ml;
	vector<int> b;
	for(; ml>=l; --ml) {
		if(qry(r+1)-qry(l)>=sr-sl)
			return -1;
		if(qry(ml+1)-qry(ml))
			continue;
		b=ask(ml);
		int c=b[0]+b[1];
		if(!c)
			return ml;
		if(c>a) {
			a=c;
			for(int vi : v)
				upd(vi);
			v.clear();
			return dc();
		}
		if(c==a) {
			v.push_back(ml);
			b[1]=b[0]+mr-ml;
			break;
		}
		if(c<a)
			upd(ml);
	}
	if(ml<l)
		b[1]=sl+mr-ml;
	int rl=dc(l, ml-1, sl, b[0]);
	return ~rl?rl:dc(mr+1, r, b[1], sr);
}

int find_best(int N) {
	n=N;
	vector<int> b=ask(n-1);
	a=b[0]+b[1];
	return a?dc():n-1;
}
