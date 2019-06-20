#include <bits/stdc++.h>
using namespace std;

const int mxN=250, di[4]={1, 0, -1, 0}, dj[4]={0, 1, 0, -1};
int t, r, c, d[mxN][mxN], a1[mxN][2*mxN-1], a2[mxN][2*mxN-1];
string g[mxN];
array<int, 2> qu[mxN*mxN];

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> t;
	for(int ti=1; ti<=t; ++ti) {
		cin >> r >> c;
		memset(d, 0x3f, sizeof(d));
		memset(a1, 0, sizeof(a1));
		memset(a2, 0, sizeof(a2));
		int qt=0;
		for(int i=0; i<r; ++i) {
			cin >> g[i];
			for(int j=0; j<c; ++j) {
				if(g[i][j]=='1') {
					d[i][j]=0;
					qu[qt++]={i, j};
				}
			}
		}
		for(int qh=0; qh<qt; ++qh) {
			array<int, 2> u=qu[qh];
			for(int k=0; k<4; ++k) {
				int ni=u[0]+di[k], nj=u[1]+dj[k];
				if(ni<0||ni>=r||nj<0||nj>=c||d[ni][nj]<1e9)
					continue;
				d[ni][nj]=d[u[0]][u[1]]+1;
				qu[qt++]={ni, nj};
			}
		}
		for(int i=0; i<r; ++i) {
			for(int j=-c+1; j<=r-1; ++j) {
				for(int k=0; k<c; ++k) {
					a1[i][j+c-1]=max(a1[i][j+c-1], min(d[i][k], j+k));
					a2[i][j+c-1]=max(a2[i][j+c-1], min(d[i][k], j+c-1-k));
				}
			}
		}
		int ans=1e9;
		for(int i=0; i<r; ++i) {
			for(int j=0; j<c; ++j) {
				int ca=0;
				for(int k=0; k<r; ++k)
					ca=max({ca, a1[k][abs(i-k)-j+c-1], a2[k][abs(i-k)-(c-1-j)+c-1]});
				ans=min(ca, ans);
			}
		}
		cout << "Case #" << ti << ": " << ans << "\n";
	}
}
