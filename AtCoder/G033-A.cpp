#include <bits/stdc++.h>
using namespace std;

const int mxN=1e3, di[4]={1, 0, -1, 0}, dj[4]={0, 1, 0, -1};
int h, w, d[mxN][mxN], ans;
string a[mxN];
queue<array<int, 2>> qu;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> h >> w;
	memset(d, 0x3f, sizeof(d));
	for(int i=0; i<h; ++i) {
		cin >> a[i];
		for(int j=0; j<w; ++j) {
			if(a[i][j]=='#') {
				qu.push({i, j});
				d[i][j]=0;
			}
		}
	}
	while(!qu.empty()) {
		array<int, 2> u=qu.front();
		qu.pop();
		ans=max(ans, d[u[0]][u[1]]);
		for(int k=0; k<4; ++k) {
			int ni=u[0]+di[k], nj=u[1]+dj[k];
			if(ni>=0&&ni<h&&nj>=0&&nj<w&&d[ni][nj]>1e9) {
				d[ni][nj]=d[u[0]][u[1]]+1;
				qu.push(array<int, 2>{ni, nj});
			}
		}
	}
	cout << ans;
}
