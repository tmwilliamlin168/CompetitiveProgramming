#include <bits/stdc++.h>
using namespace std;

const int mxN=1000;
int n, a[mxN], b[mxN], c1[mxN+1], c2[mxN+1];

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n;
	for(int i=0; i<n; ++i)
		cin >> a[i], ++c1[a[i]];
	for(int i=0; i<n; ++i)
		cin >> b[i], ++c2[b[i]];
	bool ch=0;
	for(int i=1; i<=mxN&&!ch; ++i) {
		if(c2[i]<c1[i]) {
			++c2[i];
			ch=1;
		}
	}
	int ans=0;
	for(int i=1; i<=mxN; ++i)
		ans+=min(c1[i], c2[i]);
	cout << ans-!ch;
}
