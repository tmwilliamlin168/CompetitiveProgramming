/*
	- Greedily start from first bit to the last and determine if it's possible if the current bit is not set
	- To determine if it's possible (all but the last subtask)
		- dp[i][j] = if it's possible to split first i items into j groups
	- For the last subtask O(n^3) won't work but a=1
		- It is always better to choose the minimum number of groups when splitting
		- dp[i] = minimum number of groups to split first i items
*/

#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int mxN=2000;
int n, a, b, dp[mxN+1][mxN+1];
ll y[mxN];

inline bool can(ll x) {
	if(a>1)
		memset(dp[0], 0, 4*(b+1));
	dp[0][0]=a>1;
	for(int i=1; i<=n; ++i) {
		if(a==1) {
			dp[0][i]=b+1;
			ll ys=0;
			for(int j=i-1; j>=0; --j) {
				ys+=y[j];
				if(!(ys&~x))
					dp[0][i]=min(dp[0][j]+1, dp[0][i]);
			}
		} else {
			memset(dp[i], 0, 4*(b+1));
			ll ys=0;
			for(int j=i-1; j>=0; --j) {
				ys+=y[j];
				if(!(ys&~x))
					for(int k=1; k<=b; ++k)
						dp[i][k]|=dp[j][k-1];
			}
		}
	}
	if(a==1)
		return dp[0][n]<=b;
	for(int i=a; i<=b; ++i)
		if(dp[n][i])
			return 1;
	return 0;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> a >> b;
	for(int i=0; i<n; ++i)
		cin >> y[i];
	ll ans=(1LL<<41)-1;
	for(int i=40; i>=0; --i)
		if(can(ans^(1LL<<i)))
			ans^=1LL<<i;
	cout << ans;
}
