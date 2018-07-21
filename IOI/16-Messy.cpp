/*
	- 896 = 128*7 ~ nlogn
	- http://www.ioinformatics.org/locations/ioi16/contest/IOI2016_analysis.pdf
*/

#include "messy.h"
#include <bits/stdc++.h>
using namespace std;

string s;
int n;
vector<int> ans;

void rec1(int l, int r) {
	if(l==r)
		return;
	int m=(l+r)/2;
	for(int i=0; i<l; ++i)
		s[i]='1';
	for(int i=l; i<=r; ++i)
		s[i]='0';
	for(int i=r+1; i<n; ++i)
		s[i]='1';
	for(int i=l; i<=m; ++i) {
		s[i]='1';
		add_element(s);
		s[i]='0';
	}
	rec1(l, m);
	rec1(m+1, r);
}

void rec2(int l, int r, vector<int> &v) {
	if(l==r) {
		ans[v[0]]=l;
		return;
	}
	int m=(l+r)/2;
	for(int i=0; i<n; ++i)
		s[i]='1';
	for(int i : v)
		s[i]='0';
	vector<int> vl, vr;
	for(int i : v) {
		s[i]='1';
		if(check_element(s))
			vl.push_back(i);
		else
			vr.push_back(i);
		s[i]='0';
	}
	rec2(l, m, vl);
	rec2(m+1, r, vr);
}

vector<int> restore_permutation(int n2, int w, int r) {
	n=n2;
	s="";
	for(int i=0; i<n; ++i)
		s+='0';
	rec1(0, n-1);
	compile_set();
	vector<int> v;
	for(int i=0; i<n; ++i)
		v.push_back(i);
	ans=vector<int>(n);
	rec2(0, n-1, v);
	return ans;
}
