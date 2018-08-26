/*
	- I'm not entirely sure what I did, it just works :/
	- Use a dp for maximum weighted independent set on a tree
	- If p[i]=1, just add dp[i] to dp[h[i]] as you can consider them as being the same
	- The edges with p[i]=2 form cliques
		- In each clique, you can only take one node
*/

#include <bits/stdc++.h>
using namespace std;

const int mxN=1e5;
int dp[mxN][2];

int findSample(int n, int c[], int h[], int p[]) {
	for(int i=0; i<n; ++i)
		dp[i][1]=c[i];
	for(int i=n-1; i; --i) {
		if(p[i]==0) {
			dp[h[i]][0]+=dp[i][1];
			dp[h[i]][1]+=dp[i][0];
		} else if(p[i]==1) {
			dp[h[i]][0]+=dp[i][0];
			dp[h[i]][1]+=dp[i][1];
		} else {
			dp[h[i]][1]=max(dp[h[i]][0]+dp[i][1], dp[h[i]][1]+dp[i][0]);
			dp[h[i]][0]+=dp[i][0];
		}
		dp[h[i]][1]=max(dp[h[i]][0], dp[h[i]][1]);
	}
	return max(dp[0][0], dp[0][1]);
}
