#include "paint.h"
#include <bits/stdc++.h>
using namespace std;

const int mxN=1e5;
int d[mxN];
bool e[mxN], f[mxN];
vector<int> v[mxN];

int minimumInstructions(int n, int m, int k, vector<int> c, vector<int> a, vector<vector<int>> b) {
	for(int i=0; i<m; ++i)
		for(int j : b[i])
			v[j].push_back(i);
	for(int i=0; i<n; ++i) {
		for(int j : v[c[i]]) {
			if(++d[(j-i%m+m)%m]>=m)
				e[i]=1;
			f[(j-i%m+m)%m]=1;
		}
		if(i)
			for(int j : v[c[i-1]])
				if(!f[(j-i%m+1+m)%m])
					d[(j-i%m+1+m)%m]=0;
		for(int j : v[c[i]])
			f[(j-i%m+m)%m]=0;
	}
	int i=n-1, x=0, j;
	for(; i>=0; ++x) {
		for(j=i; j<i+m&&!e[j]; ++j);
		if(j>=i+m)
			return -1;
		i=j-m;
	}
	return x;
}
