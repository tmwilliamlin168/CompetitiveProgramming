#include <bits/stdc++.h>
using namespace std;

long long dp[50*3000+1], n, p, v;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> n >> p >> v;
	for(int i=0; ; ++i) {
		dp[i]=1;
		for(int j=2; i-v-j*p>=0; ++j)
			dp[i]=max(j*dp[i-v-j*p], dp[i]);
		if(dp[i]>=n) {
			cout << i;
			break;
		}
	}
}
