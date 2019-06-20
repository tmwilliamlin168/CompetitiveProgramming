#include <bits/stdc++.h>
using namespace std;

const int mxN=1e5;
int n, m, b[mxN];
array<int, 2> a[mxN];

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> n >> m;
	for(int i=0; i<n; ++i)
		cin >> a[i][1] >> a[i][0];
	for(int i=0; i<m; ++i)
		cin >> b[i];
	sort(a, a+n);
	sort(b, b+m);
	int ans=m-1;
	for(int i=n-1; i>=0; --i)
		if(ans>=0&&a[i][1]<=b[ans])
			--ans;
	cout << m-1-ans;
}
