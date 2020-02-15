/*
	- The numerator will be the number of ways to get the key to the middle cup
	- The denominator will be 2^n
	- By observing small cases you can prove that for n>1 the numerator will have exactly one factor of 2
	- Use matrix exponentiation to find the numerator
*/

#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int mxK=1e5;
const ll M=1e9+7, i2=5e8+4;
int k;
ll a[mxK], p2=2, r2;

struct mat {
	ll a, b, c, d;
	inline mat operator*(const mat &o) const {
		return {(a*o.a+b*o.c)%M, (a*o.b+b*o.d)%M, (c*o.a+d*o.c)%M, (c*o.b+d*o.d)%M};
	}
	inline mat operator*=(const mat &o) {
		*this=*this*o;
		return *this;
	}
} m={1, 1, 2, 0}, r1;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> k;
	for(int i=0; i<k; ++i)
		cin >> a[i];
	bool b=0;
	for(int i=0; i<k&&!b; ++i)
		b=a[i]>1;
	if(!b) {
		cout << "0/1";
		return 0;
	}
	for(int i=0; i<k; ++i) {
		r1={1, 0, 0, 1};
		r2=1;
		while(a[i]) {
			if(a[i]%2) {
				r1*=m;
				r2=r2*p2%M;
			}
			m*=m;
			p2=p2*p2%M;
			a[i]/=2;
		}
		m=r1;
		p2=r2;
	}
	cout << m.d*i2%M << "/" << p2*i2%M;
}
