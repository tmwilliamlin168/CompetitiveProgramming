/*
	- https://codeforces.com/blog/entry/51010
*/

#include "park.h"
#include <bits/stdc++.h>
using namespace std;

const int mxN=1400;
int n, p[mxN], a[mxN], d[mxN], e[mxN][7];
vector<int> dl;
bool vis[mxN];

void ae(int u, int v) {
	e[u][d[u]++]=v;
	e[v][d[v]++]=u;
	Answer(min(u, v), max(u, v));
}

void dfs(int u) {
	vis[u]=1;
	dl.push_back(u);
	for(int i=0; i<d[u]; ++i)
		if(!vis[e[u][i]]&&a[e[u][i]]!=3)
			dfs(e[u][i]);
}

void b(int u) {
	a[u]=2;
	while(1) {
		for(int i=0; i<n; ++i)
			p[i]=a[i]==1;
		p[u]=1;
		if(Ask(0, u, p))
			break;
		int lb=0, rb=n-1;
		while(lb<rb) {
			int mb=(lb+rb)/2;
			for(int i=0; i<n; ++i)
				p[i]=a[i]==1||!a[i]&&i<=mb;
			p[u]=1;
			if(Ask(0, u, p))
				rb=mb;
			else
				lb=mb+1;
		}
		b(lb);
	}
	vector<int> f{0};
	for(int i=0; i<f.size(); ++i) {
		if(a[f[i]]==3)
			continue;
		memset(vis, 0, n);
		dl.clear();
		dfs(f[i]);
		memset(p, 0, 4*n);
		for(int di : dl)
			p[di]=1;
		p[u]=1;
		if(!Ask(min(f[i], u), max(f[i], u), p))
			continue;
		int lb=0, rb=dl.size()-1;
		while(lb<rb) {
			int mb=(lb+rb)/2;
			memset(p, 0, 4*n);
			for(int j=0; j<=mb; ++j)
				p[dl[j]]=1;
			p[u]=1;
			if(Ask(min(f[i], u), max(f[i], u), p))
				rb=mb;
			else
				lb=mb+1;
		}
		for(int j=0; j<d[dl[lb]]; ++j)
			f.push_back(e[dl[lb]][j]);
		ae(u, dl[lb]);
		a[dl[lb]]=3;
	}
	for(int i=0; i<n; ++i)
		if(a[i]==3||i==u)
			a[i]=1;
}

void Detect(int T, int N) {
	n=N;
	a[0]=1;
	for(int i=1; i<n; ++i)
		if(!a[i])
			b(i);
}
