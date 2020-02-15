/*
	- Finding lattice points not above a line is similar to computing f(n, a, b, c) = sum(0<=x<=n, flr((a*x+b)/c))
	- m = floor((a*n+b)/c)
		- Note that m<=n if a, b < c
	- = sum(0<=x<=n, sum(0<=y<m, y+1<=(a*x+b)/c))
	- = sum(0<=y<m, sum(0<=x<=n, (c*y+c-b)/a<=x))
	- = sum(0<=y<m, sum(0<=x<=n, (c*y+c-b-1)/a<x))
	- = m*(n+1)-sum(0<=y<m, sum(0<=x<=n, (c*y+c-b-1)/a>=x))
	- = m*n-sum(0<=y<=m-1, floor((c*y+c-b-1)/a))
	- Which becomes a subproblem like euclidean's algorithm
	- http://www.voidcn.com/article/p-mxhcmjmq-bpn.html
*/

#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int mxA=1e5;
int n, ai;
ll c[mxA+1];

ll f(ll n, ll a, ll b, ll c) {
	if(!a)
		return b/c*(n+1);
	if(a>=c||b>=c)
		return f(n, a%c, b%c, c)+a/c*n*(n+1)/2+b/c*(n+1);
	ll m=(a*n+b)/c;
	return !m?0:m*n-f(m-1, c, c-b-1, a);
}

ll gul(ll n, ll a, ll b, int c) {
	if(b<0) {
		ll sx=(a-b-1)/a;
		n-=sx;
		b+=a*sx;
	}
	if(n<0)
		return 0;
	return f(n, a, b, c);
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> n;
	vector<array<int, 2>> v;
	for(int i=0; i<n; ++i) {
		cin >> ai;
		vector<array<int, 2>> nv{{ai, 1}};
		for(array<int, 2> vi : v) {
			vi[0]=__gcd(vi[0], ai);
			if(nv.back()[0]!=vi[0])
				nv.push_back({vi[0], 0});
			nv.back()[1]+=vi[1];
		}
		v=nv;
		for(array<int, 2> vi : v)
			c[vi[0]]+=vi[1];
	}
	ll n2=(ll)n*(n+1)/2, k=(n2*(n2+1)/2+1)/2, lb=1, rb=(ll)1e15;
	while(lb<rb) {
		ll mb=(lb+rb)/2, b=0, s1=0, s2=0;
		for(int i=1; i<=mxA; ++i) {
			ll ml=min(mb/i, c[i]);
			b+=c[i]*ml-ml*(ml-1)/2;
		}
		for(int i1=1, i2=2; i1<mxA; ++i1) {
			b+=c[i1]*s1;
			while(i2<mxA&&(s2+i2*c[i2]<=mb||i2<=i1+1)) {
				if(c[i2])
					b+=gul(c[i1]-1, i1, mb-s2-i1*c[i1], i2)-gul(c[i1]-1, i1, mb-s2-i1*c[i1]-i2*c[i2], i2);
				s1+=c[i2];
				s2+=i2*c[i2];
				++i2;
			}
			if(c[i2])
				b+=gul(c[i1]-1, i1, mb-s2-i1*c[i1], i2)-gul(c[i1]-1, i1, mb-s2-i1*c[i1]-i2*c[i2], i2);
			s1-=c[i1+1];
			s2-=(i1+1)*c[i1+1];
		}
		if(b>=k)
			rb=mb;
		else
			lb=mb+1;
	}
	cout << lb;
}
