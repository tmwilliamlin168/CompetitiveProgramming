/*
	- http://codeforces.com/blog/entry/8755
*/

#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int mxN=1e3;
int n, m, qt, x0, y0, x1, y1;
ll vi, ft[4][mxN+1][mxN+1];

void upd(int x, int y, ll v) {
	int k=x&1|(y&1)<<1;
	for(int i=x+1; i<=n; i+=i&-i)
		for(int j=y+1; j<=n; j+=j&-j)
			ft[k][i][j]^=v;
}

ll qry(int x, int y) {
	int k=x&1|(y&1)<<1;
	ll r=0;
	for(int i=x; i; i-=i&-i)
		for(int j=y; j; j-=j&-j)
			r^=ft[k^3][i][j];
	return r;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> m;
	while(m--) {
		cin >> qt >> x0 >> y0 >> x1 >> y1, --x0, --y0;
		if(qt==2) {
			cin >> vi;
			upd(x1, y1, vi);
			upd(x1, y0, vi);
			upd(x0, y1, vi);
			upd(x0, y0, vi);
		} else
			cout << (qry(x1, y1)^qry(x1, y0)^qry(x0, y1)^qry(x0, y0)) << "\n";
	}
}
