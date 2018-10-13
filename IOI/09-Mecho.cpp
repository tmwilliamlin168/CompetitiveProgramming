/*
	- Binary search by answer
	- BFS on all cells that Mecho can beat the bees to
*/

#include <bits/stdc++.h>
using namespace std;

const int mxN=800;
int n, s, d1[mxN][mxN], d2[mxN][mxN], si, sj, ti, tj, lb=0, rb=mxN*mxN, nb[4][2]={{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
string g[mxN];
array<int, 2> qu[mxN*mxN];

void bfs(int d[mxN][mxN], int a) {
	int qt=0;
	for(int i=0; i<n; ++i)
		for(int j=0; j<n; ++j)
			if(!d[i][j])
				qu[qt++]={i, j};
	for(int i=0; i<qt; ++i) {
		array<int, 2> u=qu[i];
		if(a>=0&&d[u[0]][u[1]]/s+a>=d1[u[0]][u[1]])
			continue;
		for(int j=0; j<4; ++j) {
			int ni=u[0]+nb[j][0], nj=u[1]+nb[j][1];
			if(ni>=0&&ni<n&&nj>=0&&nj<n&&g[ni][nj]!='T'&&(a>=0||g[ni][nj]!='D')&&d[ni][nj]>1e7) {
				d[ni][nj]=d[u[0]][u[1]]+1;
				qu[qt++]={ni, nj};
			}
		}
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> s;
	for(int i=0; i<n; ++i)
		cin >> g[i];
	memset(d1, 1, sizeof(d1));
	for(int i=0; i<n; ++i) {
		for(int j=0; j<n; ++j) {
			if(g[i][j]=='M') {
				si=i;
				sj=j;
			} else if(g[i][j]=='D') {
				ti=i;
				tj=j;
			} else if(g[i][j]=='H')
				d1[i][j]=0;
		}
	}
	bfs(d1, -1);
	while(lb<=rb) {
		int mb=(lb+rb)/2;
		memset(d2, 1, sizeof(d2));
		d2[si][sj]=0;
		bfs(d2, mb);
		if(d2[ti][tj]<1e7)
			lb=mb+1;
		else
			rb=mb-1;
	}
	cout << rb;
}
