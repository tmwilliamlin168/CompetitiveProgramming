#include <bits/stdc++.h>
using namespace std;

const int mxN=2e4;
int n, k, a[mxN], dp[2][mxN+1], qt, m[mxN], b[mxN], mx[mxN+1];

void al(int mi, int bi, bool mo) {
	if(qt&&mi==m[qt-1]) {
		if(bi>b[qt-1])
			return;
		--qt;
	}
	while(qt>1&&(bi-b[qt-1])/(m[qt-1]-mi)<(b[qt-1]-b[qt-2])/(m[qt-2]-m[qt-1])^mo)
		--qt;
	m[qt]=mi;
	b[qt]=bi;
	++qt;
}

int qry(int x) {
	while(qt>1&&m[qt-2]*x+b[qt-2]<m[qt-1]*x+b[qt-1])
		--qt;
	return m[qt-1]*x+b[qt-1];
}

void cdp(int f[mxN+1], int t[mxN+1], int l, int r) {
	if(l>=r)
		return;
	int m=(l+r)/2;
	mx[m]=mx[m+1]=a[m];
	for(int i=m-1; i>=l; --i)
		mx[i]=max(a[i], mx[i+1]);
	for(int i=m+2; i<=r; ++i)
		mx[i]=max(a[i-1], mx[i-1]);
	for(int il=m+1, ir=m+1; ir<=r; ++ir) {
		while(il>l&&mx[il-1]<=mx[ir]) {
			--il;
			al(-il, f[il], 1);
		}
		t[ir]=min(qry(mx[ir])+ir*mx[ir], t[ir]);
	}
	qt=0;
	al(2e4, 1e9, 0);
	for(int il=l, ir=r; ir>m; --ir) {
		while(il<=m&&mx[il]>=mx[ir]) {
			al(mx[il], f[il]-il*mx[il], 0);
			++il;
		}
		t[ir]=min(qry(ir), t[ir]);
	}
	qt=0;
	cdp(f, t, l, m);
	cdp(f, t, m+1, r);
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> n >> k;
	for(int i=0; i<n; ++i)
		cin >> a[i];
	memset(dp[0], 0x3f, sizeof(dp[0]));
	dp[0][0]=0;
	for(int i=1; i<=k; ++i) {
		memset(dp[i&1], 0x3f, sizeof(dp[0]));
		cdp(dp[i&1^1], dp[i&1], 0, n);
	}
	cout << dp[k&1][n];
}
