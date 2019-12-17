#include <bits/stdc++.h>
using namespace std;

const int mxN=300, mxK=mxN*(mxN-1)/2;
int n, k, M, dp11[mxN][mxK+1], dp12[mxN][mxK+1], dp21[mxN][mxK+1], ans[mxN];

void am(int &a, int b) {
	a+=b;
	if(a>=M)
		a-=M;
}

int main() {
	ifstream cin("treedepth.in");
	ofstream cout("treedepth.out");
	
	cin >> n >> k >> M;
	dp11[0][0]=1;
	dp12[0][0]=1;
	for(int i=0; i<n-1; ++i) {
		for(int j=0; j<=k; ++j) {
			am(dp11[i+1][j], dp11[i][j]);
			am(dp12[i+1][j], dp12[i][j]);
			if(j+i+2<=k) {
				am(dp11[i+1][j+i+2], M-dp11[i][j]);
				am(dp12[i+1][j+i+2], M-dp12[i][j]);
			}
			am(dp12[i+1][j], dp11[i][j]);
			am(dp12[i+1][j+1], M-dp11[i][j]);
		}
		for(int j=0; j<k; ++j) {
			am(dp11[i+1][j+1], dp11[i+1][j]);
			am(dp12[i+1][j+1], dp12[i+1][j]);
		}
	}
	dp21[n-1][0]=1;
	for(int i=n-2; ~i; --i) {
		for(int j=0; j<=k; ++j) {
			am(dp21[i][j], dp21[i+1][j]);
			if(j+i+2<=k)
				am(dp21[i][j+i+2], M-dp21[i+1][j]);
		}
		for(int j=0; j<k; ++j)
			am(dp21[i][j+1], dp21[i][j]);
	}
	for(int i=0; i<n; ++i)
		for(int j=0; j<=k; ++j)
			ans[i]=(ans[i]+(long long)dp12[i][j]*dp21[i][k-j])%M;
	memset(dp11, 0, sizeof(dp11));
	memset(dp12, 0, sizeof(dp12));
	dp11[0][0]=1;
	dp12[0][0]=0;
	for(int i=0; i<n-1; ++i) {
		for(int j=0; j<=k; ++j) {
			am(dp11[i+1][j], dp11[i][j]);
			am(dp12[i+1][j], dp12[i][j]);
			if(j+i+2<=k) {
				am(dp11[i+1][j+i+2], M-dp11[i][j]);
				am(dp12[i+1][j+i+2], M-dp12[i][j]);
			}
			am(dp12[i+1][j+i+1], dp11[i][j]);
			if(j+i+2<=k)
				am(dp12[i+1][j+i+2], M-dp11[i][j]);
		}
		for(int j=0; j<k; ++j) {
			am(dp11[i+1][j+1], dp11[i+1][j]);
			am(dp12[i+1][j+1], dp12[i+1][j]);
		}
	}
	for(int i=0; i<n; ++i)
		for(int j=0; j<=k; ++j)
			ans[i]=(ans[i]+(long long)dp12[n-1-i][j]*dp21[n-1-i][k-j])%M;
	for(int i=0; i<n; ++i)
		cout << ans[i] << " \n"[i==n-1];
}
