#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int mxN=1e6, M=1e9+7;
int n, p[mxN];
ll a[mxN], b[mxN+1], c[mxN+1];

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n;
	for(int i=0; i<n; ++i)
		cin >> a[i];
	for(int i=1; i<n; ++i)
		cin >> p[i], --p[i];
	for(int i=n-1; i; --i)
		a[p[i]]+=a[i];
	for(int i=0; i<n; ++i) {
		ll g=__gcd(a[0], a[i]);
		if(a[0]/g<=n)
			++b[a[0]/g];
	}
	for(int i=n; i; --i)
		for(int j=i; (j+=i)<=n; )
			b[j]+=b[i];
	for(int i=n; i; --i) {
		if(b[i]>=i) {
			c[i]=1;
			for(int j=i; (j+=i)<=n; )
				c[i]=(c[j]+c[i])%M;
		}
	}
	cout << c[1];
}
