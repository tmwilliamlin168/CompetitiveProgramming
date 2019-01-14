/*
	- Similar to LCS, dp[i][j] = max(dp[i-1][j], dp[i][j-1], dp[l[i]-1][l[j]-1]+2 if a[i]==b[j])
		- l[i] is the previous occurence of the element at index i
	- O(n^2) time and memory
	- Do dp from small i to big i
	- For dp[i-1][j], we can just use the 2 layers trick to optimize memory
	- For dp[l[i]-1][l[j]-1], we only have to store 1 value for each j
*/

#include <bits/stdc++.h>
using namespace std;

const int mxN=1.5e4;
int n, m, a[mxN], bi, dp1[2][mxN+1], dp2[mxN];
unordered_map<int, int> mp;
vector<int> o[2*mxN];

void rm(int &x) {
	cin >> x;
	if(mp.find(x)==mp.end())
		mp.insert({x, mp.size()});
	x=mp[x];
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> n >> m;
	for(int i=0; i<n; ++i)
		rm(a[i]);
	for(int i=0; i<m; ++i) {
		rm(bi);
		o[bi].push_back(i);
	}
	for(int i=0; i<n; ++i) {
		memcpy(dp1[i&1], dp1[i&1^1], 4*(m+1));
		for(int oi : o[a[i]])
			dp1[i&1][oi+1]=max(dp2[oi], dp1[i&1][oi+1]);
		for(int j=1; j<m; ++j)
			dp1[i&1][j+1]=max(dp1[i&1][j], dp1[i&1][j+1]);
		for(int j=1; j<o[a[i]].size(); ++j)
			dp2[o[a[i]][j]]=dp1[i&1^1][o[a[i]][j-1]]+2;
	}
	cout << dp1[n&1^1][m];
}
