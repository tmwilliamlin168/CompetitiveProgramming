#include "minerals.h"
#include <bits/stdc++.h>
using namespace std;

bool qry(int x) {
	static int lst=0;
	int ans=Query(x), c=lst^ans;
	lst=ans;
	return c;
}

void solve(vector<int> l, vector<int> r, bool f) {
	int n=l.size(), m=floor(0.35*n);
	if(n<2) {
		Answer(l[0], r[0]);
		return;
	}
	if(f) {
		m=n-m-2;
		for(int i=n-1; i>m; --i)
			qry(l[i]);
	} else
		for(int i=0; i<=m; ++i)
			qry(l[i]);
	vector<int> v[2];
	random_shuffle(r.begin(), r.end());
	for(int x : r)
		v[v[0].size()>m||v[1].size()<n-m-1&&qry(x)].push_back(x);
	solve(vector<int>(l.begin(), l.begin()+m+1), v[0], 1);
	solve(vector<int>(l.begin()+m+1, l.end()), v[1], 0);
}

void Solve(int n) {
	vector<int> v[2];
	for(int i=1; i<=2*n; ++i)
		v[qry(i)].push_back(i);
	solve(v[0], v[1], 1);
}
