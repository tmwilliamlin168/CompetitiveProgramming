/*
	- http://ceoi.inf.elte.hu/probarch/16/trick-solution.pdf
*/

#include <bits/stdc++.h>
using namespace std;

const int mxN=1234567;
int t, r, n, m;
bool a[2*mxN+1];

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> t >> r;
	while(t--) {
		cin >> n, m=2*n+1;
		vector<array<int, 2>> p{{0, 2*n}, {0, 1}, {2*n-1, n}, {2, n}, {n+1, 4}, {n+1, 2*n-3}};
		if(n&1)
			for(int i=2; i<6; ++i)
				swap(p[i][0], p[i][1]);
		for(int i=1; i<n; ++i)
			p.push_back({i, m-i});
		if(r^3) {
			memset(a, 0, m);
			long long s=0;
			for(int i=0, b; i<n; ++i)
				cin >> b, s+=b, a[b]=1;
			for(array<int, 2> c : p) {
				if(a[(c[0]+s)%m]&&a[(c[1]+s)%m]) {
					cout << (c[0]+s)%m << " " << (c[1]+s)%m << "\n";
					break;
				}
			}
		} else {
			int s=0;
			for(int i=0, b0, b1; i<2; ++i) {
				cin >> b0 >> b1;
				for(array<int, 2> c : p)
					if((b0-c[0]+m)%m==(b1-c[1]+m)%m)
						s+=b0-c[0]+m;
			}
			cout << (4*m-s)%m << "\n";
		}
	}
}
