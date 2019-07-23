/*
	- Precalculate which BCC each edge belongs to
	- Try to grow the tree node by node
	- To find the royal edges for a node u
		- Ignore edges (u, v) such that v is already in our tree
		- For the edges (u, v) such that v is adjacent to some other node in our tree
			- We can use divide and conquer to find which edges are royal
		- For the other edges
			- We can afford to use one query per edge
			- The "base" tree will have at most 1 edge adjacent to u in each BCC
				- Find maximal forest without u
				- Try to add royal adjacent edges first before adding ones we aren't sure of
			- For each group of adjacent edges in the same BCC
				- Query the tree with each edges
				- The trees in this group along with the "base" tree with the maximum will be the ones with royal edges adjacent to u
*/

#include "simurgh.h"
#include <bits/stdc++.h>
using namespace std;

const int mxN=500, mxM=mxN*(mxN-1)/2;
int n, tin[mxN], low[mxN], dt=1, b[mxM], bs, st[mxM], sth, t[mxN], p[mxN];
vector<int> eu, ev, adj[mxN], ans;
bool c[mxN];

void dfs1(int u=0, int p=-1) {
	tin[u]=low[u]=dt++;
	for(int e : adj[u]) {
		int v=eu[e]^ev[e]^u;
		if(!tin[v]) {
			st[sth++]=e;
			dfs1(v, u);
			low[u]=min(low[v], low[u]);
			if(low[v]>=tin[u]) {
				do {
					b[st[--sth]]=bs;
				} while(st[sth]^e);
				++bs;
			}
		} else if(v^p&&tin[v]<tin[u]) {
			st[sth++]=e;
			low[u]=min(tin[v], low[u]);
		}
	}
}

int find(int x) {
	return x^p[x]?p[x]=find(p[x]):x;
}

bool join(int x, int y) {
	if((x=find(x))==(y=find(y)))
		return 0;
	p[x]=y;
	return 1;
}

void fst(vector<int> w, vector<int> &r) {
	for(int i=0; i<eu.size(); ++i)
		if(w[i]&&join(eu[i], ev[i]))
			r.push_back(i);
}

void dc(vector<int> &a, vector<int> &b, vector<int> &c, int l, int r, int s1, int s2) {
	if(s2==s1)
		return;
	if(l==r) {
		c.push_back(b[l]);
		return;
	}
	int m=(l+r)/2;
	vector<int> d=a;
	for(int i=l; i<=m; ++i)
		d[i]=b[i];
	int sl=count_common_roads(d);
	dc(a, b, c, l, m, s1, sl);
	dc(a, b, c, m+1, r, s1, s2-sl+s1);
}

void dfs2(int u=0, int pe=-1) {
	vector<int> v1, v2, r;
	for(int e : adj[u]) {
		int v=eu[e]^ev[e]^u;
		if(c[v])
			continue;
		if(t[v]<0) {
			v2.push_back(e);
			t[v]=e;
		} else
			v1.push_back(e);
	}
	if(v1.size()) {
		iota(p, p+n, 0);
		vector<int> s1, w(eu.size(), 1), s2=v1;
		for(int i=0; i<v1.size(); ++i) {
			s1.push_back(t[eu[v1[i]]^ev[v1[i]]^u]);
			join(eu[s1.back()], ev[s1.back()]);
		}
		for(int e : ans) {
			s1.push_back(e);
			join(eu[e], ev[e]);
		}
		for(int e : v1) {
			w[e]=0;
			w[t[eu[e]^ev[e]^u]]=0;
		}
		fst(w, s1);
		s2.insert(s2.end(), s1.begin()+v1.size(), s1.end());
		dc(s1, v1, r, 0, v1.size()-1, count_common_roads(s1), count_common_roads(s2));
	}
	if(v2.size()) {
		vector<int> w(eu.size(), 1), s;
		for(int e : adj[u])
			w[e]=0;
		iota(p, p+n, 0);
		fst(w, s);
		for(int e : r)
			if(join(eu[e], ev[e]))
				s.push_back(e);
		if(~pe&&join(eu[pe], ev[pe]))
			s.push_back(pe);
		for(int e : adj[u])
			if(join(eu[e], ev[e]))
				s.push_back(e);
		int bc=count_common_roads(s);
		sort(v2.begin(), v2.end(), [](const int &i, const int &j) {
			return b[i]<b[j];
		});
		for(int i=0, j=0, o; i<v2.size(); ) {
			for(; j<v2.size()&&b[v2[j]]==b[v2[i]]; ++j);
			for(int e : s)
				if(b[e]==b[v2[i]]&&(eu[e]==u||ev[e]==u))
					o=e;
			s.erase(find(s.begin(), s.end(), o));
			vector<int> a;
			int cm=bc;
			for(; i<j; ++i) {
				s.push_back(v2[i]);
				int cc=count_common_roads(s);
				if(cc>cm) {
					cm=cc;
					a=vector<int>();
				}
				if(cc==cm)
					a.push_back(v2[i]);
				s.pop_back();
			}
			s.push_back(o);
			r.insert(r.end(), a.begin(), a.end());
		}
	}
	for(int e : r) {
		ans.push_back(e);
		c[eu[e]^ev[e]^u]=1;
	}
	for(int e : r)
		dfs2(eu[e]^ev[e]^u, e);
}

vector<int> find_roads(int n, vector<int> u, vector<int> v) {
	::n=n;
	eu=u;
	ev=v;
	for(int i=0; i<u.size(); ++i) {
		adj[u[i]].push_back(i);
		adj[v[i]].push_back(i);
	}
	dfs1();
	c[0]=1;
	memset(t, -1, 4*n);
	dfs2();
	return ans;
}
