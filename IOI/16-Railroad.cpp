#include "railroad.h"
#include <bits/stdc++.h>
using namespace std;

const int mxN=4e5;
int a[mxN], p[mxN];
array<int, 2> e[mxN];

int find(int x) {
	return x^p[x]?p[x]=find(p[x]):x;
}

bool join(int x, int y) {
	if((x=find(x))==(y=find(y)))
		return 0;
	p[x]=y;
	return 1;
}

long long plan_roller_coaster(vector<int> s, vector<int> t) {
	int n=s.size();
	vector<int> x=s;
	x.insert(x.end(), t.begin(), t.end());
	sort(x.begin(), x.end());
	iota(p, p+x.size(), 0);
	for(int i=0; i<n; ++i) {
		s[i]=lower_bound(x.begin(), x.end(), s[i])-x.begin();
		t[i]=lower_bound(x.begin(), x.end(), t[i])-x.begin();
		++a[s[i]];
		--a[t[i]];
		join(s[i], t[i]);
	}
	long long ans=0;
	for(int i=0; i+1<x.size(); ++i) {
		a[i+1]+=a[i];
		ans+=(long long)(x[i+1]-x[i])*max(a[i]-1, 0);
		if(a[i]^1)
			join(i, i+1);
		e[i]={x[i+1]-x[i], i};
	}
	sort(e, e+x.size()-1);
	for(int i=0; i<x.size()-1; ++i)
		if(join(e[i][1], e[i][1]+1))
			ans+=e[i][0];
	return ans;
}
