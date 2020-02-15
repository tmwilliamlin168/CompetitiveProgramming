#include <bits/stdc++.h>
using namespace std;

#define ll long long

ll n, k, l, r, ans=-1;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> l >> r >> k, r=(r-l+n)%n;
	if(n<3e5) {
		auto c=[&](ll i, int a, int b) {
			ll j=(k-r-a+n+i+b)%(n+i+b);
			if(j<=min(i, r)&&i<=j+n-1-r&&k>=r+a+j)
				ans=max(i+b, ans);
		};
		for(ll i=0; i<=n-1; ++i) {
			c(i, 1, 0);
			c(i, 1, 1);
			c(i, 2, 1);
		}
	} else {
		for(int i=1; i<=2; ++i)
			for(int j=0; j<i; ++j)
				if(0<=k+j-i-r&&k+j-i-r<=r)
					ans=max(k+j+n-2*r-2, ans);
		auto c=[&](ll i, ll x, int c) {
			ll a=max((x-r+i-1)/i, (x+i)/(i+1)), b=min(x/i, (x+n-1-r)/(i+1));
			if(a<=b)
				ans=max(b+c, ans);
		};
		for(ll i=1; i*n+r+1<=k; ++i) {
			c(i, k-i*n-r-1, 0);
			c(i, k-i*n-i-r-2, 1);
			c(i, k-i*n-i-r-1, 1);
		}
	}
	cout << ans;
}
