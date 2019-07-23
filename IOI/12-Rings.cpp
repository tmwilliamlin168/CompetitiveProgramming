/*
	- http://blog.brucemerry.org.za/2012/09/ioi-2012-day-1-analysis.html
*/

#include "grader.h"
#include <bits/stdc++.h>
using namespace std;

const int mxN=1e6;
int n, c[4]={-1};
vector<int> adj[mxN];

struct dsu {
	int p[mxN], s[mxN], d[mxN], nc, cl, a=-1;
	void init() {
		iota(p, p+n, 0);
		fill(s, s+n, 1);
	}
	int find(int x) {
		return x^p[x]?p[x]=find(p[x]):x;
	}
	void join(int x, int y) {
		++d[x], ++d[y];
		if(d[x]>=3)
			a=x;
		if(d[y]>=3)
			a=y;
		if((x=find(x))==(y=find(y))) {
			if(!nc)
				cl=s[x];
			++nc;
			return;
		}
		if(s[x]<s[y])
			swap(x, y);
		p[y]=x;
		s[x]+=s[y];
	}
} d1, d2[4];

void Init(int N) {
	n=N;
	d1.init();
	for(int i=0; i<4; ++i)
		d2[i].init();
}

void Link(int a, int b) {
	if(c[0]<0) {
		adj[a].push_back(b);
		adj[b].push_back(a);
		d1.join(a, b);
		if(~d1.a) {
			c[3]=d1.a;
			for(int i=0; i<3; ++i)
				c[i]=adj[d1.a][i];
			for(int i=0; i<n; ++i)
				for(int j : adj[i])
					if(i<j)
						Link(i, j);
		}
	} else
		for(int i=0; i<4; ++i)
			if(c[i]^a&&c[i]^b)
				d2[i].join(a, b);
}

int CountCritical() {
	int ans=0;
	if(~c[0])
		for(int i=0; i<4; ++i)
			ans+=!d2[i].nc&&d2[i].a<0;
	else if(d1.nc<2)
		ans=d1.nc?d1.cl:n;
	return ans;
}
