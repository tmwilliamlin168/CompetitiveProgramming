/*
	- The final word will be the concatenation of subwords
	- The subwords end with letter > n/2 so that they can concatenated together
	- In order to avoid overcounting, those subwords cannot be concatenation of other subwords
	- This also reduces the length of each subword to O(logn)
	- One dp for counting the number of subwords of a specific length
	- Another dp for counting the number of ways to concatenate them
	- O((n+m)logn)
*/

#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int mxN=1e5, mxM=5e5, M=1e8+7, mxL=16;
int t, n, m;
ll dp1[mxN+2][mxL+1], dp2[mxM+1];

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> t;
	while(t--) {
		cin >> n >> m;
		memset(dp1, 0, (n+2)*sizeof(dp1[0]));
		for(int i=n; i>n/2; --i)
			dp1[i][1]=dp1[i+1][1]+1;
		for(int i=n/2; i; --i)
			for(int j=1; j<=mxL; ++j)
				dp1[i][j]=(dp1[2*i][j-1]+dp1[i+1][j])%M;
		memset(dp2, 0, 8*(m+1));
		dp2[0]=1;
		for(int i=1; i<=m; ++i)
			for(int j=1; j<=min(i, mxL); ++j)
				dp2[i]+=dp2[i-j]*dp1[1][j]%M;
		cout << dp2[m]%M << "\n";
	}
}
