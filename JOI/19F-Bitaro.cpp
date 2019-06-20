#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int mxN=3e3;
int h, w, a[mxN];
string g[mxN];
ll ans;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> h >> w;
	for(int i=0; i<h; ++i)
		cin >> g[i];
	for(int i=h-1; i>=0; --i) {
		for(int j=w-1, b=0; j>=0; --j) {
			if(g[i][j]=='J')
				ans+=a[j]*b;
			else if(g[i][j]=='O')
				++b;
			else
				++a[j];
		}
	}
	cout << ans;
}
