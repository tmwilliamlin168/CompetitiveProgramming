#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define mat vector<vector<ll>>

const int M=1e9+7;
ll n, f1, f2, f3, c;

mat matMul(mat a, mat b, ll m) {
	mat r(a.size(), vector<ll>(b[0].size()));
	for(int i=0; i<a.size(); ++i) {
		for(int k=0; k<a[0].size(); ++k) {
			for(int j=0; j<b[0].size(); ++j) {
				r[i][j]+=a[i][k]*b[k][j];
				if(r[i][j]>=m*m)
					r[i][j]-=m*m;
			}
		}
	}
	for(int i=0; i<r.size(); ++i)
		for(int j=0; j<r[0].size(); ++j)
			r[i][j]%=m;
	return r;
}

mat matExp(mat b, ll p, ll m) {
	mat r(b.size(), vector<ll>(b.size()));
	for(int i=0; i<b.size(); ++i)
		r[i][i]=1;
	while(p) {
		if(p&1)
			r=matMul(r, b, m);
		b=matMul(b, b, m);
		p/=2;
	}
	return r;
}

ll exp(ll b, ll p) {
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

	cin >> n >> f1 >> f2 >> f3 >> c;
	mat m1=matExp({{1, 1, 1}, {1, 0, 0}, {0, 1, 0}}, n-3, M-1), m2=matExp({{1, 1, 1, 2, M-7}, {1, 0, 0, 0, 0}, {0, 1, 0, 0, 0}, {0, 0, 0, 1, 1}, {0, 0, 0, 0, 1}}, n-3, M-1);
	ll f1p=m1[0][2], f2p=m2[0][1], f3p=m1[0][0], cp=m2[0][3]*4+m2[0][4];
	cout << exp(f1, f1p)*exp(f2, f2p)%M*exp(f3, f3p)%M*exp(c, cp)%M;
}
