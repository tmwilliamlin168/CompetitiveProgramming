#include <bits/stdc++.h>
using namespace std;

class BeatTheStar {
public:
	long double dp[101][10000], ans;
	double doesItMatter(int n, int g) {
		dp[0][0]=1;
		for(int i=1; i<=n; ++i) {
			for(int j=0; j<=i*(i-1)/2; ++j) {
				if(i^g) {
					dp[i][j]+=0.5*dp[i-1][j];
					dp[i][j+i]+=0.5*dp[i-1][j];
				} else
					dp[i][j]=dp[i-1][j];
			}
		}
		for(int i=0; i<=n*(n+1)/2; ++i)
			if((i<n*(n+1)/2-i)!=(i+g<n*(n+1)/2-(i+g)))
				ans+=dp[n][i];
		return ans;
	}
};
