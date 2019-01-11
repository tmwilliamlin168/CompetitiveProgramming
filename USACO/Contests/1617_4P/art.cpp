#include <bits/stdc++.h>
using namespace std;

const int mxN=1e3;
int n, a[mxN][mxN], a2, c[mxN+1][mxN+1], l1[mxN*mxN+1], r1[mxN*mxN+1], l2[mxN*mxN+1], r2[mxN*mxN+1], ans;
bool b[mxN*mxN+1], d;

int main() {
	ifstream cin("art.in");
	ofstream cout("art.out");

	cin >> n;
	memset(l1+1, 0x3f, n*n*4);
	memset(l2+1, 0x3f, n*n*4);
	for(int i=0; i<n; ++i) {
		for(int j=0; j<n; ++j) {
			cin >> a[i][j];
			d|=a2&&a[i][j]&&a[i][j]!=a2;
			l1[a[i][j]]=min(i, l1[a[i][j]]);
			r1[a[i][j]]=max(i, r1[a[i][j]]);
			l2[a[i][j]]=min(j, l2[a[i][j]]);
			r2[a[i][j]]=max(j, r2[a[i][j]]);
			if(a[i][j])
				a2=a[i][j];
		}
	}
	for(int i=1; i<=n*n; ++i) {
		if(l1[i]>r1[i])
			continue;
		++c[l1[i]][l2[i]];
		--c[l1[i]][r2[i]+1];
		--c[r1[i]+1][l2[i]];
		++c[r1[i]+1][r2[i]+1];
	}
	for(int i=0; i<n; ++i)
		for(int j=0; j<n; ++j)
			c[i][j+1]+=c[i][j];
	for(int i=0; i<n; ++i)
		for(int j=0; j<n; ++j)
			c[i+1][j]+=c[i][j];
	for(int i=0; i<n; ++i)
		for(int j=0; j<n; ++j)
			b[a[i][j]]|=c[i][j]>1;
	for(int i=1; i<=n*n; ++i)
		ans+=!b[i];
	cout << ans-(n>1&&!d);
}
