#include <bits/stdc++.h>
using namespace std;

const int mxN=1e3;
int n, ans[mxN+1][mxN];
array<int, 2> a[mxN];

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> n;
	for(int i=0; i<n; ++i) {
		cin >> a[i][0];
		a[i][1]=i;
	}
	sort(a, a+n, greater<array<int, 2>>());
	for(int i=0; i<n; ++i)
		for(int j=0; j<a[i][0]; ++j)
			ans[(i+j)%(n+1)][a[i][1]]=1;
	cout << n+1 << "\n";
	for(int i=0; i<=n; ++i) {
		for(int j=0; j<n; ++j)
			cout << ans[i][j];
		cout << "\n";
	}
}
