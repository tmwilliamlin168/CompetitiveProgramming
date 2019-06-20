#include <bits/stdc++.h>
using namespace std;

const int mxN=400;
int n, dp[mxN][8][mxN+1][4], b[mxN][7];
string s;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> n >> s;
	for(char &c : s)
		c=(c>'G')+(c>'R');
	for(int i=0; i<n; ++i) {
		if(i)
			memcpy(b[i], b[i-1], sizeof(b[0]));
		for(int j=1; j<7; ++j)
			if(j>>s[i]&1)
				b[i][j]=s[i];
	}
	memset(dp, 0x3f, sizeof(dp));
	dp[0][1<<s[0]][1][3]=0;
	auto tm=[](int &a, int b) {
		a=min(a, b);
	};
	for(int i=1; i<n; ++i) {
		for(int j=1; j<7; ++j) {
			for(int k=1; k<=i; ++k) {
				for(int l=0; l<4; ++l) {
					tm(dp[i][j|1<<s[i]][k+1][l], dp[i-1][j][k][l]);
					if(j>>s[i]&1)
						continue;
					if(l!=s[i])
						tm(dp[i][j][k][s[i]], dp[i-1][j][k][l]+k);
					if(k>1)
						tm(dp[i][j][k-1][s[i]], dp[i-1][j][k][l]+k-1);
					else
						tm(dp[i][1<<s[i]][1][b[i-1][j]], dp[i-1][j][1][l]);
				}
			}
		}
	}
	int ans=1e9;
	for(int i=1; i<5; ++i)
		for(int j=0; j<4; ++j)
			ans=min(dp[n-1][i][1][j], ans);
	cout << (ans>=1e9?-1:ans);
}
