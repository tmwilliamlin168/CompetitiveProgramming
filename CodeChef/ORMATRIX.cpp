#include <bits/stdc++.h>
using namespace std;

int t, n, m, ans[1000][1000];
string g[1000];
bool b[1000], c[1000];

inline void solve() {
	cin >> n >> m;
	bool a=0;
	memset(b, 0, n);
	memset(c, 0, m);
	for(int i=0; i<n; ++i) {
		cin >> g[i];
		for(int j=0; j<m; ++j) {
			if(g[i][j]=='1') {
				a=1;
				b[i]=1;
				c[j]=1;
			}
		}
	}
	for(int i=0; i<n; ++i) {
		for(int j=0; j<m; ++j)
			cout << (a?(g[i][j]=='1'?0:(b[i]||c[j]?1:2)):-1) << " ";
		cout << "\n";
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> t;
	while(t--)
		solve();
}
