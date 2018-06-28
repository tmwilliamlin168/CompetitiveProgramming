/*
	- Many problems with queries about all nodes within distance d of a node use centroid decomposition
	- Binary search by answer (logn)
	- For each ancestor of the queried node in the centroid tree (logn ancestors)
		- 2D range query to find number of nodes within distance d with value <= x (log^2n)
	- By using parallel binary search, the 2D range query can be reduced to 1D, making the solution O(nlog^3n)
*/

#include <bits/stdc++.h>
using namespace std;

const int mxN=5e4;
int n, q, a[mxN], qu[mxN], qd[mxN], qk[mxN], fo[mxN], dt[17][2*mxN-1], dti, ctp[mxN], sz[mxN], ql[mxN], qr[mxN], p[mxN], d2[mxN];
vector<int> adj[mxN], fts[2*mxN], tc[mxN];

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

void dfs2(int u, int p) {
	sz[u]=1;
	d2[u]=0;
	for(int v : adj[u]) {
		if(v==p||ctp[v]!=-1)
			continue;
		dfs2(v, u);
		sz[u]+=sz[v];
		d2[u]=max(d2[v]+1, d2[u]);
	}
}
 
int dfs3(int u, int p, int n) {
	for(int v : adj[u])
		if(v!=p&&ctp[v]==-1&&sz[v]>n/2)
			return dfs3(v, u, n);
	return u;
}

void cd(int u, int p) {
	int c=dfs3(u, -1, sz[u]);
	fts[c+n].resize(d2[u]+3);
	dfs2(c, -1);
	fts[c].resize(d2[c]+2);
	ctp[c]=p;
	for(int v : adj[c])
		if(ctp[v]==-1)
			cd(v, c);
}

inline void upd(int i, int j) {
	for(++j; j<fts[i].size(); j+=j&-j)
		++fts[i][j];
}

inline int qry(int i, int j) {
	int r=0;
	for(j=min((int)fts[i].size()-1, j); j>0; j-=j&-j)
		r+=fts[i][j];
	return r;
}

int main() {
	cin >> n;
	for(int i=0; i<n; ++i)
		cin >> a[i];
	for(int i=0; i<n-1; ++i) {
		int u, v;
		cin >> u >> v, --u, --v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	cin >> q;
	for(int i=0; i<q; ++i)
		cin >> qu[i] >> qd[i] >> qk[i], --qu[i];
	dfs1(0, -1, 0);
	for(int i=1; i<=lg2(2*n-1); ++i)
		for(int j=0; j<2*n-(1<<i); ++j)
			dt[i][j]=min(dt[i-1][j], dt[i-1][j+(1<<(i-1))]);
	memset(ctp, -1, 4*n);
	dfs2(0, -1);
	cd(0, -2);
	for(int i=0; i<n; ++i)
		p[i]=i;
	sort(p, p+n, [&](const int &i, const int &j) {
		return a[i]<a[j];
	});
	for(int i=0; i<q; ++i)
		qr[i]=n-1;
	int ch;
	while(1) {
		ch=0;
		for(int i=0; i<2*n; ++i)
			fill(fts[i].begin()+1, fts[i].end(), 0);
		for(int i=0; i<q; ++i) {
			if(ql[i]<=qr[i]) {
				tc[(ql[i]+qr[i])/2].push_back(i);
				++ch;
			}
		}
		if(!ch)
			break;
		for(int i=0; i<n&&ch; ++i) {
			for(int u=p[i]; u!=-2; u=ctp[u]) {
				upd(u, ds(u, p[i]));
				if(ctp[u]!=-2)
					upd(u+n, ds(ctp[u], p[i]));
			}
			for(int j : tc[i]) {
				int cn=qry(qu[j], qd[j]+1);
				for(int u=qu[j]; ctp[u]!=-2; u=ctp[u])
					cn+=qry(ctp[u], qd[j]-ds(qu[j], ctp[u])+1)-qry(u+n, qd[j]-ds(qu[j], ctp[u])+1);
				if(cn>=qk[j])
					qr[j]=i-1;
				else
					ql[j]=i+1;
				--ch;
			}
			tc[i].clear();
		}
	}
	for(int i=0; i<q; ++i)
		cout << (ql[i]>=n?-1:a[p[ql[i]]]) << "\n";
}
