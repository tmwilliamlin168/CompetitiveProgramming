#include <bits/stdc++.h>
using namespace std;
 
const int mxN=300;
int n, m, w[mxN][mxN], dp[mxN][mxN], w2[mxN][mxN][mxN], w3[mxN][mxN][mxN];
 
int main() {
	ifstream cin("pieaters.in");
	ofstream cout("pieaters.out");
 
	cin >> n >> m;
	for(int wi, l, r; m--; ) {
		cin >> wi >> l >> r;
		w[l-1][r-1]=wi;
	}
	for(int i=0; i<n; ++i) {
		for(int j=i; j<n; ++j) {
			for(int k=j; k<n; ++k) {
				w2[i][j][k]=w[j][k];
				if(i<j)
					w2[i][j][k]=max(w2[i][j][k], w2[i][j-1][k]);
			}
		}
	}
	for(int i=0; i<n; ++i) {
		for(int j=i; j<n; ++j) {
			for(int k=j; k<n; ++k) {
				w3[i][j][k]=w2[i][j][k];
				if(j<k)
					w3[i][j][k]=max(w3[i][j][k], w3[i][j][k-1]);
			}
		}
	}
	for(int i=n-1; ~i; --i) {
		for(int j=i; j<n; ++j) {
			if(j-i>0) {
				for(int k=i; k<=j; ++k)
					dp[i][j]=max(dp[i][j], w[i][k]+dp[i+1][j]);
				for(int k=i; k<=j; ++k)
					dp[i][j]=max(dp[i][j], w[k][j]+dp[i][j-1]);
				for(int k=i+1; k<j; ++k)
					dp[i][j]=max(dp[i][j], w3[i][k][j]+dp[i][k-1]+dp[k+1][j]);
			}
			dp[i][j]=max(dp[i][j], w[i][j]);
		}
	}
	cout << dp[0][n-1];
}
