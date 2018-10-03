#include <bits/stdc++.h>
using namespace std;

const int mxN=2e5;
int n, q, a[18][mxN], fo[mxN+1], lo[mxN+1];

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> q;
	bool b=0;
	for(int i=0; i<n; ++i)
		cin >> a[0][i];
	for(int i=0; i<n&&!b; ++i)
		b=a[0][i]==q;
	if(!b) {
		for(int i=0; i<n&&!b; ++i) {
			if(!a[0][i]) {
				a[0][i]=q;
				b=1;
			}
		}
	}
	if(!b) {
		cout << "NO\n";
		return 0;
	}
	for(int i=0; i<n; ++i)
		if(i&&!a[0][i])
			a[0][i]=a[0][i-1];
	memset(lo, -1, 4*(q+1));
	for(int i=n-1; i>=0; --i) {
		if(!a[0][i])
			a[0][i]=a[0][i+1];
		fo[a[0][i]]=i;
	}
	for(int i=0; i<n; ++i)
		lo[a[0][i]]=i;
	for(int i=1; 1<<i<=n; ++i)
		for(int j=0; j+(1<<i)<=n; ++j)
			a[i][j]=min(a[i-1][j], a[i-1][j+(1<<(i-1))]);
	for(int i=1; i<=q; ++i) {
		if(lo[i]==-1)
			continue;
		int k=31-__builtin_clz(lo[i]-fo[i]+1);
		if(min(a[k][fo[i]], a[k][lo[i]-(1<<k)+1])<i) {
			cout << "NO";
			return 0;
		}
	}
	cout << "YES\n";
	for(int i=0; i<n; ++i)
		cout << a[0][i] << " ";
}
