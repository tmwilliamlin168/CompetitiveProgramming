/*
	- Polynomial hashing
		- Coefficient of ith-power is i-j where j<i, s[j]==s[i], and j is maximum (distance to the next occurence of s[i])
		- If such j does not exist, the coefficient is 0
	- Sort queries by left bound and use a binary indexed tree to answer them offline
*/

#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int mxN=2e5;
const ll M=1e9+696969, B1=69;
int n, m, qa1[2*mxN], lst[26], nxt[mxN];
string s;
ll ft1[mxN+1], a1[mxN];

struct query {
	int l, r, i;
	inline bool operator<(const query &o) const {
		return l<o.l;
	}
} qs[mxN*2];

ll modI(ll a, ll m) {
	return (a%=m)<=1?1:((1-modI(m%a, a)*m)/a+m)%m;
}

inline void upd(int i, ll x) {
	for(++i; i<=n; i+=i&-i)
		ft1[i]=(ft1[i]+x)%M;
}

inline ll qry1(int i) {
	ll r=0;
	for(; i; i-=i&-i)
		r+=ft1[i];
	return r%M;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> m >> s;
	for(int i=0; i<m; ++i) {
		int x, y, l;
		cin >> x >> y >> l, --x, --y;
		qs[2*i]={x, x+l-1, 2*i};
		qs[2*i+1]={y, y+l-1, 2*i+1};
	}
	sort(qs, qs+2*m);
	for(int i=0; i<26; ++i)
		lst[i]=n;
	for(int i=n-1; i>=0; --i) {
		nxt[i]=lst[s[i]-'a'];
		if(nxt[i]<n)
			a1[nxt[i]]=nxt[i]-i;
		lst[s[i]-'a']=i;
	}
	ll pb1=1, ib1=modI(B1, M);
	for(int i=0; i<n; ++i, pb1=pb1*B1%M)
		upd(i, a1[i]=a1[i]*pb1%M);
	ll pib1=1;
	for(int i=0, i2=0; i<n; ++i, pib1=pib1*ib1%M) {
		while(i2<2*m&&qs[i2].l<=i) {
			qa1[qs[i2].i]=qry1(qs[i2].r+1)*pib1%M;
			++i2;
		}
		if(nxt[i]<n)
			upd(nxt[i], M-a1[nxt[i]]);
	}
	for(int i=0; i<m; ++i)
		cout << (qa1[2*i]==qa1[2*i+1]?"YES":"NO") << "\n";
}
