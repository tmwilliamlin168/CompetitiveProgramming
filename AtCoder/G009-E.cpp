/*
	- Imagine creating a tree with n+m leaf nodes and each internal node having k children
	- There is exactly one way to get a multiple of 1/k
	- Otherwise, k-1 children will just be 0s and 1s
	- Everything else can go into the remaining child
	- Proof that we can obtain all values with this construction
		- A node's contribution is 1/k^depth, so we can switch nodes with the same depth
		- We can make it so that in each level, only one node's subtree has different leaves
		- Lastly, we can repeatedly remove nodes that have the same type of leaves and place them elsewhere
	- A different number of children of the root that are 1s also implies that two trees must have a different value
	- We can use DP
*/

#include <bits/stdc++.h>
using namespace std;

const int mxN=2e3, M=1e9+7;
int n, m, k, dp[mxN+1][mxN+1];

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> n >> m >> k;
	for(int i=1; i<k; ++i)
		dp[i][k-i]=1;
	for(int a=2*k-1; a<=n+m; a+=k-1) {
		for(int i=max(a-m, 1); i<=min(a-1, n); ++i) {
			int j=a-i;
			dp[i][j]=1;
			for(int l=max(k-j, 0); l<min(k, i); ++l)
				dp[i][j]=(dp[i][j]+dp[i-l][j-(k-1-l)])%M;
		}
	}
	cout << dp[n][m];
}
