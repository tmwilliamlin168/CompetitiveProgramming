/*
	- Uses Knuth's optimization for O(n^2) (doesn't solve the problem though)
*/

#include <iostream>
using namespace std;

const int mxN=3000;
int n, ps[mxN+1], dp[mxN][mxN], h[mxN][mxN];

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	while(1) {
		cin >> n;
		if(!n)
			break;
		for(int i=0; i<n; ++i)
			cin >> ps[i+1], ps[i+1]+=ps[i];
		for(int i=1; i<n; ++i) {
			for(int j=0; j+i<n; ++j) {
				h[j][j+i]=i>1?h[j][j+i-1]:j;
				for(int k=h[j][j+i]+1; k<=(i>1?h[j+1][j+i]:j); ++k)
					if(dp[j][k]+dp[k+1][j+i]<dp[j][h[j][j+i]]+dp[h[j][j+i]+1][j+i])
						h[j][j+i]=k;
				dp[j][j+i]=dp[j][h[j][j+i]]+dp[h[j][j+i]+1][j+i]+ps[j+i+1]-ps[j];
			}
		}
		cout << dp[0][n-1] << "\n";
	}
}
