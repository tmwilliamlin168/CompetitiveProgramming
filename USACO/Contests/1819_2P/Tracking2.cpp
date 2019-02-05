#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int mxN=1e5, M=1e9+7;
int n, k, a[mxN+1];

ll dp(ll b, int m) {
	vector<ll> dp{1, 1};
	for(int i=1; i<k; ++i)
		dp.push_back(dp.back()*b%M);
	ll c=1;
	for(int i=0; i<k; ++i)
		c=c*(b-1)%M;
	for(int i=0; i<m; ++i)
		dp.push_back((dp.back()*b-dp[i]*c%M+M)%M);
	return dp[k+m];
}

int main() {
	ifstream cin("tracking2.in");
	ofstream cout("tracking2.out");

	cin >> n >> k;
	for(int i=1; i<=n-k+1; ++i)
		cin >> a[i], a[i]=M-6-a[i];
	a[0]=a[n-k+2]=M;
	ll ans=1;
	for(int i=1; i<=n-k+1; ) {
		int j=i;
		while(++j<=n-k+1&&a[j]==a[i]);
		ans=ans*dp(a[i], j-i-((a[i-1]<a[i])+(a[j]<a[i]))*k)%M;
		i=j;
	}
	cout << ans;
}
