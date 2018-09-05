#include "werewolf.h"
#include <bits/stdc++.h>
using namespace std;

const int mxN=2e5;
int n, q, p[mxN], st[2][mxN], en[2][mxN], dt, anc[2][mxN], r[mxN], ta[mxN], ft[mxN+1];
vector<int> adj1[mxN], adj2[mxN];
vector<array<int, 2>> b[mxN+1];
bool d[mxN];

int find(int x) {
	return x==r[x]?x:(r[x]=find(r[x]));
}

void dfs(int u, int st[mxN], int en[mxN]) {
	st[u]=dt++;
	for(int v : adj2[u])
		dfs(v, st, en);
	en[u]=dt;
}

void a(int st[mxN], int en[mxN], int anc[mxN]) {
	for(int i=0; i<n; ++i)
		r[i]=i;
	for(int i=0; i<n; ++i) {
		for(int j : adj1[p[i]]) {
			if(!d[j]||(j=find(j))==p[i])
				continue;
			r[j]=p[i];
			adj2[p[i]].push_back(j);
		}
		for(array<int, 2> c : b[p[i]])
			anc[c[1]]=find(c[0]);
		b[p[i]].clear();
		d[p[i]]=1;
	}
	dfs(p[n-1], st, en);
}

int qry(int i) {
	int r=0;
	for(; i; i-=i&-i)
		r+=ft[i];
	return r;
}

vector<int> check_validity(int n2, vector<int> x, vector<int> y, vector<int> s, vector<int> e, vector<int> l, vector<int> r) {
	n=n2;
	for(int i=0; i<x.size(); ++i) {
		adj1[x[i]].push_back(y[i]);
		adj1[y[i]].push_back(x[i]);
	}
	q=s.size();
	for(int i=0; i<n; ++i)
		p[i]=n-1-i;
	for(int i=0; i<q; ++i)
		b[l[i]].push_back({s[i], i});
	a(st[0], en[0], anc[0]);
	for(int i=0; i<n; ++i) {
		adj2[i].clear();
		p[i]=i;
	}
	memset(d, 0, n);
	dt=0;
	for(int i=0; i<q; ++i)
		b[r[i]].push_back({e[i], i});
	a(st[1], en[1], anc[1]);
	for(int i=0; i<n; ++i)
		ta[st[0][i]]=st[1][i];
	for(int i=0; i<q; ++i) {
		b[st[0][anc[0][i]]].push_back({i, -1});
		b[en[0][anc[0][i]]].push_back({i, 1});
	}
	vector<int> ans=vector<int>(q);
	for(int i=0; i<n; ++i) {
		for(int j=ta[i]+1; j<=n; j+=j&-j)
			++ft[j];
		for(array<int, 2> c : b[i+1])
			ans[c[0]]+=c[1]*(qry(en[1][anc[1][c[0]]])-qry(st[1][anc[1][c[0]]]));
	}
	for(int i=0; i<q; ++i)
		ans[i]=ans[i]>0;
	return ans;
}
