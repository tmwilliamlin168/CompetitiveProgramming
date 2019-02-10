#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int mxN=550, M=1e9+7;
int n, m;
ll iv[mxN+1], f1[mxN+1], f2[mxN+1], p2[mxN+1], ans, dp[mxN+1];
vector<int> a;

void dfs(int s, int t, ll o) {
	if(!s) {
		memset(dp+1, 0, 8*m);
		dp[0]=o;
		for(int i=1; i<=m; ++i) {
			for(int j=1; j<=i; ++j) {
				ll f=dp[i-j]*f1[i-1]%M*f2[i-j]%M;
				for(int ai : a)
					f=f*p2[__gcd(ai, j)]%M;
				dp[i]=(dp[i]+f)%M;
			}
		}
		ans+=dp[m];
	} else if(t) {
		for(int i=0; i*t<=s; ++i, o=o*iv[t]%M) {
			dfs(s-i*t, t-1, o*f2[i]%M);
			a.push_back(t);
		}
		while(a.size()&&a.back()==t)
			a.pop_back();
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> n >> m;
	if(n>m)
		swap(n, m);
	iv[1]=f1[0]=f2[0]=p2[0]=1;
	for(int i=2; i<=m; ++i)
		iv[i]=M-M/i*iv[M%i]%M;
	for(int i=1; i<=m; ++i) {
		f1[i]=f1[i-1]*i%M;
		f2[i]=f2[i-1]*iv[i]%M;
		p2[i]=p2[i-1]*2%M;
	}
	dfs(n, n, f2[m]);
	cout << ans%M;
}
