/*
	- http://codeforces.com/blog/entry/60701?#comment-446462
*/

#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int mxN=100, mxQ=1e6;
const ll M=1e9+7, INF=1e18;
int c, n, m;
ll w[mxN+1], dp[mxQ+1];

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> c >> n >> m;
	for(int i=0; i<=n; ++i)
		w[i]=INF;
	while(c--) {
		int ai, wi;
		cin >> ai >> wi;
		w[ai]=wi;
	}
	for(int i=1; i<=mxQ; ++i) {
		dp[i]=INF;
		for(int j=1; j<=min(n, i); ++j)
			dp[i]=min(dp[i-j]+w[j], dp[i]);
	}
	while(m--) {
		ll qi;
		cin >> qi;
		if(qi>mxQ) {
			__int128 ans=(__int128)INF*INF;
			for(int i=1; i<=n; ++i) {
				ll j=mxQ/i*i+qi%i-i;
				if(w[i]>=INF||dp[j]>=INF)
				    continue;
				ans=min(dp[j]+(__int128)w[i]*((qi-j)/i), ans);
			}
			cout << (ans>=(__int128)INF*INF?-1:(ll)(ans%M)) << "\n";
		} else
			cout << (dp[qi]>=INF?-1:dp[qi]%M) << "\n";
	}
}
