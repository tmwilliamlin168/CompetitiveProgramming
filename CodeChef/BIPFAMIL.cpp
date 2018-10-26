#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int mxN=2.5e3, M=1e9+7;
int t, n, m;
ll f1[mxN+1], f2[mxN+1], dp[mxN+1][mxN+1];

ll exp(ll b, int p) {
	ll r=1;
	while(p) {
		if(p&1)
			r=r*b%M;
		b=b*b%M;
		p/=2;
	}
	return r;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	f1[0]=f2[0]=1;
	for(int i=1; i<=mxN; ++i) {
		f1[i]=f1[i-1]*i%M;
		f2[i]=exp(f1[i], M-2);
	}
	for(int i=0; i<=mxN; ++i)
		dp[1][i]=f2[i];
	for(int i=2; i<=mxN; ++i) {
		for(int j=1; j<=mxN/i; ++j) {
			for(int k=1; k<i; ++k)
				for(int l=1; l<=j; ++l)
					dp[i][j]+=dp[i-k][j-l]*(exp(i+k*(k-1)/2, l)-exp(k*(k+1)/2, l)+M)%M*f2[l]%M;
			dp[i][j]%=M;
		}
	}
	cin >> t;
	while(t--) {
		cin >> n >> m;
		cout << dp[m][n]*f1[n]%M << "\n";
	}
}
