#include <bits/stdc++.h>
using namespace std;

class PrimeSubstrings {
public:
	string construct(int n, int l) {
		vector<string> s={"", "2", "11", "113", "1193", "11939", "193939", "13339913"};
		string t;
		for(int i=0; i<n; ++i)
			t+=s[l][i%s[l].size()];
		return t;
	}
};
