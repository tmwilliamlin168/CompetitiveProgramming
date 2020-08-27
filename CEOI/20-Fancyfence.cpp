#include <bits/stdc++.h>
using namespace std;
 
#define ll long long
 
const int mxN=1e5, M=1e9+7;
int n, l[mxN], r[mxN];
ll h[mxN], w[mxN+1], ans;
 
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n;
	for(int i=0; i<n; ++i) {
		cin >> h[i];
		l[i]=i-1;
		while(~l[i]&&h[l[i]]>h[i])
			l[i]=l[l[i]];
	}
	for(int i=0; i<n; ++i) {
		cin >> w[i+1];
		w[i+1]+=w[i];
	}
	for(int i=n-1; ~i; --i) {
		r[i]=i+1;
		while(r[i]<n&&h[r[i]]>=h[i])
			r[i]=r[r[i]];
		ll cw=(w[r[i]]-w[l[i]+1])%M, lh=max(~l[i]?h[l[i]]:0, r[i]<n?h[r[i]]:0);
		ans=((cw*(cw+1)/2%M)*((h[i]-lh)*(lh+1+h[i])/2%M)+ans)%M;
	}
	cout << ans;
}
