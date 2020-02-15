#include <bits/stdc++.h>
using namespace std;

#define ll long long

int t, mc[60];
ll n, rb;

ll a(int p) {
	ll lb=1;
	while(lb<rb) {
		ll mb=(lb+rb+1)/2, mp=1;
		for(int i=0; i<p; ++i, mp*=mb) {
			if(n/mb<mp) {
				mp=n+1;
				break;
			}
		}
		if(mp<=n)
			lb=mb;
		else
			rb=mb-1;
	}
	return rb-1;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	for(int i=1; i<60; ++i) {
		int tc=i==1;
		mc[i]=tc-mc[i];
		for(int j=i; (j+=i)<60; )
			mc[j]+=mc[i];
	}
	cin >> t;
	while(t--) {
		cin >> n;
		ll ans=n-1;
		rb=(ll)1e9;
		for(int i=2; i<60; ++i)
			if(mc[i])
				ans+=mc[i]*a(i);
		cout << ans << "\n";
	}
}
