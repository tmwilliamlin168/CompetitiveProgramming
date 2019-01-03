#include <bits/stdc++.h>
using namespace std;

const int mxN=1e7;
int n, l, r, a[mxN+1], b[mxN+1];
long long ans;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> n >> l >> r;
	if(n==1) {
		cout << r-l+1;
		return 0;
	}
	for(int i=1; ; ++i) {
		int pi=1;
		for(int j=0; j<n-1&&pi<=r; ++j, pi*=i);
		if(pi>r)
			break;
		for(int j=0; (j+=pi)<=r; )
			a[j]=pi;
		b[pi]=i;
	}
	for(int i=1; i<=r; ++i)
		b[i]=b[i]?b[i]:b[i-1];
	for(int i=l; i<=r; ++i)
		ans+=b[r/(i/a[i])]-b[a[i]];
	cout << ans*2;
}
