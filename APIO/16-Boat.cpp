/*
	- Grid compression, at most 2*n points are important
	- dp[i][j] = number of ways with first i schools such that the number of boats sent <= pts[j]
	- To calculate dp[i][j], iterate through k<i
		- Use dp[k][j-1] to find how many ways need to be added if school k+1 is the first to send a number of boats > pts[j-1]
*/

#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int mxN=500, M=1e9+7;
int n, a[mxN], b[mxN];
ll dp[mxN+1][2*mxN], c[2*mxN][mxN+1];
vector<int> pts;

inline ll modI(ll a, ll m) {
	return a<=1?a:(1-modI(m%a, a)*m)/a+m;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n;
	for(int i=0; i<n; ++i) {
		cin >> a[i] >> b[i], --a[i];
		pts.push_back(a[i]);
		pts.push_back(b[i]);
	}
	sort(pts.begin(), pts.end());
	pts.resize(unique(pts.begin(), pts.end())-pts.begin());
	for(int i=1; i<pts.size(); ++i) {
		c[i][1]=pts[i]-pts[i-1];
		for(int j=2; j<=n; ++j)
			c[i][j]=c[i][j-1]*(pts[i]-pts[i-1]+j-1)%M*modI(j, M)%M;
	}
	for(int i=0; i<pts.size(); ++i)
		dp[0][i]=1;
	for(int i=1; i<=n; ++i) {
		dp[i][0]=1;
		for(int j=1; j<pts.size(); ++j) {
			dp[i][j]=dp[i][j-1];
			for(int k=i, n2=0; k; --k) {
				if(pts[j]>a[k-1]&&pts[j]<=b[k-1]) {
					++n2;
					dp[i][j]+=dp[k-1][j-1]*c[j][n2]%M;
				}
			}
			dp[i][j]%=M;
		}
	}
	cout << dp[n][pts.size()-1]-1;
}
