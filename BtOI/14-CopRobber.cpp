/*
	- Call a state winning if the cop will win
	- A state when it is the cop's turn is winning if any states that it directs to are winning
	- A state when it is the robber's turn is winning if all states that it directs to are winning
	- Use a variation of topological sort to mark states as winning from the "leaf" states
	- If one of the starting positions for the cop works, then all starting positions work, so we only need to check node 0
*/

#include "coprobber.h"
#include <bits/stdc++.h>
using namespace std;

const int mxN=500;
int as[mxN][mxN], qh, qt, p, f[mxN][mxN];
bool w[mxN][mxN][2];
array<int, 3> qu[mxN*mxN*2];

int start(int n, bool a[mxN][mxN]) {
	for(int i=0; i<n; ++i)
		for(int j=0; j<n; ++j)
			for(int k=0; k<n; ++k)
				as[k][i]+=a[i][j];
	qh=qt=0;
	for(int i=0; i<n; ++i) {
		for(int j=0; j<2; ++j) {
			w[i][i][j]=1;
			qu[qt++]={i, i, j};
		}
	}
	while(qh<qt) {
		array<int, 3> u=qu[qh++];
		for(int i=0; i<n; ++i) {
			if(u[2]&&(a[u[0]][i]||i==u[0])&&!w[i][u[1]][0]) {
				w[i][u[1]][0]=1;
				qu[qt++]={i, u[1], 0};
				f[i][u[1]]=u[0];
			} else if(!u[2]&&a[u[1]][i]&&!w[u[0]][i][1]&&--as[u[0]][i]<=0) {
				w[u[0]][i][1]=1;
				qu[qt++]={u[0], i, 1};
			}
		}
	}
	p=0;
	bool ok=1;
	for(int i=0; i<n&&ok; ++i)
		ok=w[0][i][0];
	return ok?0:-1;
}

int nextMove(int r) {
	return p=f[p][r];
}
