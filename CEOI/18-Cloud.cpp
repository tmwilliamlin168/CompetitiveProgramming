#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int mxN=2e3, mxC=50;
int n, m, ci, fi, vi;
ll dp[mxN+1][mxC*2+1], ans;
vector<array<int, 3>> v1, v2;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n;
	for(int i=0; i<n; ++i) {
		cin >> ci >> fi >> vi;
		v1.push_back({fi, ci, vi});
	}
	sort(v1.begin(), v1.end(), greater<array<int, 3>>());
	cin >> m;
	for(int i=0; i<m; ++i) {
		cin >> ci >> fi >> vi;
		v2.push_back({fi, ci, vi});
	}
	sort(v2.begin(), v2.end(), greater<array<int, 3>>());
	memset(dp, 0x96, sizeof(dp));
	dp[0][50]=0;
	for(int i=0; i<=n; ++i) {
		for(int j=0; j<=m; ++j) {
			for(int k=2*mxC; k>=0; --k) {
				if(k<mxC&&i<n&&j&&v1[i][0]>=v2[j-1][0])
					dp[j][k+v1[i][1]]=max(dp[j][k]-v1[i][2], dp[j][k+v1[i][1]]);
				if(k>=mxC&&j<m) {
					dp[j+1][k-v2[j][1]]=max(dp[j][k]+v2[j][2], dp[j+1][k-v2[j][1]]);
					dp[j+1][k]=max(dp[j][k], dp[j+1][k]);
				}
			}
		}
	}
	for(int i=mxC; i<=2*mxC; ++i)
		ans=max(dp[m][i], ans);
	cout << ans;
}
