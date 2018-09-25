#include <bits/stdc++.h>
using namespace std;

const int mxN=300;
int t, n, ai, c[4], dp[mxN+1][mxN+1][mxN+1][4];

void solve() {
	cin >> n;
	c[0]=c[1]=c[2]=c[3]=0;
	for(int i=0; i<n; ++i)
		cin >> ai, ++c[ai%4];
	cout << (dp[c[1]][c[2]][c[3]][0]^c[0]&1?"Ghayeeth\n":"Siroj\n");
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	for(int i=0; i<=mxN; ++i) {
		for(int j=0; j<=mxN-i; ++j) {
			for(int k=0; k<=mxN-i-j; ++k) {
				for(int l=0; l<4; ++l) {
					if(l==2) {
						dp[i][j][k][l]=9;
						continue;
					}
					int a=i?dp[i-1][j][k][(l+1)&3]:9, b=j?dp[i][j-1][k][(l+2)&3]:9, c=k?dp[i][j][k-1][(l+3)&3]:9;
					for(int m=0; ; ++m) {
						if(a!=m&&b!=m&&c!=m) {
							dp[i][j][k][l]=m;
							break;
						}
					}
				}
			}
		}
	}
	cin >> t;
	while(t--)
		solve();
}
