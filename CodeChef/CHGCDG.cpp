#include <bits/stdc++.h>
using namespace std;

const int mxN=1e5, mxC=1e6;
int t, n, a[mxN];
vector<int> b[mxC+1];

inline void solve() {
	cin >> n;
	for(int i=0; i<n; ++i) {
		cin >> a[i];
		for(int j=2; j*j<=a[i]; ++j) {
			if(a[i]%j==0)
				b[j].push_back(0);
			while(a[i]%j==0) {
				a[i]/=j;
				++b[j].back();
			}
		}
		if(a[i]>1)
			b[a[i]].push_back(1);
	}
	int ans=1;
	for(int i=1; i<=mxC; ++i) {
		for(int j=1; ; ++j) {
			int d=0;
			for(int c : b[i]) {
				if(c>j)
					d+=(c-j)/2+j;
				else
					d+=c;
			}
			if(d<j*n)
				break;
			ans*=i;
		}
	}
	cout << ans << "\n";
	for(int i=1; i<=mxC; ++i)
		b[i].clear();
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> t;
	while(t--)
		solve();
}
