#include <bits/stdc++.h>
using namespace std;

const int mxA=2e5;
int n, f, bi, wi, ri, ans, g[mxA];
bitset<mxA+1> c, t, d[99];

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> n >> f;
	for(int i=2; i<=mxA; ++i) {
		if(c[i])
			continue;
		for(long long j=(long long)i*i; j<=mxA; j+=i)
			c[j]=1;
		for(int j=1; j<=i&&i*j<=mxA; ++j)
			if(!c[j])
				t[i*j]=1;
	}
	t[f]=0;
	for(int i=0; i<mxA; ++i) {
		while(d[g[i]][i])
			++g[i];
		d[g[i]]|=t<<i;
	}
	for(int i=0; i<n; ++i) {
		cin >> bi >> wi >> ri;
		ans^=g[wi-bi-1]^g[ri-wi-1];
	}
	for(int i=0; i<2; ++i)
		cout << ((ans>0)^i?"Alice\n":"Bob\n");
}
