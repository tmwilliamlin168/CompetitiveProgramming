#include <bits/stdc++.h>
using namespace std;

const int mxN=1e3;
int n, xm[mxN], ym[mxN], xs, ys, x[mxN], y[mxN], a, b, ans, m[mxN], d[mxN][mxN], e[mxN][mxN], t1, t2;
bool c[mxN][mxN], vis1[mxN], vis2[mxN], used[mxN];
vector<int> adj[mxN], a1[mxN], a2[mxN];
array<int, 3> s1[mxN], s2[mxN];

bool dfs1(int u) {
	vis1[u]=1;
	for(int v : adj[u]) {
		int u2=m[v];
		if(u2==-1||!vis1[u2]&&dfs1(u2)) {
			m[v]=u;
			return 1;
		}
	}
	return 0;
}

void dfs2(int u) {
	vis1[u]=1;
	for(int v : adj[u]) {
		if(!vis2[v]) {
			vis2[v]=1;
			dfs2(m[v]);
		}
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n;
	for(int i=0; i<n; ++i)
		cin >> x[i] >> y[i];
	memcpy(xm, x, 4*n);
	sort(xm, xm+n);
	for(int i=0; i<n; ++i) {
		xm[xs]=xm[i];
		xs+=i>=n-1||xm[i+1]!=xm[i];
	}
	memcpy(ym, y, 4*n);
	sort(ym, ym+n);
	for(int i=0; i<n; ++i) {
		ym[ys]=ym[i];
		ys+=i>=n-1||ym[i+1]!=ym[i];
	}
	ans=xs+ys;
	for(int i=0; i<n; ++i) {
		x[i]=lower_bound(xm, xm+xs, x[i])-xm;
		y[i]=lower_bound(ym, ym+ys, y[i])-ym;
		c[x[i]][y[i]]=1;
	}
	memset(d, -1, sizeof(d));
	memset(e, -1, sizeof(e));
	for(int i=0; i<xs; ++i) {
		int l=-1;
		for(int j=0; j<ys; ++j) {
			if(!c[i][j])
				continue;
			if(l!=-1) {
				for(int k=l+1; k<j; ++k)
					d[i][k]=a;
				s1[a]={i, l, j};
				++a;
			} else
				a1[i].push_back(j);
			l=j;
		}
		a1[i].push_back(l);
	}
	for(int j=0; j<ys; ++j) {
		int l=-1;
		for(int i=0; i<xs; ++i) {
			if(!c[i][j])
				continue;
			if(l!=-1) {
				for(int k=l+1; k<i; ++k)
					e[k][j]=b;
				s2[b]={j, l, i};
				++b;
			} else
				a2[j].push_back(i);
			l=i;
		}
		a2[j].push_back(l);
	}
	for(int i=0; i<xs; ++i)
		for(int j=0; j<ys; ++j)
			if(d[i][j]!=-1&&e[i][j]!=-1&&!c[i][j])
				adj[d[i][j]].push_back(e[i][j]);
	memset(m, -1, 4*b);
	for(int i=0; i<a; ++i) {
		memset(vis1, 0, a);
		used[i]=dfs1(i);
	}
	memset(vis1, 0, a);
	for(int i=0; i<a; ++i)
		if(!used[i])
			dfs2(i);
	for(int i=0; i<b; ++i) {
		if(vis2[i]) {
			a2[s2[i][0]].push_back(s2[i][1]);
			a2[s2[i][0]].push_back(s2[i][2]);
			++t2;
		}
	}
	for(int i=0; i<a; ++i) {
		if(!vis1[i]) {
			a1[s1[i][0]].push_back(s1[i][1]);
			a1[s1[i][0]].push_back(s1[i][2]);
			++t1;
		}
	}
	cout << ys+t2 << "\n";
	for(int i=0; i<ys; ++i) {
		sort(a2[i].begin(), a2[i].end());
		for(int j=0; j<a2[i].size(); j+=2)
			cout << xm[a2[i][j]] << " " << ym[i] << " " << xm[a2[i][j+1]] << " " << ym[i] << "\n";
	}
	cout << xs+t1 << "\n";
	for(int i=0; i<xs; ++i) {
		sort(a1[i].begin(), a1[i].end());
		for(int j=0; j<a1[i].size(); j+=2)
			cout << xm[i] << " " << ym[a1[i][j]] << " " << xm[i] << " " << ym[a1[i][j+1]] << "\n";
	}
}
