#include "split.h"
#include <bits/stdc++.h>
using namespace std;

#define ar array

const int mxN=1e5;
ar<int, 2> ps[3];
vector<int> ans, adj1[mxN], adj2[2*mxN], st, adj3[mxN];
int n, tin[mxN], low[mxN], dt=1, bccI, s[2*mxN], nxt[mxN][2], it[mxN];
bool cb[mxN], bl[mxN], si[mxN];

void dfs1(int u=0, int p=-1) {
	tin[u]=low[u]=dt++;
	st.push_back(u);
	for(int v : adj1[u]) {
		if(!tin[v]) {
			int sts=st.size();
			dfs1(v, u);
			low[u]=min(low[v], low[u]);
			if(low[v]>=tin[u]) {
				while(st.size()>sts) {
					adj2[n+bccI].push_back(st.back());
					st.pop_back();
				}
				adj2[n+bccI].push_back(u);
				adj2[u].push_back(n+bccI++);
			}
		} else if(v^p)
			low[u]=min(tin[v], low[u]);
	}
}

void dfs2(int u=0, int p=-1) {
	s[u]=u<n;
	for(int v : adj2[u]) {
		if(v==p)
			continue;
		dfs2(v, u);
		s[u]+=s[v];
	}
}

void dfs4(int u, int p=-1) {
	it[dt]=u;
	tin[u]=low[u]=dt++;
	for(int v : adj3[u]) {
		if(!tin[v]) {
			dfs4(v, u);
			low[u]=min(low[v], low[u]);
		} else if(v^p)
			low[u]=min(tin[v], low[u]);
	}
}

void dfs5(int u, int p=-1) {
	tin[u]=0;
	bool d=si[it[low[u]]];
	if(~p) {
		nxt[u][!d]=p;
		nxt[u][d]=nxt[p][d];
		nxt[p][d]=u;
		if(~nxt[u][d])
			nxt[nxt[u][d]][!d]=u;
		si[p]=!d;
	}
	for(int v : adj3[u])
		if(tin[v])
			dfs5(v, u);
}

void dfs6(int u, int c, int &l) {
	if(!l)
		return;
	ans[u]=c;
	--l;
	for(int v : adj1[u])
		if(!bl[v]&&ans[v]==ps[2][1])
			dfs6(v, c, l);
}

void as(vector<int> a, vector<int> b) {
	if(ans[0])
		return;
	fill(ans.begin(), ans.end(), ps[2][1]);
	int la=ps[0][0], lb=ps[1][0];
	for(int c : b)
		bl[c]=1;
	dfs6(a[0], ps[0][1], la);
	for(int c : b)
		bl[c]=0;
	dfs6(b[0], ps[1][1], lb);
}

void dfs3(int u=0, int p=-1) {
	if(u>=n) {
		ar<int, 2> mx{};
		for(int v : adj2[u]) {
			cb[v]=1;
			mx=max(ar<int, 2>{s[v], v}, mx);
		}
		if(mx[0]>=ps[1][0]) {
			if(n-mx[0]>=ps[0][0]) {
				vector<int> a=adj2[u];
				a.erase(find(a.begin(), a.end(), mx[1]));
				as(a, {mx[1]});
			}
		} else if(mx[0]>=ps[0][0]) {
			if(n-mx[0]>=ps[1][0]) {
				vector<int> b=adj2[u];
				b.erase(find(b.begin(), b.end(), mx[1]));
				as({mx[1]}, b);
			}
		} else {
			for(int v : adj2[u])
				for(int w : adj1[v])
					if(cb[w])
						adj3[v].push_back(w);
			int cs=0, cu=adj2[u][0];
			dt=1;
			dfs4(cu);
			nxt[cu][0]=nxt[cu][1]=-1;
			si[cu]=1;
			dfs5(cu);
			vector<int> a, b;
			while(cs<ps[0][0]) {
				cs+=s[cu];
				a.push_back(cu);
				cu=nxt[cu][1];
			}
			while(~cu) {
				b.push_back(cu);
				cu=nxt[cu][1];
			}
			as(a, b);
		}
		for(int v : adj2[u]) {
			cb[v]=0;
			adj3[v].clear();
			si[v]=0;
		}
	}
	for(int v : adj2[u]) {
		if(v==p)
			continue;
		s[u]=n-s[v];
		dfs3(v, u);
	}
}

vector<int> find_split(int n, int a, int b, int c, vector<int> p, vector<int> q) {
	::n=n;
	ps[0]={a, 1};
	ps[1]={b, 2};
	ps[2]={c, 3};
	sort(ps, ps+3);
	for(int i=0; i<p.size(); ++i) {
		adj1[p[i]].push_back(q[i]);
		adj1[q[i]].push_back(p[i]);
	}
	ans=vector<int>(n);
	dfs1();
	dfs2();
	memset(tin, 0, 4*n);
	dfs3();
	return ans;
}
