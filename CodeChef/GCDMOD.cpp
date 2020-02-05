#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int M=1e9+7;
int t;
ll a, b, n, m, pa, pb, s;

inline ll gcd(ll a, ll b) {
	if(a&&b)
		while((a%=b)&&(b%=a));
	return a^b;
}

inline ll exp(ll b, ll p, ll m) {
	ll r=1;
	while(p) {
		if(p&1)
			r=(__int128)r*b%m;
		b=(__int128)b*b%m;
		p/=2;
	}
	return r;
}

inline void solve() {
	cin >> a >> b >> n;
	m=a==b?M:a-b;
	s=(exp(a, n, m)+exp(b, n, m))%m;
	cout << gcd(a-b, s)%M << "\n";
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> t;
	while(t--)
		solve();
}
