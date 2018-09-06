/*
	- Precompute for each cell
		- Minimum distance to a wall (with BFS)
		- Number of cells until a wall on each of the 4 sides
	- In addition to the normal 4 edges, add 4 extra edges to each cell x
		- Connects to the 4 farmost cells not blocked by a wall from x with distance equal to the x's minimum distance to a wall
*/

#include <bits/stdc++.h>
using namespace std;

const int mxN=1e3;
int n, m, nb[4][2]={{-1, 0}, {0, -1}, {1, 0}, {0, 1}}, b[mxN][mxN][4], d1[mxN][mxN], d2[mxN][mxN];
string g[mxN];
vector<array<int, 2>> tp[mxN*mxN];

__attribute__((always_inline)) bool a(int i, int j) {
	return i>=0&&i<n&&j>=0&&j<m&&g[i][j]!='#';
}

void bfs(int d[mxN][mxN], bool c) {
	for(int it=0; it<n*m; ++it) {
		for(array<int, 2> u : tp[it]) {
			int i=u[0], j=u[1];
			if(c&&g[i][j]=='C') {
				cout << d[i][j];
				exit(0);
			}
			if(d[i][j]<it)
				continue;
			for(int k=0; k<4; ++k) {
				if(!a(i+nb[k][0], j+nb[k][1]))
					continue;
				int ni=i+nb[k][0], nj=j+nb[k][1];
				if(d[ni][nj]>it+1) {
					tp[it+1].push_back({ni, nj});
					d[ni][nj]=it+1;
				}
				ni=i+nb[k][0]*b[i][j][k], nj=j+nb[k][1]*b[i][j][k];
				if(c&&d[ni][nj]>it+d1[i][j]) {
					tp[it+d1[i][j]].push_back({ni, nj});
					d[ni][nj]=it+d1[i][j];
				}
			}
		}
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> m;
	for(int i=0; i<n; ++i) {
		cin >> g[i];
		for(int j=0; j<m; ++j)
			if(a(i, j))
				for(int k=0; k<2; ++k)
					b[i][j][k]=a(i+nb[k][0], j+nb[k][1])?b[i+nb[k][0]][j+nb[k][1]][k]+1:0;
	}
	for(int i=n-1; i>=0; --i) {
		memset(d1[i], 0x3F, 4*m);
		for(int j=m-1; j>=0; --j) {
			if(!a(i, j))
				continue;
			for(int k=2; k<4; ++k)
				b[i][j][k]=a(i+nb[k][0], j+nb[k][1])?b[i+nb[k][0]][j+nb[k][1]][k]+1:0;
			for(int k=0; k<4; ++k) {
				if(!a(i+nb[k][0], j+nb[k][1])) {
					d1[i][j]=1;
					tp[1].push_back({i, j});
					break;
				}
			}
		}
	}
	bfs(d1, 0);
	for(int i=0; i<n; ++i) {
		memset(d2[i], 0x3F, 4*m);
		for(int j=0; j<m; ++j) {
			tp[i*m+j].clear();
			if(g[i][j]=='S') {
				d2[i][j]=0;
				tp[0].push_back({i, j});
			}
		}
	}
	bfs(d2, 1);
}
