/*
	- We can use Alien's trick
	- It can be proven with min-cost flow or quadrangle inequalities
*/

#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pli pair<ll, int>

const int mxN=3e5;
int n, k;
ll a[mxN+1], lb, rb=3e14;
pli dp[mxN+1];

pli cdp(ll x) {
	memset(dp, 0, sizeof(dp));
	pli ms{};
	for(int i=0; i<n; ++i) {
		pli cs{dp[i].first-a[i], dp[i].second};
		if(cs.first^ms.first?cs.first>ms.first:cs.second<ms.second)
			ms=cs;
		pli nd{ms.first-x+a[i+1], ms.second+1};
		dp[i+1]=(nd.first^dp[i].first?nd.first>dp[i].first:nd.second<dp[i].second)?nd:dp[i];
	}
	return dp[n];
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> n >> k;
	for(int i=0; i<n; ++i)
		cin >> a[i+1], a[i+1]+=a[i];
	while(lb<rb) {
		ll mb=(lb+rb)/2;
		if(cdp(mb).second<=k)
			rb=mb;
		else
			lb=mb+1;
	}
	pli r=cdp(lb);
	cout << r.first+k*lb;
}
