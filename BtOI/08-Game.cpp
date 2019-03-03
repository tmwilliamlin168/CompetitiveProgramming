/*
	- If A and B have odd manhattan distance, A can always win
	- A and B will always travel along a shortest path
	- A and B will only move forward along the shortest path
	- Split the shortest path DAG from A to B into layers
	- dp[layer 1][layer 2][pos 1][pos 2] (layer 2 is +-1 layer 1)
*/

#include <bits/stdc++.h>
using namespace std;
 
const int mxN=300, di[4]={0, 1, 0, -1}, dj[4]={1, 0, -1, 0};
int t, n, m, ai, aj, bi, bj, d[mxN][mxN];
string g[mxN];
bool dp[2][2*mxN][2*mxN];
vector<array<int, 2>> p[mxN][mxN], bd[mxN*mxN];
array<int, 2> qu[mxN*mxN];
 
void dfs(int i, int j) {
	bd[d[i][j]].push_back({i, j});
	d[i][j]=-1;
	for(array<int, 2> v : p[i][j])
		if(d[v[0]][v[1]]!=-1)
			dfs(v[0], v[1]);
}
 
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> t;
	while(t--) {
		cin >> n;
		for(int i=0; i<n; ++i) {
			cin >> g[i];
			auto f=find(g[i].begin(), g[i].end(), 'A');
			if(f!=g[i].end()) {
				ai=i;
				aj=f-g[i].begin();
			}
			f=find(g[i].begin(), g[i].end(), 'B');
			if(f!=g[i].end()) {
				bi=i;
				bj=f-g[i].begin();
			}
		}
		if(ai+aj+bi+bj&1) {
			cout << "A\n";
			continue;
		}
		memset(d, 0x3f, sizeof(d));
		for(int i=0; i<n; ++i) {
			for(int j=0; j<n; ++j) {
				p[i][j].clear();
				bd[i*n+j].clear();
			}
		}
		d[ai][aj]=0;
		qu[0]={ai, aj};
		for(int qh=0, qt=1; qh<qt; ++qh) {
			array<int, 2> u=qu[qh];
			for(int k=0; k<4; ++k) {
				int ni=u[0]+di[k], nj=u[1]+dj[k];
				if(ni<0||ni>=n||nj<0||nj>=n||g[ni][nj]=='#')
					continue;
				if(d[ni][nj]>1e9) {
					d[ni][nj]=d[u[0]][u[1]]+1;
					qu[qt++]={ni, nj};
				}
				if(d[ni][nj]==d[u[0]][u[1]]+1)
					p[ni][nj].push_back(u);
			}
		}
		int la=d[bi][bj]/2, ra=la;
		dfs(bi, bj);
		for(int i=0; i<bd[la].size(); ++i)
			for(int j=0; j<bd[ra].size(); ++j)
				dp[0][i][j]=i^j;
		for(; la; ) {
			++ra;
			memset(dp[1], 0, sizeof(dp[0]));
			for(int i=0; i<bd[ra].size(); ++i)
				for(int j=0; j<bd[ra-1].size(); ++j)
					if(abs(bd[ra][i][0]-bd[ra-1][j][0])+abs(bd[ra][i][1]-bd[ra-1][j][1])==1)
						for(int k=0; k<bd[la].size(); ++k)
							dp[1][k][i]|=!dp[0][k][j];
			--la;
			memset(dp[0], 0, sizeof(dp[0]));
			for(int i=0; i<bd[la].size(); ++i)
				for(int j=0; j<bd[la+1].size(); ++j)
					if(abs(bd[la][i][0]-bd[la+1][j][0])+abs(bd[la][i][1]-bd[la+1][j][1])==1)
						for(int k=0; k<bd[ra].size(); ++k)
							dp[0][i][k]|=!dp[1][j][k];
		}
		cout << (dp[0][0][0]?'A':'B') << "\n";
	}
}
