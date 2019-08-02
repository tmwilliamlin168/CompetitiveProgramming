#include "boxes.h"
#include <bits/stdc++.h>
using namespace std;

long long dp[10000002], ans;

long long delivery(int n, int k, int l, int p[]) {
	int m=upper_bound(p, p+n, l/2)-p;
	for(int i=1; i<=m; ++i) {
		dp[i]=2*p[i-1];
		if(i>k)
			dp[i]+=dp[i-k];
	}
	for(int i=n; i>m; --i) {
		dp[i]=2*(l-p[i-1]);
		if(i+k<=n)
			dp[i]+=dp[i+k];
	}
	ans=dp[m]+dp[m+1];
	for(int i=m+1; i<m+k; ++i)
		ans=min(dp[max(i-k, 0)]+l+dp[min(i+1, n+1)], ans);
	return ans;
}
