#include <bits/stdc++.h>
using namespace std;

int t, n, p, s[100000];

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> t;
	for(int ti=1; ti<=t; ++ti) {
		cin >> n >> p;
		for(int i=0; i<n; ++i)
			cin >> s[i];
		sort(s, s+n);
		int a=0;
		for(int i=0; i<p; ++i)
			a+=s[i];
		int ans=s[p-1]*p-a;
		for(int i=p; i<n; ++i) {
			a+=s[i]-s[i-p];
			ans=min(s[i]*p-a, ans);
		}
		cout << "Case #" << ti << ": " << ans << "\n";
	}
}
