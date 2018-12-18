#include <bits/stdc++.h>
using namespace std;

const int mxN=1e4, mxK=1e3;
int n, k, s[mxN], dp[mxN+1];

int main() {
	ifstream cin("teamwork.in");
	ofstream cout("teamwork.out");
	
	//input
	cin >> n >> k;
	for(int i=0; i<n; ++i)
		cin >> s[i];
	//calc the dp
	for(int i=1; i<=n; ++i) {
		int runningmax=0;
		for(int j=0; j<k&&i>j; ++j) {
			runningmax=max(s[i-j-1], runningmax);
			dp[i]=max(dp[i-j-1]+runningmax*(j+1), dp[i]);
		}
	}
	cout << dp[n];
}
