#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int mxN=1e5, M=1e9+7;
int n, k;
ll pk[mxN], mb[mxN], ans;
bool c[mxN];

ll iv(ll a, ll m) {
	return a<2?1:(1-iv(m%a, a)*m)/a+m;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> n >> k;
	pk[1]=iv(k, M);
	for(int i=2; i<n; ++i)
		pk[i]=pk[i-1]*pk[1]%M;
	fill(mb, mb+n, 1);
	for(int i=2; i<n; ++i) {
		if(c[i])
			continue;
		for(int j=i; j<n; j+=i) {
			if(j/i%i)
				mb[j]=mb[j]*(M-1)%M;
			else
				mb[j]=0;
			c[j]=1;
		}
	}
	for(int i=1; i<n; ++i) {
		for(int t=i; t<2*n-1; t+=i) {
			for(int s=t; s<2*n-1; s+=t) {
				int g=s/t, l=max(t-(n-1)/g-1, 0), r=min(t-1, (n-1)/g);
				if(l<r&&g<n)
					ans=(ans+(r/i-l/i)*pk[n-max(s-n, g)]%M*mb[i])%M;
			}
		}
	}
	cout << ans;
}
