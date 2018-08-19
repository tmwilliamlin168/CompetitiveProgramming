#include <bits/stdc++.h>
using namespace std;

const int mxN=5e5;
int n, k, m, anc[mxN][19], b[mxN], mn[mxN][19];
vector<int> adj[mxN];
array<int, 3> fs[mxN];
long long ans;

struct dsu {
	int p[mxN], r[mxN];
	void init(int n) {
		for(int i=0; i<n; ++i)
			p[i]=i;
	}
	int find(int x) {
		return x==p[x]?x:(p[x]=find(p[x]));
	}
	bool join(int x, int y) {
		if((x=find(x))==(y=find(y)))
			return 0;
		if(r[x]<r[y])
			p[x]=y;
		else
			p[y]=x;
		r[x]+=r[x]==r[y];
		return 1;
	}
} d;

void dfs(int u, int p=-1) {
	anc[u][0]=p;
	for(int i=1; i<19; ++i)
		anc[u][i]=anc[u][i-1]==-1?-1:anc[anc[u][i-1]][i-1];
	b[u]=p==-1?0:b[p]+1;
	for(int v : adj[u])
		if(v!=p)
			dfs(v, u);
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> k >> m;
	d.init(n);
	for(int i=0; i<k; ++i) {
		int ga, gb;
		cin >> ga >> gb, --ga, --gb;
		d.join(ga, gb);
		adj[ga].push_back(gb);
		adj[gb].push_back(ga);
	}
	for(int i=0; i<m; ++i) {
		cin >> fs[i][0] >> fs[i][1] >> fs[i][2], --fs[i][0], --fs[i][1];
		if(d.join(fs[i][0], fs[i][1])) {
			adj[fs[i][0]].push_back(fs[i][1]);
			adj[fs[i][1]].push_back(fs[i][0]);
			fs[i][2]=0;
		}
	}
	dfs(0);
	memset(mn, 0x3F, n*sizeof(mn[0]));
	auto c=[&](int &i, int j, int k) {
		mn[i][j]=min(k, mn[i][j]);
		i=anc[i][j];
	};
	for(int i=0; i<m; ++i) {
		if(b[fs[i][0]]<b[fs[i][1]])
			swap(fs[i][0], fs[i][1]);
		int db=b[fs[i][0]]-b[fs[i][1]];
		for(int j=18; j>=0; --j)
			if(db>>j&1)
				c(fs[i][0], j, fs[i][2]);
		if(fs[i][0]==fs[i][1])
			continue;
		for(int j=18; j>=0; --j) {
			if(anc[fs[i][0]][j]!=anc[fs[i][1]][j]) {
				c(fs[i][0], j, fs[i][2]);
				c(fs[i][1], j, fs[i][2]);
			}
		}
		c(fs[i][0], 0, fs[i][2]);
		c(fs[i][1], 0, fs[i][2]);
	}
	for(int i=18; i; --i) {
		for(int j=0; j<n; ++j) {
			mn[j][i-1]=min(mn[j][i], mn[j][i-1]);
			if(anc[j][i-1]!=-1)
				mn[anc[j][i-1]][i-1]=min(mn[j][i], mn[anc[j][i-1]][i-1]);
		}
	}
	for(int i=1; i<n; ++i) {
		if(mn[i][0]>1e9) {
			cout << -1;
			return 0;
		}
		ans+=mn[i][0];
	}
	cout << ans;
}
