#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int mxN=5e3, M=998244353;
int n[2];
string s[2];
ll dp1[2][2][2*mxN+1], dp2[2][2][2*mxN+1], ans;

void a(int &n, string &s, ll dp1[2][2*mxN+1], ll dp2[2][2*mxN+1]) {
	cin >> s;
	s+='P';
	n=s.size();
	dp1[n&1^1][n-1]=dp2[n&1^1][n-1]=1;
	for(int i=n-2; i>=0; --i) {
		memset(dp1[i&1], 0, 8*(2*n-1));
		memset(dp2[i&1], 0, 8*(2*n-1));
		if(s[i]!='P') {
			for(int j=1; j<2*n-1; ++j) {
				dp1[i&1][j]=dp1[i&1^1][j-1];
				dp2[i&1][j]=dp2[i&1^1][j-1];
			}
		}
		if(s[i]!='V') {
			for(int j=0; j<n-1; ++j) {
				dp1[i&1][j]=(dp1[i&1][j]+dp1[i&1^1][j+1])%M;
				dp2[i&1][j]=(dp2[i&1][j]+dp2[i&1^1][j+1])%M;
			}
			for(int j=n; j<2*n-1; ++j)
				dp1[i&1][n-1]=(dp1[i&1][n-1]+dp1[i&1^1][j])%M;
		}
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	for(int i : {0, 1})
		a(n[i], s[i], dp1[i], dp2[i]);
	for(int i=0; i<2*n[0]-1; ++i)
		for(int j=2*n[1]-2; j>=0&&i+j>n[0]+n[1]-2; --j)
			ans+=dp1[0][0][i]*dp1[1][0][j]%M;
	for(int i=max(n[0]-n[1], 0); i<=min(2*n[0]-2, n[0]+n[1]-2); ++i)
		ans+=dp2[0][0][i]*dp2[1][0][n[0]+n[1]-2-i]%M;
	cout << ans%M;
}
