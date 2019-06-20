#include <bits/stdc++.h>
using namespace std;

const int M[7]={16,9,5,7,11,13,17};
int t, n, m;
bool ans[1000001];

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> t >> n >> m;
	while(t--) {
		memset(ans, 0, m+1);
		for(int i=0; i<7; ++i) {
			for(int j=0; j<18; ++j)
				cout << M[i] << " ";
			cout << endl;
			int s=0;
			for(int j=0, a; j<18; ++j)
				cin >> a, s=(s+a)%M[i];
			for(int j=1; j<=m; ++j)
				ans[j]|=j%M[i]^s;
		}
		for(int i=1; i<=m; ++i)
			if(!ans[i])
				cout << i << endl;
		cin >> n;
	}
}
