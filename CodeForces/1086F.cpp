#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int mxN=50, M=998244353, i2=499122177, i6=166374059;
int n, t, it[mxN*mxN+1], y[2*mxN];
array<int, 2> p[mxN];
ll ans, b[3];

ll f(int t) {
	for(int i=0; i<n; ++i) {
		y[2*i]=p[i][1]-t;
		y[2*i+1]=p[i][1]+t+1;
	}
	sort(y, y+2*n);
	ll r=0;
	for(int i=0; i<2*n-1; ++i) {
		for(int j=0, l=-M; j<n; ++j) {
			if(y[i]<p[j][1]-t||y[i]>p[j][1]+t||p[j][0]+t<=l)
				continue;
			r+=(ll)(y[i+1]-y[i])*(p[j][0]+t-max(l, p[j][0]-t-1));
			l=p[j][0]+t;
		}
	}
	return r%M;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> n >> t;
	for(int i=0; i<n; ++i)
		cin >> p[i][0] >> p[i][1];
	sort(p, p+n);
	for(int i=0; i<n; ++i)
		for(int j=i+1; j<n; ++j)
			it[i*n+j]=(max(p[j][0]-p[i][0], abs(p[j][1]-p[i][1]))+1)/2;
	it[0]=t;
	sort(it, it+n*n+1);
	for(int i=0; it[i]<t; ++i) {
	    ll td=it[i+1]-it[i];
		for(int j=0; j<min(3ll, td); ++j)
			b[j]=f(it[i]+j);
		if(td>=4) {
			ans+=(b[0]*i2+M-b[1]+b[2]*i2)%M*(td-1)%M*td%M*(2*td-1)%M*i6%M;
			ans+=(M-3*b[0]*i2%M+2*b[1]+M-b[2]*i2%M)%M*(td-1)%M*td%M*i2%M;
			ans+=b[0]*td%M;
		} else
			for(int j=0; j<td; ++j)
				ans+=b[j];
	}
	cout << (t*f(t)-ans%M+M)%M;
}
