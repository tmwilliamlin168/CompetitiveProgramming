#include <bits/stdc++.h>
using namespace std;

const int mxN=1e5;
int n, m, ui, vi, anc[mxN][17], dt, ds[mxN], de[mxN], gu[mxN], gd[mxN+1], ai, bi;
vector<int> adj1[mxN], adj2[mxN];
bool vis[mxN], act[mxN], fk, a1[mxN];

void dfs1(int u=0, int p=-1) {
	ds[u]=dt++;
	anc[u][0]=p==-1?-1:p;
	for(int i=1; i<17; ++i)
		anc[u][i]=anc[u][i-1]==-1?-1:anc[anc[u][i-1]][i-1];
	for(int v : adj1[u])
		if(v!=p)
			dfs1(v, u);
	de[u]=dt;
}

void dfs2(int u=0) {
	for(int v : adj1[u]) {
		if(v==anc[u][0])
			continue;
		dfs2(v);
		gu[ds[u]]+=gu[ds[v]];
	}
	gd[ds[u]]-=gu[ds[u]];
}

void dfs3(int u) {
	vis[u]=1;
	act[u]=1;
	for(int v : adj2[u]) {
		a1[v]=1;
		fk|=act[v];
		if(!vis[v])
			dfs3(v);
	}
	act[u]=0;
}

int main() {
	ifstream cin("gathering.in");
	ofstream cout("gathering.out");
	
	//input
	cin >> n >> m;
	for(int i=0; i<n-1; ++i) {
		cin >> ui >> vi, --ui, --vi;
		adj1[ui].push_back(vi);
		adj1[vi].push_back(ui);
	}
	//find basic tree stuff
	dfs1();
	while(m--) {
		cin >> ai >> bi, --ai, --bi;
		adj2[bi].push_back(ai);
		if(ds[ai]<ds[bi]&&ds[bi]<de[ai]) {
			//b is descendant
			//add downward edges to all nodes but subtree with b
			++gd[1];
			--gd[n];
			//child of a that is b's ancestor
			int c=bi;
			for(int i=16; i>=0; --i)
				if(anc[c][i]!=-1&&ds[ai]<ds[anc[c][i]])
					c=anc[c][i];
			--gd[ds[c]];
			++gd[de[c]];
			//upward edges from a to root
			++gu[ds[ai]];
		} else {
			//add downward edges to a's subtree
			++gd[ds[ai]+1];
			--gd[de[ai]];
		}
	}
	//Postprocess down edges
	for(int i=1; i<n; ++i)
		gd[i]+=gd[i-1];
	//Postprocess up edges
	dfs2();
	//Add the down/up edges
	for(int i=1; i<n; ++i) {
		if(gd[ds[i]])
			adj2[anc[i][0]].push_back(i);
		if(gu[ds[i]])
			adj2[i].push_back(anc[i][0]);
	}
	//Check DAG and find nodes with in-degree 0
	for(int i=0; i<n; ++i)
		if(!vis[i])
			dfs3(i);
	//output
	for(int i=0; i<n; ++i)
		cout << (!a1[i]&&!fk) << "\n";
}
