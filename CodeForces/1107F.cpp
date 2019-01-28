#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int mxN=500;
int n, p[mxN];
ll a[mxN], b[mxN], c[mxN], dp[mxN+1][mxN+1];

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> n;
	for(int i=0; i<n; ++i)
		cin >> a[i] >> b[i] >> c[i];
	iota(p, p+n, 0);
	sort(p, p+n, [&](const int &i, const int &j) {
		return b[i]>b[j];
	});
	for(int i=0; i<n; ++i) {
		for(int j=0; j<=i; ++j) {
			dp[i+1][j]=max({dp[i][j], dp[i][j]+a[p[i]]-b[p[i]]*c[p[i]], dp[i+1][j]});
			dp[i+1][j+1]=max(dp[i+1][j], dp[i][j]+a[p[i]]-b[p[i]]*j);
		}
	}
	cout << dp[n][n];
}
