#include <bits/stdc++.h>
using namespace std;

const int mxN=1e6;
int n, k, p[mxN+1];
bool c[mxN+1];

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> n >> k;
	iota(p, p+n+1, 0);
	for(int i=2; i<=n; ++i) {
		if(c[i])
			continue;
		for(int j=i; j<=n; j+=i) {
			c[j]=1;
			p[j]=p[j]/i*(i-1);
		}
	}
	sort(p+1, p+n+1);
	cout << (k<2?3:accumulate(p+1, p+k+3, 0ll));
}
