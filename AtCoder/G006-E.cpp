#include <bits/stdc++.h>
using namespace std;

const int mxN=1e5;
int n, a[3][mxN], c[2], ft[mxN+1];

void fk() {
	cout << "No";
	exit(0);
}

void upd(int i) {
	for(; i<=n; i+=i&-i)
		++ft[i];
}

int qry(int i) {
	int r=0;
	for(; i; i-=i&-i)
		r+=ft[i];
	return r;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> n;
	for(int i=0; i<3; ++i)
		for(int j=0; j<n; ++j)
			cin >> a[i][j];
	for(int k : {0, 1}) {
		for(int i=k; i<n; i+=2) {
			if(a[1][i]%3^2||abs(a[0][i]-a[1][i])>1||abs(a[2][i]-a[1][i])>1||(a[1][i]/3^i)&1)
				fk();
			c[k]+=a[0][i]>a[2][i];
			c[k^1]+=qry(n-a[1][i]/3);
			upd(n-a[1][i]/3);
		}
		memset(ft+1, 0, 4*n);
	}
	if(c[0]&1||c[1]&1)
		fk();
	cout << "Yes";
}
