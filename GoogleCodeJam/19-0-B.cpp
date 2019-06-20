#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	int t, n;
	cin >> t;
	for(int ti=1; ti<=t; ++ti) {
		string s;
		cin >> n >> s;
		cout << "Case #" << ti << ": ";
		for(int i=0; i<2*(n-1); ++i)
			cout << (char)(s[i]^'E'^'S');
		cout << "\n";
	}
}
