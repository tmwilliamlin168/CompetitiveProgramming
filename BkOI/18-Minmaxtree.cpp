/*
	- http://boi2018.ro/assets/Tasks/BOI/Day_1/minmaxtree/minmaxtree-solution.pdf
*/

#include <bits/stdc++.h>
using namespace std;

const int mxN=7e4;
int n, ui, vi, d[mxN], anc[mxN][17], c1[mxN][17], c2[mxN][17], k, wi, i2w[mxN], mt[mxN-1];
vector<int> adj[mxN], cm[mxN];
char qt;
unordered_map<int, int> w2i;
bool vis[mxN];

void dfs1(int u=n-1, int p=-1) {
	anc[u][0]=p;
	for(int i=1; i<17; ++i)
		anc[u][i]=anc[u][i-1]==-1?-1:anc[anc[u][i-1]][i-1];
	d[u]=p==-1?0:d[p]+1;
	for(int v : adj[u])
		if(v!=p)
			dfs1(v, u);
}

bool dfs2(int u) {
	vis[u]=1;
	for(int v : cm[u]) {
		if(mt[v]==-1||!vis[mt[v]]&&dfs2(mt[v])) {
			mt[v]=u;
			return 1;
		}
	}
	return 0;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> n;
	for(int i=0; i<n-1; ++i) {
		cin >> ui >> vi, --ui, --vi;
		adj[ui].push_back(vi);
		adj[vi].push_back(ui);
	}
	dfs1();
	memset(c2, 0x96, sizeof(c2));
	cin >> k;
	for(int i=0; i<k; ++i) {
		cin >> qt >> ui >> vi >> wi, --ui, --vi;
		i2w[i]=wi;
		w2i[wi]=i;
		int (*c)[17];
		if(qt=='M') {
			wi=-wi;
			c=c2;
		} else
			c=c1;
		if(d[ui]<d[vi])
			swap(ui, vi);
		auto ue=[&](int &u, int j) {
			c[u][j]=max(wi, c[u][j]);
			u=anc[u][j];
		};
		for(int j=16; j>=0; --j)
			if(d[ui]-(1<<j)>=d[vi])
				ue(ui, j);
		if(ui!=vi) {
			for(int j=16; j>=0; --j) {
				if(anc[ui][j]!=anc[vi][j]) {
					ue(ui, j);
					ue(vi, j);
				}
			}
			ue(ui, 0);
			ue(vi, 0);
		}
	}
	for(int i=16; i; --i) {
		for(int j=0; j<n; ++j) {
			c1[j][i-1]=max(c1[j][i], c1[j][i-1]);
			c2[j][i-1]=max(c2[j][i], c2[j][i-1]);
			if(anc[j][i-1]!=-1) {
				c1[anc[j][i-1]][i-1]=max(c1[j][i], c1[anc[j][i-1]][i-1]);
				c2[anc[j][i-1]][i-1]=max(c2[j][i], c2[anc[j][i-1]][i-1]);
			}
		}
	}
	for(int i=0; i<n-1; ++i) {
		c2[i][0]=-c2[i][0];
		if(w2i.find(c1[i][0])!=w2i.end())
			cm[w2i[c1[i][0]]].push_back(i);
		if(w2i.find(c2[i][0])!=w2i.end())
			cm[w2i[c2[i][0]]].push_back(i);
	}
	memset(mt, -1, 4*(n-1));
	for(int i=0; i<k; ++i) {
		dfs2(i);
		memset(vis, 0, k);
	}
	for(int i=0; i<n-1; ++i)
		cout << i+1 << " " << anc[i][0]+1 << " " << (mt[i]>=0&&i2w[mt[i]]==c1[i][0]?c1[i][0]:c2[i][0]) << "\n";
}
