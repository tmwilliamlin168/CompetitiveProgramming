/*
	- We first calculate the ending locations given a starting location and direction of push
	- Then a dp / bfs is used for calculating for each consecutive range of robots and a location, the minimum cost to get a merged robot with that range on that location
*/

#include <bits/stdc++.h>
using namespace std;

const int mxN=9, mxS=500, mxD=mxS*mxS*mxN;
int n, w, h, di[4]={-1, 0, 1, 0}, dj[4]={0, 1, 0, -1}, d[mxN*(mxN+1)/2][mxS][mxS], ans=INT_MAX, m1[mxN][mxN];
string g[mxS];
array<int, 2> e[mxS][mxS][4], m2[mxN*(mxN+1)/2];
vector<array<int, 2>> bd[mxD];

array<int, 2> dfs(int i, int j, int k) {
	if(e[i][j][k][0]==-1) {
		e[i][j][k][0]=-2;
		int nk=k;
		if(g[i][j]=='C')
			nk=(k+1)%4;
		else if(g[i][j]=='A')
			nk=(k+3)%4;
		int ni=i+di[nk], nj=j+dj[nk];
		e[i][j][k]=ni<0||ni>=h||nj<0||nj>=w||g[ni][nj]=='x'?array<int, 2>{i, j}:dfs(ni, nj, nk);
	}
	return e[i][j][k];
}

void ud(int d[mxS][mxS], int i, int j, int k) {
	if(k<mxD&&d[i][j]>k) {
		d[i][j]=k;
		bd[k].push_back({i, j});
	}
}

void bfs(int d[mxS][mxS]) {
	for(int di=0; di<mxD; ++di) {
		for(array<int, 2> u : bd[di]) {
			if(d[u[0]][u[1]]<di)
				continue;
			for(int i=0; i<4; ++i) {
				array<int, 2> v=e[u[0]][u[1]][i];
				if(v[0]!=-2)
					ud(d, v[0], v[1], di+1);
			}
		}
		bd[di].clear();
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> w >> h;
	for(int i=0; i<h; ++i)
		cin >> g[i];
	memset(e, -1, sizeof(e));
	for(int i=0; i<h; ++i)
		for(int j=0; j<w; ++j)
			for(int k=0; k<4; ++k)
				dfs(i, j, k);
	memset(d, 0x3f, sizeof(d));
	for(int i=0, k=0; i<n; ++i) {
		for(int j=i; j>=0; --j, ++k) {
			m1[j][i]=k;
			m2[k]={j, i};
			if(j<i) {
				for(int x=0; x<h; ++x)
					for(int y=0; y<w; ++y)
						for(int l=j; l<i; ++l)
							ud(d[k], x, y, d[m1[j][l]][x][y]+d[m1[l+1][i]][x][y]);
			} else
				for(int x=0; x<h; ++x)
					for(int y=0; y<w; ++y)
						if(g[x][y]-'0'-1==j)
							ud(d[k], x, y, 0);
			bfs(d[k]);
		}
	}
	for(int i=0; i<h; ++i)
		for(int j=0; j<w; ++j)
			ans=min(d[m1[0][n-1]][i][j], ans);
	cout << (ans>1e9?-1:ans);
}
