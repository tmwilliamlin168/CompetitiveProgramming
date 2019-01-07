/*
	- https://www.hackerrank.com/contests/w38/challenges/neighborhood-queries/editorial
*/

#include <bits/stdc++.h>
using namespace std;

const int mxN=5e4;
int n, q, a[mxN], fo[mxN], dt[17][2*mxN-1], dti, ctp[mxN], sz[mxN], p[mxN], ip[mxN], sts=1;
vector<int> adj[mxN], sti[2*mxN], nbd[mxN];

struct node {
	int lc, rc, x;
} st[2*mxN*16*16+1];

void upd(int &sti, int l1, int x, int l2=0, int r2=n-1) {
	st[sts]=st[sti];
	sti=sts++;
	st[sti].x+=x;
	if(l2==r2)
		return;
	int m2=(l2+r2)/2;
	if(l1<=m2)
		upd(st[sti].lc, l1, x, l2, m2);
	else
		upd(st[sti].rc, l1, x, m2+1, r2);
}

inline int lg2(int x) {
	return 31-__builtin_clz(x);
}

void dfs1(int u, int p, int d) {
	fo[u]=dti;
	dt[0][dti++]=d;
	for(int v : adj[u]) {
		if(v==p)
			continue;
		dfs1(v, u, d+1);
		dt[0][dti++]=d;
	}
}

inline int ds(int u, int v) {
	if(u==v)
		return 0;
	if((u=fo[u])>(v=fo[v]))
		swap(u, v);
	int k=lg2(v-u);
	return dt[0][u]+dt[0][v]-2*min(dt[k][u], dt[k][v-(1<<k)+1]);
}

void dfs2(int u, int p, int d) {
	sz[u]=1;
	nbd[d].push_back(u);
	for(int v : adj[u]) {
		if(v==p||ctp[v]!=-1)
			continue;
		dfs2(v, u, d+1);
		sz[u]+=sz[v];
	}
}
 
int dfs3(int u, int p, int n) {
	for(int v : adj[u])
		if(v!=p&&ctp[v]==-1&&sz[v]>n/2)
			return dfs3(v, u, n);
	return u;
}

void cd(int u, int p) {
	dfs2(u, p, 1);
	int c=dfs3(u, -1, sz[u]);
	ctp[c]=p;
	sti[c+n].push_back(0);
	for(int i=1; !nbd[i].empty(); ++i) {
		sti[c+n].push_back(sti[c+n].back());
		for(int j : nbd[i])
			upd(sti[c+n][i], ip[j], -1);
		nbd[i].clear();
	}
	dfs2(c, -1, 0);
	for(int i=0; !nbd[i].empty(); ++i) {
		sti[c].push_back(i?sti[c].back():0);
		for(int j : nbd[i])
			upd(sti[c][i], ip[j], 1);
		nbd[i].clear();
	}
	for(int v : adj[c])
		if(ctp[v]==-1)
			cd(v, c);
}

inline int gsti(int u, int d) {
	return d<0?0:sti[u][min(d, (int)sti[u].size()-1)];
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n;
	for(int i=0; i<n; ++i)
		cin >> a[i];
	for(int i=0; i<n-1; ++i) {
		int u, v;
		cin >> u >> v, --u, --v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	dfs1(0, -1, 0);
	for(int i=1; i<=lg2(2*n-1); ++i)
		for(int j=0; j<2*n-(1<<i); ++j)
			dt[i][j]=min(dt[i-1][j], dt[i-1][j+(1<<(i-1))]);
	for(int i=0; i<n; ++i)
		p[i]=i;
	sort(p, p+n, [&](const int &i, const int &j) {
		return a[i]<a[j];
	});
	for(int i=0; i<n; ++i)
		ip[p[i]]=i;
	memset(ctp, -1, 4*n);
	cd(0, -2);
	cin >> q;
	while(q--) {
		int u, d, k, t=0;
		cin >> u >> d >> k, --u;
		vector<int> qst;
		qst.push_back(gsti(u, d));
		t+=st[gsti(u, d)].x;
		for(int i=u; ctp[i]!=-2; i=ctp[i]) {
			int j=gsti(ctp[i], d-ds(ctp[i], u));
			qst.push_back(j);
			t+=st[j].x;
			j=gsti(i+n, d-ds(ctp[i], u));
			qst.push_back(j);
			t+=st[j].x;
		}
		if(t<k) {
			cout << "-1\n";
			continue;
		}
		int lb=0, rb=n-1;
		while(lb<rb) {
			int mb=(lb+rb)/2, cn=0;
			for(int qsti : qst)
				cn+=st[st[qsti].lc].x;
			if(k<=cn) {
				for(int &qsti : qst)
					qsti=st[qsti].lc;
				rb=mb;
			} else {
				k-=cn;
				for(int &qsti : qst)
					qsti=st[qsti].rc;
				lb=mb+1;
			}
		}
		cout << a[p[lb]] << "\n";
	}
}
