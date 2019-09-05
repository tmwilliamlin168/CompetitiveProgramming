#include "hiccup.h"
#include <bits/stdc++.h>
using namespace std;

int a[1000000], lb=0, rb=1000000, mb;

bool chk(string &s, int l, int r, int b=0) {
	if(l>r)
		return 1;
	for(; s[r]=='!'; --r, ++b);
	return b<mb?0:chk(s, a[r]+1, r-1)&&chk(s, l, a[r]-1, b-mb);
}

int HicCup(string s) {
	int n=s.size();
	if(s[0]=='!')
		return -1;
	for(int i=0; i+1<n; ++i)
		if(s[i]=='H'&&s[i+1]=='!')
			return -1;
	vector<int> t;
	for(int i=0; i<n; ++i) {
		if(s[i]=='C') {
			if(t.empty())
				return -1;
			a[i]=t.back();
			t.pop_back();
		} else if(s[i]=='H')
			t.push_back(i);
	}
	if(t.size())
		return -1;
	while(lb<rb) {
		mb=(lb+rb+1)/2;
		if(chk(s, 0, n-1))
			lb=mb;
		else
			rb=mb-1;
	}
	return lb;
}
