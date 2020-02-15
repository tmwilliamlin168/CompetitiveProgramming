#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int mxN=1e6, M=1e9+7;
int n, m;
ll iv[mxN+1], f1[mxN+1], f2[mxN+1], pn[mxN+1], pm[mxN+1], ans;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> n >> m;
	iv[1]=1;
	for(int i=2; i<=mxN; ++i)
		iv[i]=M-M/i*iv[M%i]%M;
	f1[0]=f2[0]=pn[0]=pm[0]=1;
	for(int i=1; i<=mxN; ++i) {
		f1[i]=f1[i-1]*i%M;
		f2[i]=f2[i-1]*iv[i]%M;
		pn[i]=pn[i-1]*n%M;
		pm[i]=pm[i-1]*m%M;
	}
	for(int i=1; i<=min(n-1, m); ++i)
		ans+=f1[m-1]*f2[i-1]%M*f2[m-i]%M*f1[n-2]%M*f2[n-1-i]%M*pm[n-1-i]%M*(i<n-1?pn[n-2-i]*(i+1)%M:1)%M;
	cout << ans%M;
}
