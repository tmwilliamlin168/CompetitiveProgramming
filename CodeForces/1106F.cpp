#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int mxN=100, M=998244353;
int n, c, d;
ll b[mxN][mxN], b2[mxN][mxN], a[mxN], a2[mxN];

ll bsgs(ll g, ll t) {
	ll b=1, gp=g;
	while(b*b<M) {
		gp=gp*g%M;
		++b;
	}
	unordered_map<ll, ll> mp;
	for(ll i=1, p2=gp; i<=b; ++i, p2=p2*gp%M)
		mp[p2]=i;
	for(ll i=0, p2=1; i<b; ++i, p2=p2*g%M)
		if(mp.find(t*p2%M)!=mp.end())
			return mp[t*p2%M]*b-i;
}

ll mi(ll a, ll m) {
	return a<2?1:(1-mi(m%a, a)*m)/a+m;
}

ll pm(ll b, ll p) {
	ll r=1;
	while(p) {
		if(p&1)
			r=r*b%M;
		b=b*b%M;
		p/=2;
	}
	return r;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> n;
	for(int i=0; i<n; ++i)
		cin >> b[0][i];
	for(int i=1; i<n; ++i)
		b[i][i-1]=1;
	cin >> c >> d, c-=n;
	a[0]=1;
	while(c) {
		if(c&1) {
			memset(a2, 0, sizeof(a));
			for(int i=0; i<n; ++i)
				for(int k=0; k<n; ++k)
					a2[i]=(a2[i]+b[i][k]*a[k])%(M-1);
			memcpy(a, a2, sizeof(a));
		}
		memset(b2, 0, sizeof(b));
		for(int i=0; i<n; ++i)
			for(int k=0; k<n; ++k)
				for(int j=0; j<n; ++j)
					b2[i][j]=(b2[i][j]+b[i][k]*b[k][j])%(M-1);
		memcpy(b, b2, sizeof(b));
		c/=2;
	}
	d=bsgs(3, d)%(M-1);
	if(!a[0]) {
		cout << (d?-1:1);
		return 0;
	}
	ll g=__gcd(a[0], (ll)M-1);
	if(d%g) {
		cout << -1;
		return 0;
	}
	cout << pm(3, d/g*mi(a[0]/g, (M-1)/g));
}
