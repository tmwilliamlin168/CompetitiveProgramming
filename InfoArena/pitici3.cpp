#include <bits/stdc++.h>
using namespace std;

const int mxN=2e3;
int n, h[mxN], l[mxN], d, p[mxN], dp[mxN+1][mxN+1];

int main() {
	ifstream cin("pitici3.in");
	ofstream cout("pitici3.out");

	cin >> n;
	memset(dp, 0xc0, sizeof(dp));
	dp[0][0]=0;
	for(int i=0; i<n; ++i) {
		cin >> h[i] >> l[i];
		dp[0][0]+=h[i];
	}
	cin >> d;
	iota(p, p+n, 0);
	sort(p, p+n, [](const int &i, const int &j) {
		return h[i]+l[i]<h[j]+l[j];
	});
	for(int i=0; i<n; ++i) {
		for(int j=0; j<=i; ++j) {
			if(dp[i][j]+l[p[i]]>=d)
				dp[i+1][j+1]=dp[i][j]-h[p[i]];
			dp[i+1][j]=max(dp[i][j], dp[i+1][j]);
		}
	}
	for(int i=n; ; --i) {
		if(dp[n][i]>=0) {
			cout << i;
			break;
		}
	}
}
