/*
	- n bits max
*/

#include "advisor.h"
#include <bits/stdc++.h>
using namespace std;

const int mxN=1e5;
int a[2*mxN], nxt[2*mxN], d[mxN];
bool b[2*mxN];

void ComputeAdvice(int *c, int n, int k, int m) {
	iota(a, a+k, 0);
	memcpy(a+k, c, 4*n);
	map<int, int> mp;
	for(int i=0; i<n; ++i)
		mp[i]=1e9;
	for(int i=n+k-1; ~i; --i) {
		nxt[i]=mp[a[i]];
		mp[a[i]]=i;
	}
	set<array<int, 2>> s;
	for(int i=0; i<k; ++i)
		s.insert({nxt[i], i});
	for(int i=k; i<n+k; ++i) {
		if((*s.begin())[0]>i) {
			array<int, 2> c=*--s.end();
			s.erase(--s.end());
			b[c[1]]=1;
		} else
			s.erase(s.begin());
		s.insert({nxt[i], i});
	}
	memset(d, -1, 4*n);
	vector<int> v;
	for(int i=0; i<k; ++i) {
		v.push_back(i);
		d[i]=i;
	}
	for(int i=k; i<n+k; ++i) {
		if(d[a[i]]<0) {
			while(1) {
				int u=v.back();
				v.pop_back();
				if(b[d[u]]) {
					d[u]=-1;
					break;
				}
				WriteAdvice(0);
			}
			WriteAdvice(1);
		}
		d[a[i]]=i;
		v.push_back(a[i]);
	}
}
