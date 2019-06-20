#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	int t;
	cin >> t;
	for(int ti=1; ti<=t; ++ti) {
		string s;
		cin >> s;
		string t(s.size(), '0');
		for(int i=0; i<s.size(); ++i) {
			if(s[i]=='4') {
				s[i]='3';
				t[i]='1';
			}
		}
		cout << "Case #" << ti << ": " << s << " " << t << "\n";
	}
}
