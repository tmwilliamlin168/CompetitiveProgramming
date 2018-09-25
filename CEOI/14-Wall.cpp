/*
	- http://ceoi2014.informatik-olympiade.de/wp-content/uploads/2014/06/wall-spoiler.pdf
*/

#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int mxN=400, nb[4][2]={{1, 0}, {0, 1}, {-1, 0}, {0, -1}}, f[4][2]={{1, 3}, {2, 3}, {0, 2}, {0, 1}};
int n, m, e[mxN+1][mxN+1][2], p[mxN+1][mxN+1], a[mxN][mxN], b[mxN+1][mxN+1][2];;
ll d[mxN+1][mxN+1][4];
priority_queue<array<ll, 4>, vector<array<ll, 4>>, greater<array<ll, 4>>> pq;

void dijkstra(bool c) {
	memset(d, 0x3f, sizeof(d));
	d[0][0][1]=0;
	pq.push({0, 0, 0, 1});
	while(!pq.empty()) {
		array<ll, 4> u=pq.top();
		pq.pop();
		int i=u[1], j=u[2], k=u[3];
		if(d[i][j][k]<u[0])
			continue;
		if(c&&(i||j)) {
			if((i<1-k%2||!b[i-1+k%2][j][0])&&d[i][j][k^2]>u[0]) {
				d[i][j][k^2]=u[0];
				pq.push({u[0], i, j, k^2});
			}
			if((j<1-k/2||!b[i][j-1+k/2][1])&&d[i][j][k^1]>u[0]) {
				d[i][j][k^1]=u[0];
				pq.push({u[0], i, j, k^1});
			}
		}
		for(int l=0; l<4; ++l) {
			int ni=i+nb[l][0], nj=j+nb[l][1];
			if(c&&f[l][0]!=k&&f[l][1]!=k||ni<0||ni>n||nj<0||nj>m)
				continue;
			int nk=k^(c?l%2+1:0), ne=e[i-(l==2)][j-(l==3)][l&1];
			if(d[ni][nj][nk]>u[0]+ne) {
				d[ni][nj][nk]=u[0]+ne;
				pq.push({u[0]+ne, ni, nj, nk});
				p[ni][nj]=l;
			}
		}
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> m;
	for(int i=0; i<n; ++i)
		for(int j=0; j<m; ++j)
			cin >> a[i][j];
	for(int k=0; k<2; ++k)
		for(int i=0; i<n+k; ++i)
			for(int j=0; j<m+!k; ++j)
				cin >> e[i][j][k];
	dijkstra(0);
	for(int i1=0; i1<n; ++i1) {
		for(int j1=0; j1<m; ++j1) {
			if(!a[i1][j1])
				continue;
			int i=i1, j=j1;
			while(i||j) {
				int cp=p[i][j], &cb=b[i-(cp==0)][j-(cp==1)][cp&1];
				if(cb)
					break;
				cb=1;
				i-=nb[cp][0];
				j-=nb[cp][1];
			}
			b[i1][j1][0]=b[i1][j1][1]=b[i1][j1+1][0]=b[i1+1][j1][1]=1;
		}
	}
	dijkstra(1);
	cout << d[0][0][2];
}
