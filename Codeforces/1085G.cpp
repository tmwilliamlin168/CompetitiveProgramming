#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int mxN=2e3, M=998244353;
int n, a[mxN][mxN], ft[2][mxN+1];
ll dp[mxN+1][mxN+1], ans, p1=1;
bool v1[mxN], v2[mxN];

void upd(int i, int j, int x) {
	for(++j; j<=n; j+=j&-j)
		ft[i][j]+=x;
}

int qry(int i, int j) {
	int r=0;
	for(; j; j-=j&-j)
		r+=ft[i][j];
	return r;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin >> n;
	for(int i=0; i<n; ++i)
		for(int j=0; j<n; ++j)
			cin >> a[i][j], --a[i][j];
	dp[0][0]=1;
	for(int i=1; i<=n; ++i) {
		dp[i][0]=dp[i-1][1]*(i-1)%M;
		for(int j=1; j<=n; ++j)
			dp[i][j]=(dp[i-1][j-1]*j+dp[i-1][j]*(i-j))%M;
	}
	for(int i=n-1; i; --i, p1=p1*dp[n][0]%M) {
		memset(v1, 0, n);
		memset(v2, 0, n);
		for(int j=0; j<n; ++j)
			upd(0, j, 1);
		for(int j=0, um=1; j<n; ++j, ++um) {
			v1[a[i-1][j]]=1;
			if(!v2[a[i-1][j]])
				upd(0, a[i-1][j], -1);
			else
				--um;
			ans+=(qry(0, a[i][j])*dp[n-j-1][um]+qry(1, a[i][j])*dp[n-j-1][um-1])%M*p1%M;
			if(!v2[a[i-1][j]])
				upd(1, a[i-1][j], 1);
			um-=v1[a[i][j]];
			v2[a[i][j]]=1;
			upd(v1[a[i][j]], a[i][j], -1);
		}
	}
	for(int j=n-1; j>=0; p1=p1*(n-j)%M, --j) {
		ans+=qry(0, a[0][j])*p1%M;
		upd(0, a[0][j], 1);
	}
	cout << ans%M;
}
