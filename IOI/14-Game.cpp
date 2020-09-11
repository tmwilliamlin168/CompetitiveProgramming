#include "game.h"
#include <bits/stdc++.h>
using namespace std;

const int mxN=1.5e3;
int n, d[mxN];
bool adj[mxN][mxN], c[mxN]={1};

void initialize(int n) {
	::n=n;
	for(int i=0; i<n; ++i)
		for(int j=0; j<n; ++j)
			adj[i][j]=1;
	for(int i=1; i<n; ++i)
		d[i]=1;
}

int hasEdge(int u, int v) {
	adj[u][v]=adj[v][u]=0;
	if(c[v])
		swap(u, v);
	if(c[u])
		--d[v];
	if(!d[v]) {
		c[v]=1;
		for(int i=0; i<n; ++i)
			if(adj[i][v])
				++d[i];
	}
	return c[v];
}
