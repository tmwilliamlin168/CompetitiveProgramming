#include <bits/stdc++.h>
using namespace std;

const int mxN=1e6;
int n, a[mxN], b[mxN];

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n;
	for(int i=0; i<n; ++i)
		cin >> a[i] >> b[i];
	for(bool ch=1; ch; ) {
		ch=0;
		for(int i=0; i<n; ++i) {
			if(a[i]<=b[i]||a[i]<2)
				continue;
			int c=max((a[i]-b[i])/2, 1);
			a[i]-=c*2;
			a[(i+1)%n]+=c;
			ch|=c;
		}
	}
	cout << (memcmp(a, b, 4*n)?"No":"Yes");
}
