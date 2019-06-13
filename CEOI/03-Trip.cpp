/*
	- dp[i][j] stores all distinct LCS
	- Only keep 2 layers of DP to pass the ML of 16MB
	- O(n*m*max(n, m)*(num LCS)) time
	- O(m*max(n, m)*(num LCS)) memory
*/

#include <bits/stdc++.h>
using namespace std;

const int mxN=80;
string s, t;
int n, m;
vector<string> dp[mxN+1][mxN+1];

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> s >> t, n=s.size(), m=t.size();
	dp[0][0]={""};
	for(int i=1; i<=n; ++i)
		dp[i][0]={""};
	for(int i=1; i<=m; ++i)
		dp[0][i]={""};
	for(int i=1; i<=n; ++i) {
		for(int j=1; j<=m; ++j) {
			if(s[i-1]^t[j-1]) {
				vector<string> a=dp[i-1][j], b=dp[i][j-1];
				if(a[0].size()<b[0].size())
					a.clear();
				else if(a[0].size()>b[0].size())
					b.clear();
				dp[i][j].insert(dp[i][j].end(), a.begin(), a.end());
				dp[i][j].insert(dp[i][j].end(), b.begin(), b.end());
				sort(dp[i][j].begin(), dp[i][j].end());
				dp[i][j].resize(unique(dp[i][j].begin(), dp[i][j].end())-dp[i][j].begin());
			} else {
				dp[i][j]=dp[i-1][j-1];
				for(string &s : dp[i][j])
					s+=t[j-1];
			}
			vector<string>().swap(dp[i-1][j-1]);
		}
	}
	for(string s : dp[n][m])
		cout << s << "\n";
}
