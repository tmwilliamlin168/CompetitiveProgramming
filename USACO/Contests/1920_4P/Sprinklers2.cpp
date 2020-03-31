#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int mxN=2e3, M=1e9+7, I2=5e8+4;
int n;
string g[mxN];
ll dp1[mxN+1][mxN+1], dp2[mxN+1][mxN+1];

int main() {
	ifstream cin("sprinklers2.in");
	ofstream cout("sprinklers2.out");
	
	cin >> n;
	for(int i=0; i<n; ++i)
		cin >> g[i];
	dp1[0][0]=dp2[0][0]=1;
	for(int i=0; i<=n; ++i) {
		for(int j=0; j<=n; ++j) {
			if(i<n) {
				dp1[i+1][j]=(dp1[i+1][j]+dp1[i][j])%M;
				if(j&&g[i][j-1]=='.')
					dp1[i+1][j]=(dp1[i+1][j]+dp2[i][j]*I2)%M;
			}
			if(j<n) {
				dp2[i][j+1]=(dp2[i][j+1]+dp2[i][j])%M;
				if(i&&g[i-1][j]=='.')
					dp2[i][j+1]=(dp2[i][j+1]+dp1[i][j]*I2)%M;
			}
		}
	}
	int ans=(dp1[n][n]+dp2[n][n])%M;
	for(int i=0; i<n; ++i)
		for(int j=0; j<n; ++j)
			if(g[i][j]=='.')
				ans=ans*2%M;
	cout << ans;
}
