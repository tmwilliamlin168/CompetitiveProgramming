#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int mxN=50;
int n, m, k, M;
ll dp[mxN+1][mxN+1][mxN+1], dp2[mxN+1][mxN+1];

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> m >> k >> M;
	dp[0][0][0]=1;
	for(int a=1; a<=n; ++a) {
		memset(dp2, 0, (a+1)*sizeof(dp2[0]));
		for(int b=1; b<=a; ++b) {
			for(int c=1; c<=b; ++c) {
				for(int d=a; d<=n; ++d) {
					for(int e=m; e; --e) {
						dp[a][c][e]=(dp[b-1][c-1][e-1]+dp[a][c][e-1]+dp[a][c][e])%M;
						if(d>a)
							dp2[c][e]=(dp[b-1][c-1][e-1]+dp2[c][e-1]+dp2[c][e])%M;
					}
				}
			}
		}
		for(int b=0; b<=a; ++b)
			for(int c=0; c<=m; ++c)
				dp[a][b][c]=(dp[a][b][c]-dp2[b][c]+M+dp[a-1][b][c])%M;
	}
	cout << dp[n][k][m];
}
