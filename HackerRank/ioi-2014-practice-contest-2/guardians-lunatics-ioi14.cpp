#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int mxN=8000;
int n, k;
ll ps[mxN+1], dp[2][mxN+1];

inline void cdp(int a, int l1, int r1, int l2, int r2) {
	if(l1>r1)
		return;
	int m1=(l1+r1)/2, mi;
	for(int i=l2; i<=m1&&i<=r2; ++i) {
		if(dp[a^1][i]+(m1-i)*(ps[m1]-ps[i])<dp[a][m1]) {
			dp[a][m1]=dp[a^1][i]+(m1-i)*(ps[m1]-ps[i]);
			mi=i;
		}
	}
	cdp(a, l1, m1-1, l2, mi);
	cdp(a, m1+1, r1, mi, r2);
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> k;
	for(int i=0; i<n; ++i)
		cin >> ps[i+1], ps[i+1]+=ps[i];
	memset(dp[0], 0x3F, 8*(n+1));
	dp[0][0]=0;
	for(int i=1; i<=k; ++i) {
		memset(dp[i&1], 0x3F, 8*(n+1));
		cdp(i&1, 0, n, 0, n);
	}
	cout << dp[k&1][n];
}
